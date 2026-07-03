#include "Cidade.h"

Cidade::Cidade(std::string nome, int visitas) : nome(nome), visitas(visitas) {}

std::string Cidade::getNome() { return nome; }
void Cidade::adicionarVisita() { visitas++; }
int Cidade::getVisitas() { return visitas; }