#include "modulo1/Objeto.hpp"


Objeto::Objeto(int id, double x, double y, double largura) 
    : _id(id),
    _x(x),
    _y(y),
    _largura(largura) {

    this->_calcularIntervalo(x);
}

Objeto::Objeto() { this->_id = -1; }

void Objeto::movimentar(double x, double y) {
    this->_x = x;
    this->_y = y;

    this->_calcularIntervalo(x);
}

Objeto& Objeto::operator = (const Objeto& objeto) {
    this->_id = objeto._id;
    this->_x = objeto._x;
    this->_y = objeto._y;
    this->_largura = objeto._largura;
    this->_intervalo = objeto._intervalo;

    return *this;
}

int Objeto::getId() { return this->_id; }

double Objeto::getX() { return this->_x; }

double Objeto::getY() { return this->_y; }

Intervalo Objeto::getIntervalo() { return this->_intervalo; }


void Objeto::_calcularIntervalo(double x) {
    this->_intervalo.id = this->_id;

    // EXEMPLO: x = 5, largura = 4.
    // inicio = 5 - 2 = 3, fim = 5 + 2 = 7
    // Logo, o intervalo é (3, 7), com 4 de tamanho e centro em 5.
    this->_intervalo.inicio = x - (this->_largura/2.00);
    this->_intervalo.fim = x + (this->_largura/2.00);
}