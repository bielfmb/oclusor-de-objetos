#include "modulo1/Cena.hpp"


Cena::Cena(int tempo, Objeto* objetos, int quantObjetos) 
            :  _tempo(tempo),
                _quantObjetos(0),
                _naCena(0)
{
    if (quantObjetos < 0 || quantObjetos > this->_MAX_TAM) 
        throw std::out_of_range("A lista deve ter um tamanho entre 0 e " 
                                + std::to_string(this->_MAX_TAM));

    for (int i = 0; i < quantObjetos; i++)
        this->adicionarObjeto(objetos[i]);
}

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

void Cena::gerarCena() {
    Intervalo objeto;

    if (this->_quantObjetos <= 0) 
        throw std::logic_error("Não é possível criar uma cena sem objetos.");

    if (this->_naCena <= 0){
        this->_cena[0] = this->_objetos[0].getIntervalo();
        this->_naCena = 1;
    }

    this->_quickSort(0, this->_quantObjetos - 1, this->_objetos, this->_retornarKeyY);

    for (int i = 0; i < this->_quantObjetos; i++) {
        objeto = this->_objetos[i].getIntervalo();
        this->_calcularOclusao(&objeto, 0);
    }
}

void Cena::imprimir() {
    if (this->_quantObjetos <= 0) 
        throw std::logic_error("Não é possível imprimir uma cena sem objetos.");

    this->_quickSort(0, this->_naCena - 1, this->_cena, this->_retornarKeyId);

    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < this->_naCena; i++) {
        std::cout << "S "
                << this->_tempo << " "
                << this->_cena[i].id << " "
                << this->_cena[i].inicio << " "
                << this->_cena[i].fim << std::endl;
    }
}


void Cena::_calcularOclusao(Intervalo* ocluido, int verificados) {
    Intervalo* o = ocluido;

    if (o->inicio >= o->fim) return;

    for (int i = verificados; i < this->_naCena; i++) {
        if (o->fim <= this->_cena[i].inicio)
            break;

        if (o->inicio >=this->_cena[i].inicio && o->fim <= this->_cena[i].fim)
            return;

        if(o->inicio > this->_cena[i].inicio && o->inicio < this->_cena[i].fim)
            o->inicio =this->_cena[i].fim;

        if(o->fim > this->_cena[i].inicio && o->fim < this->_cena[i].fim)
            o->fim = this->_cena[i].inicio;

        if (this->_cena[i].inicio >= o->inicio && this->_cena[i].fim <= o->fim) {
            Intervalo parte1 = {o->id, o->inicio, this->_cena[i].inicio};
            Intervalo parte2 = {o->id, this->_cena[i].fim, o->fim};

            this->_calcularOclusao(&parte1, i);
            this->_calcularOclusao(&parte2, i);
            
            return;
        }
    }
        
    int i = this->_naCena - 1;

    while (( i >= 0 ) && (o->inicio < this->_cena[i].inicio)) {
        this->_cena[i + 1] = this->_cena[i];
        i--;
    }

    this->_cena[i + 1] = *o;
    this->_naCena++;
}

double Cena::_retornarKeyId(Intervalo* inter) {
    const double FATOR = 100000.0;
    
    return (double)inter->id + (inter->inicio / FATOR);
}

double Cena::_retornarKeyY(Objeto* objeto) {
    return objeto->getY();
}
