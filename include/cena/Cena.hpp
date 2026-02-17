#ifndef CENA_CENA_HPP
#define CENA_CENA_HPP

#include <iostream>
#include <iomanip>
#include "cena/Objeto.hpp"

/**
 * @class Cena
 * 
 * @brief Representação de uma série de objetos em um dado momento do jogo.
 */
class Cena {
    public:
        /**
         * @brief Construtor padrão de cena.
         * 
         * @details Utilizado apenas para setar os valores de tempo e das
         * quantidades de elementos nos vetores de objetos e intervalos da
         * cena no momento que uma cena é instanciada.
         */
        Cena();
        
        /**
         * @brief Insere um objeto para ser processado antes de entrar
         * em cena.
         * 
         * @param objeto O elemento a ser inserido na lista de objetos.
         * 
         * @details Este método também é utilizado pelo construtor de cena,
         * a fim de garantir que o objeto passado com argumento pode ser
         * usado na lista de objetos guardados por esta classe.
         */
        void adicionarObjeto(Objeto objeto);

        /**
         * @brief Procura e move um objeto tanto no eixo x, quanto no y.
         * 
         * @param id Qual objeto deve ser movido
         * @param x Novo centro do objeto no eixo horizontal.
         * @param y Nova posição do objeto no eixo vertical.
         */
        void movimentarObjeto(int id, double x, double y);

        /**
         * @brief Reorganiza o vetor de objetos para conter apenas os 
         * elementos que vão aparecer na cena final.
         */
        void gerar();

        /**
         * @brief Formata a cena final para impressão no terminal.
         * 
         * @details Mostra no terminal os atributos dos elementos que 
         * estão no vetor de intervalos, seguindo o formato:
         * S <tempo> <inicio> <fim>.
         */
        void imprimir();

        void setTempo(int tempo);

    private:
        static const int _MAX_TAM = 100; //!< Define o tamanho máximo do
                                         // vetor de objetos.

        int _tempo; //!< Instante em que a cena será gerada.

        int _quantObjetos; //!< Número de objetos válidos a processar.

        int _naCena; //!< Número de intervalos válidos na cena.

        Objeto _objetos[_MAX_TAM]; //!< Lista de objetos a serem processados

        Intervalo _cena[_MAX_TAM * 10]; //!< Lista de intervalos a renderizar


        /**
         * @brief Utilizada como parâmetro no QuickSort para ordenar um array
         * de intervalos pelo id. 
         * 
         * @details Retorna uma chave composta para o QuickSort, garantindo  
         * que a ordenação por inicio funcione como critério secundário de 
         * desempate para intervalos com mesmo id de objeto.
         * 
         * @param inter Intervalo a se retornar o id.
         * 
         * @return O identificador do objeto que aquele intervalo pertence.
         */
        static double _getKeyId(Intervalo* inter);

        /**
         * @brief Utilizada como parâmetro no QuickSort para ordenar um array
         * de objetos pela profundidade. 
         * 
         * @param objeto Objeto a se retornar a posição no eixo y.
         * 
         * @return A posição do objeto no eixo vertical.
         */        
        static double _getKeyY(Objeto* objeto);

        /**
         * @brief Percorre a lista de intervalos na cena e verifica se 
         * algum oclui o objeto passado como parâmetro.
         * 
         * @details Se um elemento na cena divide o objeto em 2 partes, o
         * pedaço à esquerda é adicionado à cena e o que está à direita
         * é comparado aos próximos elementos recursivamente.
         * 
         * @param ocluido Intervalo a se verificar se há interseção com os 
         * elementos já na cena.
         * @param verificados Índice do primeiro intervalo a ser usado na 
         * verificação, usado para otimizar a recursão.
         */
        void _calcularOclusao(Intervalo* ocluido, int verificados);

        /**
         * @brief Insere um intervalo de forma ordenada na cena, do menor 
         * início para o maior.
         * 
         * @param inter O intervalo a ser inserido.
         */
        void _inserirNaCena(Intervalo* inter);

        /**
         * @brief Ordena a lista de objetos passada como parâmetro de
         * acordo com uma chave específica.
         * 
         * @param esq Posição do elemento inicial da sub-lista.
         * @param dir Posição do elemento final da sub-lista.
         * @param lista Lista de a ser ordenada.
         * @param get Função que retorna por qual parâmetro a lista deve 
         * ser ordenada.
         */
        template <typename T, typename GetKey>
        void _quickSort(int esq, int dir, 
                      T* lista, GetKey get) 
        {
            int i, j;
            this->_particao(esq, dir, &i, &j, lista, get);

            if (esq < j) this->_quickSort(esq, j, lista, get);
            if (i < dir) this->_quickSort(i, dir, lista, get);
        }

        /**
         * @brief Particiona a sub-lista de forma genérica, preparando-a para
         * o próximo passo recursivo do QuickSort.
         * 
         * @param esq Posição do elemento inicial da sub-lista.
         * @param dir Posição do elemento final da sub-lista.
         * @param i Ponteiro para o índice da esquerda (que será retornado).
         * @param j Ponteiro para o índice da direita (que será retornado).
         * @param lista Lista a ser particionada.
         * @param get Função que retorna a chave de ordenação do elemento.
         */
        template <typename T, typename GetKey>
        void _particao(int esq, int dir, int* i, int* j, 
                     T* lista, GetKey get) 
        {
            int pivo;

            *i = esq; 
            *j = dir;

            // NOTA: se há mais de 3 elementos na particao, escolhe o pivô como 
            // a mediana entre 3 objetos para evitar o pior caso do QuickSort
            if (dir - esq >= 3) {
                pivo = this->_calcularPivo(*i,
                                            (*i + *j)/2,
                                            *j,
                                            lista,
                                            get); 
            }
            else pivo = *i; // se há menos, o pivô é o primeiro elemento

            do {
                while (get(&lista[pivo]) > get(&lista[*i])) (*i)++;
                while (get(&lista[pivo]) < get(&lista[*j])) (*j)--;

                if (*i <= *j) {
                    T aux = lista[*i];
                    lista[*i] = lista[*j];
                    lista[*j] = aux;

                    (*i)++; (*j)--;
                }
            } while (*i <= *j);
        }

        /**
         * @brief Calcula o índice do pivô utilizando uma mediana de três
         * para evitar o pior caso de O(n^2) do QuickSort.
         * 
         * @param a Índice do primeiro elemento.
         * @param b Índice do elemento central.
         * @param c Índice do último elemento.
         * @param lista Lista contendo os elementos.
         * @param get Função que retorna a chave de ordenação.
         * 
         * @return O índice do elemento que representa a mediana.
         */
        template <typename T, typename GetKey>
        int _calcularPivo(int a, int b, int c, T* lista, GetKey get) {
            double x = get(&lista[a]);
            double y = get(&lista[b]);
            double z = get(&lista[c]);

            if ((x <= y && y <= z) || (z <= y && y <= x)) return b;
            if ((y <= x && x <= z) || (z <= x && x <= y)) return a;
            return c;
        }

};

#endif