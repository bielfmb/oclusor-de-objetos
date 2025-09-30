#ifndef MODULO1_CENA_HPP
#define MODULO1_CENA_HPP

#include <iostream>
#include <iomanip>
#include "modulo1/Objeto.hpp"


class Cena {
    public:
        Cena(int tempo, Objeto* objetos, int nObjetos);

        void adicionarObjeto(Objeto objeto);
        void gerarCena();
        void movimentarObjeto(int id, int x, int y);
        void imprimir();

        Objeto* getObjetos();

    private:
        enum _CriterioOrdenacao {
            POR_ID,
            POR_Y
        };

        static const int _MAX_TAM = 100;
        int _tempo;
        int _quantObjetos;
        int _objetosNaCena;
        Objeto _objetos[_MAX_TAM];
        Objeto _cena[_MAX_TAM];

        void _calcularOclusao(Objeto* objeto);

        void _particao(int esq, 
                       int dir, 
                       int* i, 
                       int* j, 
                       Objeto *objetos,
                       _CriterioOrdenacao criterio);

        void _quickSort(int esq, 
                        int dir, 
                        Objeto *objetos, 
                        _CriterioOrdenacao criterio);

        int _calcularPivo(int x, 
                          int y,
                          int z, 
                          Objeto *objetos, 
                          _CriterioOrdenacao criterio);

        void _trocar(int x, int y, Objeto *objetos);

};

#endif