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
         * estão no vetor de intervalos, seguindo o formato:
         * S <tempo> <inicio> <fim>.
         */
        void imprimir();


    private:
        static const int _MAX_TAM = 100; //!< Define o tamanho máximo do
                                         // vetor de objetos.

        int _tempo; //!< Instante em que a cena será gerada.

        int _quantObjetos; //!< Número de objetos válidos na cena.

        Objeto _objetos[_MAX_TAM]; //!< Lista de objetos a serem processados

        Intervalo _cena[_MAX_TAM * 10]; //!< Lista da cena a ser renderizada

        int _naCena; //!< Número de intervalos válidos na cena.

        /**
         * @brief Percorre a lista de intervalos na cena e verifica se 
         * algum oclui o objeto passado como parâmetro.
         * 
         * @details Se um elemento na cena divide o objeto em 2 partes, esses
         * pedaços são comparados aos próximos elementos recursivamente.
         * 
         * @param ocluido Intervalo a se verificar se há interseção com os 
         * elementos já na cena.
         * @param verificados Quantidade de intervalos que já foram realizadas
         * as verificações, usado pricipalmente na recursão.
         */
        void _calcularOclusao(Intervalo* ocluido, int verificados);

        /**
         * @brief Utilizada como parâmetro no QuickSort para ordenar um array
         * de intervalos pelo id. 
         * 
         * @param inter Intervalo a se retornar o id.
         * 
         * @return O identificador do objeto que aquele intervalo pertence.
         */
        static double _retornarKeyId(Intervalo* inter);

        /**
         * @brief Utilizada como parâmetro no QuickSort para ordenar um array
         * de objetos pela profundidade. 
         * 
         * @param objeto Objeto a se retornar a posição no eixo y.
         * 
         * @return A posição do objeto no eixo vertical.
         */        
        static double _retornarKeyY(Objeto* objeto);

        /**
         * @brief Ordena a lista de objetos passada como parâmetro de
         * acordo com uma chave específico.
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

        template <typename T, typename GetKey>
        int _calcularPivo(int a, int b, int c, 
                                T* lista, GetKey get) 
        {
            double x = get(&lista[a]);
            double y = get(&lista[b]);
            double z = get(&lista[c]);

            if ((y >= x && x <= z) || (z <= x && x >= y)) return a;
            if ((x >= y && y <= z) || (z >= y && y <= x)) return b;
            return c;
        }

};

#endif