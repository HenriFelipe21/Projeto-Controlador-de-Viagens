#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include <vector>
#include <string>
#include "Cidade.h"
#include "Trajeto.h"
#include "Transporte.h"
#include "Passageiro.h"
#include "Viagem.h"

class ControladorDeTransito {
private:
    std::vector<Cidade*> cidades;
    std::vector<Trajeto*> trajetos;
    std::vector<Transporte*> transportes;
    std::vector<Passageiro*> passageiros;
    std::vector<Viagem*> viagens;

    std::vector<std::string> ordemCidades;

    Cidade* buscarCidade(std::string nome);
    Transporte* buscarTransporte(std::string nome);
    Passageiro* buscarPassageiro(std::string nome);
    Trajeto* buscarTrajetoDireto(Cidade* o, Cidade* d);

public:
    ControladorDeTransito();
    ~ControladorDeTransito();

    void cadastrarCidade(std::string nome, int visitas = 0);
    void cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia);
    void cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade, int dist_descanso, int tempo_descanso, std::string localAtual);
    void cadastrarPassageiro(std::string nome, std::string localAtual);
    
    void iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, std::string nomeOrigem, std::string nomeDestino);
    void avancarHoras(int horas);
    void relatarEstado();

    void carregarDados();
    void salvarDados();
    void inicializarDistancias();
};
#endif