#include <iostream>
#include <fstream>
#include "modulo1/Objeto.hpp"
#include "modulo1/Cena.hpp"


int main() {

    Objeto objetos[100] = {};
    int quantObjetos = 0;

    char tipo;
    while (std::cin >> tipo)
    {
        switch (tipo) {
            case 'O': {
                int id;
                double x, y, largura;

                if (std::cin >> id >> x >> y >> largura) {
                    objetos[quantObjetos] = Objeto(id, x, y, largura);
                    quantObjetos++;
                }

                break;
            }
            case 'M':{
                int id, tempo;
                double x, y;

                if (std::cin >> tempo >> id >> x >> y)
                    for (int i = 0; i < quantObjetos; i++)
                        if (objetos[i].getId() == id) 
                            objetos[i].movimentar(x, y);

                break;
            }
            case 'C': {
                int tempo;

                if (std::cin >> tempo) {
                    try {
                        Cena cena(tempo, objetos, quantObjetos);
                        cena.gerarCena();
                        cena.imprimir();
                    }
                    catch(std::out_of_range& e) {
                        std::cerr << e.what() << std::endl;
                    }
                    catch(std::logic_error& e) {
                        std::cerr << e.what() << std::endl;
                    }
                    catch(std::exception& e) {
                        std::cerr << e.what() << std::endl;
                    }
                }
                
                break;
            }

        }
    }
}