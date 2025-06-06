#ifndef PILA_H
#define PILA_H

#include <string>
using namespace std;

const int MAX_PILA = 100;

class Pila {
private:
    string elementos[MAX_PILA];
    int tope;

public:
    Pila();

    void apilar(const string& valor);
    string desapilar();
    string cima() const;
    bool vacia() const;
    bool llena() const;
};

#endif
