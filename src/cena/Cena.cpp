#include "cena/Cena.hpp"


Cena::Cena() : _tempo(0), _quantObjetos(0), _naCena(0) {}

void Cena::adicionarObjeto(Objeto objeto) {
    if (_quantObjetos < this->_MAX_TAM) {
        this->_objetos[_quantObjetos] = objeto;
        _quantObjetos++;
    } else {
        throw std::out_of_range("A lista atingiu o tamanho máximo de " 
                                + std::to_string(this->_MAX_TAM)
                                + " objetos.");
    }
}

void Cena::movimentarObjeto(int id, double x, double y) {
    for (int i = 0; i < this->_quantObjetos; i++)
        if (this->_objetos[i].getId() == id) {
            this->_objetos[i].movimentar(x, y);
            return;
        }
}

void Cena::gerar() {
    Intervalo objeto;

    if (this->_quantObjetos <= 0) 
        throw std::logic_error("Não é possível criar uma cena sem objetos.");

    this->_quickSort(0, this->_quantObjetos - 1, this->_objetos, this->_getKeyY);

    // NOTA: Inicializa a cena com o objeto que aparece primeiro no eixo y
    // (não pode ser ocluído).
    this->_cena[0] = this->_objetos[0].getIntervalo();
    this->_naCena = 1;

    for (int i = 1; i < this->_quantObjetos; i++) {
        objeto = this->_objetos[i].getIntervalo();
        this->_calcularOclusao(&objeto, 0);
    }
}

void Cena::imprimir() {
    if (this->_quantObjetos <= 0) 
        throw std::logic_error("Não é possível imprimir uma cena sem objetos.");

    this->_quickSort(0, this->_naCena - 1, this->_cena, this->_getKeyId);

    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < this->_naCena; i++) {
        std::cout << "S "
                << this->_tempo << " "
                << this->_cena[i].id << " "
                << this->_cena[i].inicio << " "
                << this->_cena[i].fim << std::endl;
    }
}

void Cena::setTempo(int tempo) {
    if (tempo < 0)
        throw std::logic_error("Não é possível gerar uma cena em um "
                                "instante de tempo negativo.");
    
    this->_tempo = tempo; 
}


double Cena::_getKeyId(Intervalo* inter) {
    // IMPORTANTE: O fator precisa ser maior que o valor do inicio do segmento,
    // a fim de garantir que um valor entre 0 e 1 seja adicionado à chave;
    const double FATOR = 100000.0; 

    return (double)inter->id + (inter->inicio / FATOR);
}

double Cena::_getKeyY(Objeto* objeto) { return objeto->getY(); }

void Cena::_calcularOclusao(Intervalo* ocluido, int verificados) {
    Intervalo* o = ocluido;

    // CASO BASE: intervalo inválido
    if (o->inicio >= o->fim) return;

    for (int i = verificados; i < this->_naCena; i++) {
        // CASO 1: Ocluido termina antes do começo do ocluidor
        if (o->fim <= this->_cena[i].inicio)
            break;

        // CASO 2: Ocluido dentro do intervalo do ocluidor
        if (o->inicio >= this->_cena[i].inicio && o->fim <= this->_cena[i].fim)
            return;

        // CASO 3: Parte esquerda do ocluido toda dentro do intervalo do ocluidor
        if(o->inicio > this->_cena[i].inicio && o->inicio < this->_cena[i].fim)
            o->inicio = this->_cena[i].fim;

        // CASO 4: Parte direita do ocluido toda dentro do intervalo do ocluidor
        if(o->fim > this->_cena[i].inicio && o->fim < this->_cena[i].fim)
            o->fim = this->_cena[i].inicio;

        // CASO 5: Ocluidor totalmente dentro do intervalo do ocluido
        if (this->_cena[i].inicio >= o->inicio && this->_cena[i].fim <= o->fim) {
            Intervalo esquerda = {o->id, o->inicio, this->_cena[i].inicio};
            Intervalo direita = {o->id, this->_cena[i].fim, o->fim};

            this->_inserirNaCena(&esquerda);
            this->_calcularOclusao(&direita, i);
            
            return;
        }
    }

    this->_inserirNaCena(o);
}

void Cena::_inserirNaCena(Intervalo* inter) {
    if (this->_naCena >= _MAX_TAM * 10)
        throw std::out_of_range("Lista de intervalos excedeu o tamanho máximo de " 
                                + std::to_string(this->_MAX_TAM * 10)
                                + " elementos.");

    int i = this->_naCena - 1;

    while (( i >= 0 ) && (inter->inicio < this->_cena[i].inicio)) {
        this->_cena[i + 1] = this->_cena[i];
        i--;
    }

    this->_cena[i + 1] = *inter;
    this->_naCena++;
}