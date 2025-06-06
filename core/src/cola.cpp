#include "cola.h"

Cola::Cola() {
    frente = 0;
    final = 0;
}

void Cola::encolar(const string& valor) {
    if (!llena()) {
        elementos[final] = valor;
        final = (final + 1) % MAX_COLA;
    }
}

string Cola::desencolar() {
    if (!vacia()) {
        string valor = elementos[frente];
        frente = (frente + 1) % MAX_COLA;
        return valor;
    }
    return "";
}

string Cola::primero() const {
    if (!vacia()) {
        return elementos[frente];
    }
    return "";
}

bool Cola::vacia() const {
    return frente == final;
}

bool Cola::llena() const {
    return (final + 1) % MAX_COLA == frente;
}
