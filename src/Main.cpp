#include <iostream>
#include <fstream>
#include "modulo1/Objeto.hpp"
#include "modulo1/Cena.hpp"


int main() {
    Cena cena;

    char tipo;
    while (std::cin >> tipo)
    {
        switch (tipo) {
            case 'O': {
                int id;
                double x, y, largura;

                if (std::cin >> id >> x >> y >> largura)
                    cena.adicionarObjeto(Objeto(id, x, y, largura));

                break;
            }
            case 'M':{
                int id, tempo;
                double x, y;

                if (std::cin >> tempo >> id >> x >> y)
                    cena.movimentarObjeto(id, x, y);

                break;
            }
            case 'C': {
                int tempo;

                if (std::cin >> tempo) {
                    try {
                        cena.setTempo(tempo);
                        cena.gerar();
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