#include "modulo1/Cena.hpp"


Cena::Cena(int tempo, Objeto* objetos, int nObjetos) 
            :  _tempo(tempo),
                _quantObjetos(0), 
                _objetosNaCena(0) {

    for (int i = 0; i < nObjetos; i++)
        this->adicionarObjeto(objetos[i]);
}

void Cena::adicionarObjeto(Objeto objeto) {
    if (_quantObjetos < this->_MAX_TAM) {
        this->_objetos[_quantObjetos] = objeto;
        _quantObjetos++;
    }
}

void Cena::gerarCena() {
    Objeto aux;

    this->_quickSort(0, this->_quantObjetos - 1, this->_objetos, this->POR_Y);

    for (int i = 0; i < this->_quantObjetos; i++) {
        aux = this->_objetos[i];

        if (this->_objetosNaCena > 0)
            this->_calcularOclusao(&aux);

        if (aux.getInicio() < aux.getFim()) {
            this->_cena[this->_objetosNaCena] = aux;
            this->_objetosNaCena++;
        }
    }
}

void Cena::movimentarObjeto(int id, int x, int y) {
    if (id <= this->_quantObjetos)
        this->_objetos[id].movimentar(x, y);
}

void Cena::imprimir() {
    this->_quickSort(0, this->_objetosNaCena - 1, this->_cena, this->POR_ID);

    for (int i = 0; i < this->_objetosNaCena; i++) {
        std::cout << std::fixed << std::setprecision(2);

        std::cout << "S "
                  << this->_tempo << " "
                  << this->_cena[i].getId() << " " 
                  << this->_cena[i].getInicio() << " " 
                  << this->_cena[i].getFim() 
                  << std::endl;
    }
}

Objeto* Cena::getObjetos() { return this->_objetos; }


void Cena::_calcularOclusao(Objeto* objeto) {
    Objeto ocluidor;

    for (int i = 0; i < this->_objetosNaCena; i++) {
        ocluidor = this->_cena[i];

        if (!ocluidor.estaNoIntervalo(*objeto)) 
            continue;

        if (objeto->getFim() > ocluidor.getInicio())
            objeto->setFim(ocluidor.getInicio()); 

        if (objeto->getInicio() < ocluidor.getFim())
            objeto->setInicio(ocluidor.getFim());
            
        if (objeto->getInicio() >= objeto->getFim())
            return;
    }
}

void Cena::_particao(int esq, int dir, int* i, int* j, Objeto* objetos, _CriterioOrdenacao criterio) {
    Objeto x;

    *i = esq; 
    *j = dir;

    // NOTA: se há mais de 3 elementos na particao, escolhe o pivô como a mediana
    // entre 3 objetos para evitar o pior caso do QuickSort
    if (dir - esq >= 3) {
        int idPivo = this->_calcularPivo(*i,
                                        (*i + *j)/2,
                                        *j,
                                        objetos,
                                        criterio); 
        x = objetos[idPivo];
    }
    else x = objetos[*i]; // se há menos, o pivô é o primeiro elemento

    do {
        if (criterio == this->POR_Y) {
            while (x.getY() > objetos[*i].getY()) (*i)++;
            while (x.getY() < objetos[*j].getY()) (*j)--;
        }

        else if (criterio == this->POR_ID) {
            while (x.getId() > objetos[*i].getId()) (*i)++;
            while (x.getId() < objetos[*j].getId()) (*j)--;
        }

        if (*i <= *j) {
            this->_trocar(*i, *j, objetos);
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

void Cena::_quickSort(int esq, int dir, Objeto* objetos, _CriterioOrdenacao criterio) {
    int i, j;
    this->_particao(esq, dir, &i, &j, objetos, criterio);

    if (esq < j) this->_quickSort(esq, j, objetos, criterio);
    if (i < dir) this->_quickSort(i, dir, objetos, criterio);
}

void Cena::_trocar(int x, int y, Objeto* objetos) {
    Objeto aux = objetos[x];
    objetos[x] = objetos[y];
    objetos[y] = aux;
}

int Cena::_calcularPivo(int a, int b, int c, Objeto* objetos, _CriterioOrdenacao criterio) {
    double x, y, z;

    if (criterio == this->POR_Y) {
        x = objetos[a].getY();
        y = objetos[b].getY();
        z = objetos[c].getY();
    }
    else if (criterio == this->POR_ID) {
        x = objetos[a].getId();
        y = objetos[b].getId();
        z = objetos[c].getId();        
    }

    if ((y >= x && x <= z) || (z <= x && x >= y)) return a;
    if ((x >= y && y <= z) || (z >= y && y <= x)) return b;
    return c;
}