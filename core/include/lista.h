#ifndef LISTA_H
#define LISTA_H

#include <string>
using namespace std;

const int MAX_LISTA = 100;

class Lista {
private:
    string elementos[MAX_LISTA];
    int cantidad;

public:
    Lista();

    void agregar(const string& valor);
    string obtener(int indice) const;
    int tamano() const;
    void limpiar();
    bool estaVacia() const;
};

#endif
