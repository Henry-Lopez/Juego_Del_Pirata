#ifndef COLA_H
#define COLA_H

#include <string>
using namespace std;

const int MAX_COLA = 100;

class Cola {
private:
    string elementos[MAX_COLA];
    int frente;
    int final;

public:
    Cola();

    void encolar(const string& valor);
    string desencolar();
    string primero() const;
    bool vacia() const;
    bool llena() const;
};

#endif
