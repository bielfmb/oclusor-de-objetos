#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <iostream>
#include "cena/Objeto.hpp"
#include "cena/Cena.hpp"


class Sistema {
    public:
        /**
         * @brief Orquestra a execução do oclusor de objetos
         * 
         * @details Através de funções internas, realiza as operações
         * de adição ou movimentação de objetos, ou ainda de geração
         * de cenas, a depender do comando de entrada.
         */
        void executar();
    
    private:
        /**
         * @brief Adiciona um objeto à cena específica
         * 
         * @param cena Instância de Cena que receberá o objeto
         */
        void _processarObj(Cena& cena);

        /**
         * @brief Movimenta um objeto da cena.
         * 
         * @param cena Instância de Cena que terá um objeto movimentado
         */
        void _processarMovimentacao(Cena& cena);

        /**
         * @brief Gera e imprime uma cena.
         * 
         * @param cena Instância de Cena que será gerada
         */        
        void _processarGeracaoCena(Cena& cena);
};

#endif