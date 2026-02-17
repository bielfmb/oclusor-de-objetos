#include "Sistema.hpp"


void Sistema::executar() {
    Cena cena;

    char tipo;

    // NOTA: Loop é executado enquanto um caractere for inserido na entrada.
    while (std::cin >> tipo)
    {
        switch (tipo) {
            case 'O': 
                this->_processarObj(cena);
                break;

            case 'M':
                this->_processarMovimentacao(cena);
                break;

            case 'C': {
                this->_processarGeracaoCena(cena);
                break;
            }

        }
    }
}

void Sistema::_processarObj(Cena& cena) {
    int id;
    double x, y, largura;

    if (std::cin >> id >> x >> y >> largura) {
        try {
            cena.adicionarObjeto(Objeto(id, x, y, largura));
        }
        catch(std::exception& e) {
            std::cerr << "Erro ao adicionar: " << e.what() << std::endl;
        }
    }
}

void Sistema::_processarMovimentacao(Cena& cena) {
    int id, tempo;
    double x, y;

    if (std::cin >> tempo >> id >> x >> y)
        cena.movimentarObjeto(id, x, y);
}

void Sistema::_processarGeracaoCena(Cena& cena) {
    int tempo;

    if (std::cin >> tempo) {
        try {
            cena.setTempo(tempo);
            cena.gerar();
            cena.imprimir();
        }
        catch(std::exception& e) {
            std::cerr << "Erro na cena: " << e.what() << std::endl;
        }
    }          
}
