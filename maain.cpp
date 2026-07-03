#include <iostream>
#include <string>
#include <vector>
#include "ControladorDeTransito.h"

void exibirMenu() {
    std::cout << "         SISTEMA CONTROLADOR DE VIAGENS\n\n";
    std::cout << "  CADASTRAR_PASSAGEIRO <nome> <cidade>\n";
    std::cout << "  CADASTRAR_TRANSPORTE <nome> <tipo: digite A para aquático ou T para terrestre> <capacidade> <velocidade em km/h> <distancia para descanso em km> <tempo de descanso em horas> <cidade>\n";
    std::cout << "  INICIAR_VIAGEM <transporte> <origem> <destino> <quantidade de passageiros> <passageiro 1> <ppassageiro 2>...\n";
    std::cout << "  AVANCAR_HORAS <quantidade>\n";
    std::cout << "  RELATORIO\n";
    std::cout << "  SAIR\n";
    std::cout << "  O usuario deve digitar cada campo < > com espacos, as cidades estão definidas dessa forma: Fortaleza, Natal, Joao_Pessoa, Recife, Maceio e Salvador. Modo de uso da interface estara melhor explicado no arquivo readme.\n";
}

int main() {
    ControladorDeTransito controlador;
    
    controlador.carregarDados();
    std::cout << "Bem vindo ao sistema controlador de viagens, realizamos viagens para Fortaleza, Natal, Joao Pessoa, Recife, Maceio e Salvador. Primeiramente, digite as distancias requeridas abaixo:\n";
    controlador.inicializarDistancias();

    exibirMenu();
    std::string comando;

    while (true) {
        std::cout << "\nComando > ";
        std::cin >> comando;

        if (comando == "SAIR") {
            controlador.salvarDados();
            std::cout << "Dados salvos com sucesso. Encerrando o sistema.\n";
            break;
        } 
        else if (comando == "CADASTRAR_PASSAGEIRO") {
            std::string nome, cidade;
            std::cin >> nome >> cidade;
            controlador.cadastrarPassageiro(nome, cidade);
        }
        else if (comando == "CADASTRAR_TRANSPORTE") {
            std::string nome, cidade; char tipo;
            int cap, vel, dist_d, temp_d;
            std::cin >> nome >> tipo >> cap >> vel >> dist_d >> temp_d >> cidade;
            controlador.cadastrarTransporte(nome, tipo, cap, vel, dist_d, temp_d, cidade);
        }
        else if (comando == "INICIAR_VIAGEM") {
            std::string trans, orig, dest;
            int qtdPassageiros;
            std::cin >> trans >> orig >> dest >> qtdPassageiros;
            
            std::vector<std::string> passageiros;
            for(int i = 0; i < qtdPassageiros; i++) {
                std::string pass;
                std::cin >> pass;
                passageiros.push_back(pass);
            }
            controlador.iniciarViagem(trans, passageiros, orig, dest);
        }
        else if (comando == "AVANCAR_HORAS") {
            int horas;
            std::cin >> horas;
            controlador.avancarHoras(horas);
        }
        else if (comando == "RELATORIO") {
            controlador.relatarEstado();
        }
    }
    return 0;
}