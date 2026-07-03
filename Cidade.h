#ifndef CIDADE_H
#define CIDADE_H
#include <string>

class Cidade {
private:
    std::string nome;
    int visitas;
public:
    Cidade(std::string nome, int visitas = 0);
    std::string getNome();
    void adicionarVisita();
    int getVisitas();
};
#endif