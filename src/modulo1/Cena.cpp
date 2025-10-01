#include "modulo1/Cena.hpp"


Cena::Cena(int tempo, Objeto* objetos, int nObjetos) 
            :  _tempo(tempo),
                _quantObjetos(0) {

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
    this->_quickSort(0, this->_quantObjetos - 1, this->_objetos, this->POR_Y);

    if (this->_quantObjetos <= 0) return; 

    for (int i = 0; i < this->_quantObjetos; i++) {
        for (int j = i + 1; j < this->_quantObjetos; j++){
            int inter = this->_objetos[j].getQuantIntervalos();

            this->_calcularOclusao(this->_objetos[j].getIntervalos(), 
                                   inter,
                                    this->_objetos[i].getIntervalos(), 
                                    this->_objetos[i].getQuantIntervalos()); 

            this->_objetos[j].setQuantIntervalos(inter);
        }        
    }
}

void Cena::movimentarObjeto(int id, int x, int y) {
    if (id <= this->_quantObjetos)
        this->_objetos[id].movimentar(x, y);
}

void Cena::imprimir() {
    Objeto o;
    Intervalo* inter;

    this->_quickSort(0, this->_quantObjetos - 1, this->_objetos, this->POR_ID);

    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < this->_quantObjetos; i++) {
        o = this->_objetos[i];
        inter = o.getIntervalos();
        for (int j = 0; j < o.getQuantIntervalos(); j++) {
            std::cout << "S "
                    << this->_tempo << " "
                    << o.getId() << " "
                    << inter[j].inicio << " "
                    << inter[j].fim << std::endl;
        }
    }
}

Objeto* Cena::getObjetos() { return this->_objetos; }


void Cena::_calcularOclusao(
    Intervalo* A, int& quantA,
    Intervalo* B, int quantB   
) {
    Intervalo currA;
    int iA = 0, iB = 0, iWA = 0;

    while (iA < quantA) {
        currA = A[iA];

        // Avança B até que possa afetar A
        while (iB < quantB && B[iB].fim <= currA.inicio) {
            iB++;
        }

        double inicio = currA.inicio;

        while (iB < quantB && B[iB].inicio < currA.fim) {
            if (B[iB].inicio > inicio) {
                Intervalo sobra = {inicio, B[iB].inicio};
                A[iWA++] = sobra;
            }
            inicio = (inicio > B[iB].fim) ? inicio : B[iB].fim;

            if (inicio >= currA.fim) break;
            iB++;
        }

        if (inicio < currA.fim) {
            Intervalo sobra = {inicio, currA.fim};
            A[iWA++] = sobra;
        }

        iA++;
    }

    quantA = iWA;
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