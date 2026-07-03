#ifndef VIAGEM_H
#define VIAGEM_H
#include <vector>
#include "Transporte.h"
#include "Passageiro.h"
#include "Cidade.h"

class Viagem {
private:
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    Viagem* proxima;
    int horasEmTransito;
    bool emAndamento;
    int distanciaTotal;
    int distanciaPercorrida;
    int kmDesdeUltimoDescanso;
    int horasDescansandoRestantes;

public:
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int distanciaTotal);
    void setProxima(Viagem* prox);
    Viagem* getProxima();
    void iniciarViagem();
    void avancarHoras(int horas);
    bool isEmAndamento();
    Cidade* getOrigem();
    Cidade* getDestino();
    Transporte* getTransporte();
    std::vector<Passageiro*> getPassageiros();
};
#endif