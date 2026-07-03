#include "Viagem.h"
#include <iostream>

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int distanciaTotal)
    : transporte(transporte), passageiros(passageiros), origem(origem), destino(destino), 
      proxima(nullptr), horasEmTransito(0), emAndamento(false), 
      distanciaTotal(distanciaTotal), distanciaPercorrida(0), 
      kmDesdeUltimoDescanso(0), horasDescansandoRestantes(0) {}

void Viagem::setProxima(Viagem* prox) { proxima = prox; }
Viagem* Viagem::getProxima() { return proxima; }
bool Viagem::isEmAndamento() { return emAndamento; }
Cidade* Viagem::getOrigem() { return origem; }
Cidade* Viagem::getDestino() { return destino; }
Transporte* Viagem::getTransporte() { return transporte; }
std::vector<Passageiro*> Viagem::getPassageiros() { return passageiros; }

void Viagem::iniciarViagem() {
    emAndamento = true;
    transporte->setLocalAtual(nullptr); 
    for (auto p : passageiros) {
        p->setLocalAtual(nullptr); 
    }
}

void Viagem::avancarHoras(int horas) {
    if (!emAndamento) return;

    for (int h = 0; h < horas; ++h) {
        if (horasDescansandoRestantes > 0) {
            horasDescansandoRestantes--;
            horasEmTransito++;
            if (horasDescansandoRestantes == 0) {
                std::cout << transporte->getNome() << " terminou o descanso e voltou a rodar.\n";
            }
            continue;
        }

        horasEmTransito++;
        int vel = transporte->getVelocidade();
        distanciaPercorrida += vel;
        kmDesdeUltimoDescanso += vel;

        if (kmDesdeUltimoDescanso >= transporte->getDistanciaEntreDescansos() && distanciaPercorrida < distanciaTotal) {
            horasDescansandoRestantes = transporte->getTempoDescanso();
            kmDesdeUltimoDescanso = 0;
            std::cout << transporte->getNome() << " parou para descansar por " << horasDescansandoRestantes << "hora(s).\n";
        }

        if (distanciaPercorrida >= distanciaTotal) {
            emAndamento = false;
            std::cout << transporte->getNome() << " completou o trecho ate " << destino->getNome() << ".\n";
            break; 
        }
    }
}