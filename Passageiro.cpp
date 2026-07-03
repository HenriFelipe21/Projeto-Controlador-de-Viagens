#include "Passageiro.h"

Passageiro::Passageiro(std::string nome, Cidade* localAtual) : nome(nome), localAtual(localAtual) {}

std::string Passageiro::getNome() { return nome; }
Cidade* Passageiro::getLocalAtual() { return localAtual; }
void Passageiro::setLocalAtual(Cidade* local) { localAtual = local; }