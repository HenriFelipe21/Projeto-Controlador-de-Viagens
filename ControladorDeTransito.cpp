#include "ControladorDeTransito.h"
#include <iostream>
#include <algorithm>
#include <fstream>

ControladorDeTransito::ControladorDeTransito() {
    ordemCidades = {"Fortaleza", "Natal", "Joao_Pessoa", "Recife", "Maceio", "Salvador"};
}

ControladorDeTransito::~ControladorDeTransito() {
    for (auto c : cidades) delete c;
    for (auto t : trajetos) delete t;
    for (auto tr : transportes) delete tr;
    for (auto p : passageiros) delete p;
    for (auto v : viagens) delete v;
}

Cidade* ControladorDeTransito::buscarCidade(std::string nome) {
    for (auto c : cidades) if (c->getNome() == nome) return c;
    return nullptr;
}

Transporte* ControladorDeTransito::buscarTransporte(std::string nome) {
    for (auto t : transportes) if (t->getNome() == nome) return t;
    return nullptr;
}

Passageiro* ControladorDeTransito::buscarPassageiro(std::string nome) {
    for (auto p : passageiros) if (p->getNome() == nome) return p;
    return nullptr;
}

Trajeto* ControladorDeTransito::buscarTrajetoDireto(Cidade* o, Cidade* d) {
    for (auto t : trajetos) {
        if (t->getOrigem() == o && t->getDestino() == d) return t;
    }
    return nullptr;
}

void ControladorDeTransito::cadastrarCidade(std::string nome, int visitas) {
    if (!buscarCidade(nome)) cidades.push_back(new Cidade(nome, visitas));
}

void ControladorDeTransito::cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia) {
    Cidade* o = buscarCidade(nomeOrigem);
    Cidade* d = buscarCidade(nomeDestino);
    if (o && d) trajetos.push_back(new Trajeto(o, d, tipo, distancia));
}

void ControladorDeTransito::cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade, int dist_descanso, int tempo_descanso, std::string localAtual) {
    Cidade* cid = buscarCidade(localAtual);
    if (cid || localAtual == "") {
        transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, dist_descanso, tempo_descanso, cid));
    }
}

void ControladorDeTransito::cadastrarPassageiro(std::string nome, std::string localAtual) {
    Cidade* cid = buscarCidade(localAtual);
    if (cid || localAtual == "") {
        passageiros.push_back(new Passageiro(nome, cid));
    }
}

void ControladorDeTransito::carregarDados() {
    std::ifstream arqCid("cidades.txt");
    if (arqCid.is_open()) {
        std::string nome; int vis;
        while (arqCid >> nome >> vis) cadastrarCidade(nome, vis);
        arqCid.close();
    } else {
        for (const auto& c : ordemCidades) cadastrarCidade(c, 0);
    }

    std::ifstream arqTraj("trajetos.txt");
    if (arqTraj.is_open()) {
        std::string orig, dest; char tipo; int dist;
        while (arqTraj >> orig >> dest >> tipo >> dist) cadastrarTrajeto(orig, dest, tipo, dist);
        arqTraj.close();
    }

    std::ifstream arqTransp("transportes.txt");
    if (arqTransp.is_open()) {
        std::string n, cid; char t; int c, v, dd, td;
        while (arqTransp >> n >> t >> c >> v >> dd >> td >> cid) {
            cadastrarTransporte(n, t, c, v, dd, td, (cid == "Em_Transito" ? "" : cid));
        }
        arqTransp.close();
    }

    std::ifstream arqPass("passageiros.txt");
    if (arqPass.is_open()) {
        std::string n, cid;
        while (arqPass >> n >> cid) {
            cadastrarPassageiro(n, (cid == "Em_Transito" ? "" : cid));
        }
        arqPass.close();
    }
}

void ControladorDeTransito::salvarDados() {
    std::ofstream arqCid("cidades.txt");
    for (auto c : cidades) arqCid << c->getNome() << " " << c->getVisitas() << "\n";
    
    std::ofstream arqTraj("trajetos.txt");
    for (auto t : trajetos) arqTraj << t->getOrigem()->getNome() << " " << t->getDestino()->getNome() << " " << t->getTipo() << " " << t->getDistancia() << "\n";

    std::ofstream arqTransp("transportes.txt");
    for (auto t : transportes) arqTransp << t->getNome() << " " << t->getTipo() << " " << t->getCapacidade() << " " << t->getVelocidade() << " " << t->getDistanciaEntreDescansos() << " " << t->getTempoDescanso() << " " << (t->getLocalAtual() ? t->getLocalAtual()->getNome() : "Em_Transito") << "\n";

    std::ofstream arqPass("passageiros.txt");
    for (auto p : passageiros) arqPass << p->getNome() << " " << (p->getLocalAtual() ? p->getLocalAtual()->getNome() : "Em_Transito") << "\n";
}

void ControladorDeTransito::inicializarDistancias() {
    if (!trajetos.empty()) return;

    for (size_t i = 0; i < ordemCidades.size() - 1; ++i) {
        int dist;
        std::cout << "Digite a distancia (em km) para o trecho Terrestre entre " << ordemCidades[i] << " e " << ordemCidades[i+1] << ": ";
        std::cin >> dist;
        cadastrarTrajeto(ordemCidades[i], ordemCidades[i+1], 'T', dist);
        cadastrarTrajeto(ordemCidades[i+1], ordemCidades[i], 'T', dist); 
    }
    std::cout << "----------------------------------------\n\n";
}

void ControladorDeTransito::iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, std::string nomeOrigem, std::string nomeDestino) {
    Transporte* trans = buscarTransporte(nomeTransporte);
    Cidade* orig = buscarCidade(nomeOrigem);
    Cidade* dest = buscarCidade(nomeDestino);

    if (!trans || !orig || !dest || trans->getLocalAtual() != orig) {
        std::cout << "Erro: Transporte ou cidades invalidas, ou veiculo fora da origem.\n";
        return;
    }

    std::vector<Passageiro*> passEscolhidos;
    for (const auto& nome : nomesPassageiros) {
        Passageiro* p = buscarPassageiro(nome);
        if (p && p->getLocalAtual() == orig) passEscolhidos.push_back(p);
    }

    // 1. Validar Lotação
    if (passEscolhidos.size() > (size_t)trans->getCapacidade()) {
        std::cout << "Erro: Quantidade de passageiros (" << passEscolhidos.size() 
                  << ") excede a capacidade do veiculo (" << trans->getCapacidade() << ").\n";
        return;
    }

    auto itOrig = std::find(ordemCidades.begin(), ordemCidades.end(), nomeOrigem);
    auto itDest = std::find(ordemCidades.begin(), ordemCidades.end(), nomeDestino);
    if (itOrig == ordemCidades.end() || itDest == ordemCidades.end()) return;

    int idxOrig = std::distance(ordemCidades.begin(), itOrig);
    int idxDest = std::distance(ordemCidades.begin(), itDest);
    int passo = (idxOrig < idxDest) ? 1 : -1;
    
    Viagem* primeiraViagem = nullptr;
    Viagem* ultimaCriada = nullptr;

    int i = idxOrig;
    while (i != idxDest) {
        Cidade* cAtual = buscarCidade(ordemCidades[i]);
        Cidade* cProxima = buscarCidade(ordemCidades[i + passo]);
        Trajeto* traj = buscarTrajetoDireto(cAtual, cProxima);
        
        if (!traj) {
            std::cout << "Erro: Trajeto nao cadastrado entre " << cAtual->getNome() << " e " << cProxima->getNome() << "\n";
            return;
        }

        // 2. Validar Tipo do Transporte vs Trajeto
        if (trans->getTipo() != traj->getTipo()) {
            std::cout << "Erro: Veiculo do tipo '" << trans->getTipo() << "' nao pode navegar pelo trajeto do tipo '" << traj->getTipo() << "'.\n";
            return;
        }

        Viagem* novaPerna = new Viagem(trans, passEscolhidos, cAtual, cProxima, traj->getDistancia());
        if (!primeiraViagem) primeiraViagem = novaPerna;
        else ultimaCriada->setProxima(novaPerna);
        
        ultimaCriada = novaPerna;
        viagens.push_back(novaPerna);
        i += passo;
    }

    if (primeiraViagem) {
        primeiraViagem->iniciarViagem();
        std::cout << "Viagem em andamento de " << nomeOrigem << " ate " << nomeDestino << "!\n";
    }
}

void ControladorDeTransito::avancarHoras(int horas) {
    for (auto v : viagens) {
        if (v->isEmAndamento()) {
            v->avancarHoras(horas);
            
            if (!v->isEmAndamento()) {
                Viagem* prox = v->getProxima();
                if (prox) {
                    prox->iniciarViagem();
                } else {
                    Cidade* destinoFinal = v->getDestino();
                    v->getTransporte()->setLocalAtual(destinoFinal);
                    for (auto p : v->getPassageiros()) p->setLocalAtual(destinoFinal);
                    
                    destinoFinal->adicionarVisita(); 
                    
                    std::cout << "Viagem concluida. Passageiros chegaram em " << destinoFinal->getNome() << "\n";
                }
            }
            break; 
        }
    }
}

void ControladorDeTransito::relatarEstado() {
    std::cout << "\n RELATORIO DE ESTADO \n\n";
    
    std::cout << "VIAGENS EM ANDAMENTO:\n";
    bool temViagem = false;
    for (auto v : viagens) {
        if (v->isEmAndamento()) {
            std::cout << "  - " << v->getTransporte()->getNome() << " de " << v->getOrigem()->getNome() << " para " << v->getDestino()->getNome() << "\n";
            temViagem = true;
        }
    }
    if (!temViagem) std::cout << "  - Nenhuma viagem em andamento.\n";

    std::cout << "\nCIDADES MAIS VISITADAS:\n";
    for (auto c : cidades) {
        std::cout << "  - " << c->getNome() << ": " << c->getVisitas() << " desembarques\n";
    }

    // 3. Relatório com formato Origem-Destino-Transporte
    std::cout << "\nLOCALIZACAO DOS PASSAGEIROS:\n";
    for (auto p : passageiros) {
        if (p->getLocalAtual() != nullptr) {
            std::cout << "  - " << p->getNome() << " -> Cidade: " << p->getLocalAtual()->getNome() << "\n";
        } else {
            bool encontrado = false;
            for (auto v : viagens) {
                if (v->isEmAndamento()) {
                    auto passDaViagem = v->getPassageiros();
                    if (std::find(passDaViagem.begin(), passDaViagem.end(), p) != passDaViagem.end()) {
                        std::cout << "  - " << p->getNome() << " -> Em Transito (Origem: " 
                                  << v->getOrigem()->getNome() << ", Destino: " << v->getDestino()->getNome() 
                                  << ", Transporte: " << v->getTransporte()->getNome() << ")\n";
                        encontrado = true;
                        break;
                    }
                }
            }
            if (!encontrado) std::cout << "  - " << p->getNome() << " -> Em Transito (Aguardando conexao)\n";
        }
    }
    
    std::cout << "\nLOCALIZACAO DOS TRANSPORTES:\n";
    for (auto t : transportes) {
        std::cout << "  - " << t->getNome() << " -> " << (t->getLocalAtual() ? t->getLocalAtual()->getNome() : "Em Transito") << "\n";
    }
    std::cout << "\n";
}