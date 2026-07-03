#include "Transporte.h"

Transporte::Transporte(std::string nome, char tipo, int capacidade, int velocidade, int dist_descanso, int tempo_descanso, Cidade* localAtual)
    : nome(nome), tipo(tipo), capacidade(capacidade), velocidade(velocidade), 
      distancia_entre_descansos(dist_descanso), tempo_de_descanso(tempo_descanso), localAtual(localAtual) {}

std::string Transporte::getNome() { return nome; }
char Transporte::getTipo() { return tipo; }
int Transporte::getCapacidade() { return capacidade; }
Cidade* Transporte::getLocalAtual() { return localAtual; }
void Transporte::setLocalAtual(Cidade* local) { localAtual = local; }
int Transporte::getVelocidade() { return velocidade; }
int Transporte::getDistanciaEntreDescansos() { return distancia_entre_descansos; }
int Transporte::getTempoDescanso() { return tempo_de_descanso; }