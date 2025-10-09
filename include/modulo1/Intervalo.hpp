#ifndef MODULO1_INTERVALO_HPP
#define MODULO1_INTERVALO_HPP


/**
 * @struct Intervalo
 * 
 * @brief Representa um segmento ocupado por um objeto.
 */
struct Intervalo {
    double inicio; //!< Ponto mais à esquerda do intervalo.
    double fim; //!< Ponto mais à direita do intervalo.

    Intervalo& operator = (const Intervalo& intervalo) {
        this->inicio = intervalo.inicio;
        this->fim = intervalo.fim;

        return *this;
    }
};


#endif