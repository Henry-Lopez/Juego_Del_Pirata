#include "lista.h"

Lista::Lista() {
    cantidad = 0;
}

void Lista::agregar(const string& valor) {
    if (cantidad < MAX_LISTA) {
        elementos[cantidad] = valor;
        cantidad++;
    }
}

string Lista::obtener(int indice) const {
    if (indice >= 0 && indice < cantidad) {
        return elementos[indice];
    }
    return "";
}

int Lista::tamano() const {
    return cantidad;
}

void Lista::limpiar() {
    cantidad = 0;
}

bool Lista::estaVacia() const {
    return cantidad == 0;
}
