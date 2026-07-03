#ifndef TRANSPORTE_H
#define TRANSPORTE_H
#include <string>
#include "Cidade.h"

class Transporte {
private:
    std::string nome;
    char tipo;
    int capacidade;
    int velocidade;
    int distancia_entre_descansos;
    int tempo_de_descanso;
    Cidade* localAtual;
public:
    Transporte(std::string nome, char tipo, int capacidade, int velocidade, int dist_descanso, int tempo_descanso, Cidade* localAtual);
    std::string getNome();
    char getTipo();
    int getCapacidade();
    Cidade* getLocalAtual();
    void setLocalAtual(Cidade* local);
    int getVelocidade();
    int getDistanciaEntreDescansos();
    int getTempoDescanso();
};
#endif