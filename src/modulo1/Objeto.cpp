#include "modulo1/Objeto.hpp"


Objeto::Objeto(int id, double x, double y, double largura) 
    : _quantIntervalos(0),
      _id(id),
      _x(x),
      _y(y),
      _largura(largura) {

    this->_adicionarIntervalo(x);
}

Objeto::Objeto() { this->_id = -1; }

void Objeto::movimentar(double x, double y) {
    this->_x = x;
    this->_y = y;

    for (int i = 0; i < this->_quantIntervalos; i++)
        this->_atualizarIntervalo(i, x);
}

void Objeto::_adicionarIntervalo(double x) {
    this->_intervalos[this->_quantIntervalos].inicio = x - (this->_largura/2.00);
    this->_intervalos[this->_quantIntervalos].fim = x + (this->_largura/2.00);

    this->_quantIntervalos++;
}

void Objeto::_atualizarIntervalo(int pos, double x){
    if (pos >= this->_quantIntervalos) return;

    this->_intervalos[pos].inicio = x - (this->_largura/2.00);
    this->_intervalos[pos].fim = x + (this->_largura/2.00);
}

void Objeto::_removerIntervalo(int pos, double x) {
    if (pos >= this->_quantIntervalos) return;

    this->_quantIntervalos--;

    for (int i = pos; i < this->_quantIntervalos; i++) {
        this->_intervalos[i].inicio = this->_intervalos[i + 1].inicio;
        this->_intervalos[i].fim = this->_intervalos[i + 1].fim;
    }
}

Objeto& Objeto::operator = (const Objeto& objeto) {
    this->_id = objeto._id;
    this->_x = objeto._x;
    this->_y = objeto._y;
    this->_largura = objeto._largura;
    this->_quantIntervalos = objeto._quantIntervalos;

    for (int i = 0; i < objeto._quantIntervalos; i++)
        this->_intervalos[i] = objeto._intervalos[i];

    return *this;
}

int Objeto::getQuantIntervalos() { return this->_quantIntervalos; }

void Objeto::setQuantIntervalos(int quant) { this->_quantIntervalos = quant; }

int Objeto::getId() { return this->_id; }

double Objeto::getX() { return this->_x; }

double Objeto::getY() { return this->_y; }

Intervalo* Objeto::getIntervalos() { return this->_intervalos; }
