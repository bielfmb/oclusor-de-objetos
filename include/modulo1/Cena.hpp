#ifndef MODULO1_CENA_HPP
#define MODULO1_CENA_HPP

#include <iostream>
#include <iomanip>
#include "modulo1/Objeto.hpp"

/**
 * @class Cena
 * 
 * @brief Representação de uma série de objetos em um dado momento do jogo.
 */
class Cena {
    public:
        /**
         * @brief Construtor da cena.
         * 
         * @param tempo Instante da renderização da cena
         * @param objetos Lista dos objetos a serem processados para 
         * aparecer na cena.
         * @param quantObjetos Número dos objetos na lista passada. 
         */
        Cena(int tempo, Objeto* objetos, int quantObjetos);
        
        /**
         * @brief Insere um objeto para ser processado antes de entrar
         * em cena.
         * 
         * @param objeto O elemento a ser inserido na lista de objetos.
         * 
         * @details Este método também é utilizado pelo construtor de cena,
         * a fim de garantir que o ponteiro passado com argumento pode ser
         * usado na lista de objetos guardados por esta classe.
         */
        void adicionarObjeto(Objeto objeto);

        /**
         * @brief Reorganiza o vetor de objetos para conter apenas os 
         * elementos que vão aparecer na cena final
         * 
         * 
         */
        void gerarCena();

        /**
         * @brief Formata a cena final para a impressão no terminal.
         * 
         * @details Mostra no terminal os atributos do elementos que 
         * estão no vetor de objetos, seguindo o formato:
         * S <tempo> <inicio> <fim>.
         */
        void imprimir();


    private:
        /**
         * @brief Descreve por qual atributo um vetor deve ser organizado. 
         */
        enum _CriterioOrdenacao {
            POR_ID, //!< O array deve ser organizado pelo id do objeto.
            POR_Y //!< O vetor deve ser ordenado pela profundidade.
        };

        static const int _MAX_TAM = 100; //!< Define o tamanho máximo do
                                         // vetor de objetos.

        int _tempo; //!< Instante em que a cena será gerada.

        int _quantObjetos; //!< Número de objetos válidos na cena.

        Objeto _objetos[_MAX_TAM]; //!< Lista de objetos a serem processados

        /**
         * @brief Percorre a lista de intervalos de dois objetos e, se
         * necessário, oclui o que está mais atrás.
         * 
         * @details 
         */
        void _calcularOclusao(Objeto& frente, Objeto& tras);

        /**
         * @brief Ordena a lista de objetos passada como parâmetro de
         * acordo com um critério específico.
         * 
         * @param esq Posição do elemento inicial da sub-lista.
         * @param dir Posição do elemento final da sub-lista.
         * @param objetos Lista de objetos a ser ordenada.
         * @param criterio Atributo pelo qual a lista será organizada.
         */
        void _quickSort(int esq, 
                        int dir, 
                        Objeto *objetos, 
                        _CriterioOrdenacao criterio);

        /**
         * @brief 
         */
        void _particao(int esq, int dir, 
                       int* i, int* j, 
                       Objeto *objetos,
                       _CriterioOrdenacao criterio);

        int _calcularPivo(int x, int y, int z, 
                          Objeto *objetos, 
                          _CriterioOrdenacao criterio);

        void _trocar(int x, int y, Objeto *objetos);

};

#endif