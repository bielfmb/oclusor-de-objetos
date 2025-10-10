#ifndef MODULO1_INTERVALO_HPP
#define MODULO1_INTERVALO_HPP


/**
 * @struct Intervalo
 * 
 * @brief Representa um segmento ocupado por um objeto.
 */
struct Intervalo {
    int id; //!< Identificador do objeto que o intervalo pertence.
    double inicio; //!< Ponto mais à esquerda do intervalo.
    double fim; //!< Ponto mais à direita do intervalo.
};


#endif