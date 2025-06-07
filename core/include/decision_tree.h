#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include <string>
using namespace std;

// Nodo de un árbol binario para decisiones basadas en pistas
struct NodoDecision {
    string clave;      // palabra clave a evaluar
    string valor;      // ubicación sugerida si coincide
    NodoDecision* izquierda; // no coincide → seguir izquierda
    NodoDecision* derecha;   // coincide → seguir derecha

    NodoDecision(const string& k, const string& v);
};

class DecisionTree {
private:
    NodoDecision* raiz;

    string interpretarRecursivo(NodoDecision* nodo, const string& pista) const;
    void liberar(NodoDecision* nodo); // destructor recursivo

public:
    DecisionTree();
    ~DecisionTree();

    void construirArbolEjemplo(); // crea árbol fijo básico
    string interpretarPista(const string& pista) const; // analiza pista y retorna ubicación

    void mostrar() const;

};

#endif
