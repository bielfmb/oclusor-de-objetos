#ifndef MODULO1_INTERVALO_HPP
#define MODULO1_INTERVALO_HPP


struct Intervalo {
    double inicio;
    double fim;

    Intervalo& operator = (const Intervalo& intervalo) {
        this->inicio = intervalo.inicio;
        this->fim = intervalo.fim;

        return *this;
    }
};


#endif