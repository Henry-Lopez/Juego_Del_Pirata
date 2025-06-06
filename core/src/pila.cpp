#include "pila.h"

Pila::Pila() {
    tope = -1;
}

void Pila::apilar(const string& valor) {
    if (!llena()) {
        tope++;
        elementos[tope] = valor;
    }
}

string Pila::desapilar() {
    if (!vacia()) {
        string valor = elementos[tope];
        tope--;
        return valor;
    }
    return "";
}

string Pila::cima() const {
    if (!vacia()) {
        return elementos[tope];
    }
    return "";
}

bool Pila::vacia() const {
    return tope == -1;
}

bool Pila::llena() const {
    return tope == MAX_PILA - 1;
}
