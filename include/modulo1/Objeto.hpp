#ifndef MODULO1_OBJETO_HPP
#define MODULO1_OBJETO_HPP

#include <iostream>
#include "modulo1/Intervalo.hpp"


 /**
  * @class Objeto
  * 
  * @brief Abstração de um objeto renderizável em cena.
  */
class Objeto {
    public:
        /**
         * @brief Construtor pricipal de Objeto.
         * 
         * @param id Identificador do objeto.
         * @param x Centro do objeto no eixo x.
         * @param y Posição do objeto no eixo y.
         * @param largura Tamanho do segmento.
         */
        Objeto(int id, double x, double y, double largura);

        /**
         * @brief Construtor vazio.
         * 
         * @details Utilizado para construir um objeto "nulo", a fim de
         * poder criar vetores de objetos sem a necessidade de inicializar
         * todas as posições. Define o id como -1, sinalizando que o
         * objeto não é válido.
         */
        Objeto();

        /**
         * @brief Move o objeto tanto no eixo x, quanto no y.
         * 
         * @param x Novo centro do segmento no eixo horizontal.
         * @param y Nova posição do segmento no eixo vertical.
         */
        void movimentar(double x, double y);

        /**
         * @brief Sobrescreve o operador de atribuição de Objeto.
         * 
         * @param objeto O objeto a ser atribuído a este.
         * 
         * @return O endereço do objeto que recebeu a atribuição.
         */
        Objeto& operator = (const Objeto& objeto);

        /**
         * @brief Getter do identificador do objeto.
         * 
         * @return Um inteiro que representa o identificador.
         */
        int getId();

        /**
         * @brief Getter do centro do segmento no eixo x.
         * 
         * @return O double que representa o centro do objeto.
         */
        double getX();

        /**
         * @brief Getter da posição do objeto no eixo y.
         * 
         * @return Um double com a profundidade do objeto. 
         */
        double getY();

        /**
         * @brief Getter do segmento ocupado pelo objeto.
         * 
         * @return Cópia do intervalo que o objeto preenche.
         */
        Intervalo getIntervalo();
        

    private:
        int _id; //!< Identificador do objeto.

        double _x, _y; //!< Centro do segmento no eixo x e posição dele
                       // no eixo y, respectivamente.

        double _largura; //!< Tamanho total do segmento, de uma ponta
                         // à outra.
        
        Intervalo _intervalo; //!< Segmento ocupado pelo objeto

        /**
         * @brief Método auxiliar para atualizar o intervalo do objeto
         * 
         * @param x Centro do segmento, utilizado para calcular o início
         * e o fim dele no eixo x a partir da largura.
         */        
        void _calcularIntervalo(double x);
        
};

#endif