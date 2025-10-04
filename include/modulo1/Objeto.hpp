#ifndef MODULO1_OBJETO_HPP
#define MODULO1_OBJETO_HPP

#include "modulo1/Intervalo.hpp"


class Objeto {
    public:
        Objeto(int id, double x, double y, double largura);
        Objeto();

        void movimentar(double x, double y);
        void _adicionarIntervalo(double x);
        void _atualizarIntervalo(int pos, double x);

        Objeto& operator = (const Objeto& objeto);

        int getQuantIntervalos();
        void setQuantIntervalos(int quant);
        int getId();
        double getX();
        double getY();
        Intervalo* getIntervalos();

    private:
        static const int _MAX_TAM = 10;
        int _quantIntervalos;
        int _id;
        double _x, _y;
        double _largura;
        
        // NOTA: lista de possiveis intervalos do objeto
        Intervalo _intervalos[_MAX_TAM];
        
};

#endif