#include <iostream>
#include <fstream>
#include "modulo1/Objeto.hpp"
#include "modulo1/Cena.hpp"


int main(int argc, char* argv[]) {
    const char* nomeArquivo = argv[1];

    std::ifstream entrada;
    entrada.open(nomeArquivo);

    if (!entrada.is_open()) return 1;

    Objeto objetos[100] = {};
    int quantObjetos = 0;

    char tipo;
    while (entrada >> tipo)
    {
        switch (tipo) {
            case 'O': {
                int id;
                double x, y, largura;

                if (entrada >> id >> x >> y >> largura) {
                    objetos[quantObjetos] = Objeto(id, x, y, largura);
                    quantObjetos++;
                }

                break;
            }
            case 'M':{
                int id, tempo;
                double x, y;

                if (entrada >> tempo >> id >> x >> y)
                    for (int i = 0; i < quantObjetos; i++)
                        if (objetos[i].getId() == id) 
                            objetos[i].movimentar(x, y);

                break;
            }
            case 'C': {
                int tempo;

                if (entrada >> tempo) {
                    Cena cena(tempo, objetos, quantObjetos);
                    cena.gerarCena();
                    cena.imprimir();
                }
                
                break;
            }

        }
    }
    

    entrada.close();
}