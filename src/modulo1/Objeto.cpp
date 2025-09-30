#include "modulo1/Objeto.hpp"


Objeto::Objeto(int id, double x, double y, double largura) 
    : _id(id),
      _x(x),
      _y(y),
      _largura(largura) {

    this->_calcularIntervalo();
}

Objeto::Objeto() { this->_id = -1; }

void Objeto::movimentar(double x, double y) {
    this->_x = x;
    this->_y = y;

    this->_calcularIntervalo();
}

bool Objeto::estaNoIntervalo(Objeto objeto) {
    return (this->_inicio < objeto._fim && objeto._inicio < this->_fim);
}

Objeto& Objeto::operator = (const Objeto& objeto) {
    this->_id = objeto._id;
    this->_x = objeto._x;
    this->_y = objeto._y;
    this->_largura = objeto._largura;
    this->_inicio = objeto._x - (objeto._largura/2.00);
    this->_fim = objeto._x + (objeto._largura/2.00);      
    //this->_calcularIntervalo();

    return *this;
}

int Objeto::getId() { return this->_id; }

double Objeto::getX() { return this->_x; }

double Objeto::getY() { return this->_y; }

double Objeto::getInicio() { return this->_inicio; }

void Objeto::setInicio(double inicio) { this->_inicio = inicio; }

double Objeto::getFim() { return this->_fim; }

void Objeto::setFim(double fim) { this->_fim = fim; }

void Objeto::_calcularIntervalo() {
    this->_inicio = this->_x - (this->_largura/2.00);
    this->_fim = this->_x + (this->_largura/2.00);  
}