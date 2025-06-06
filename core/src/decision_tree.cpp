#include "decision_tree.h"

// Constructor del nodo
NodoDecision::NodoDecision(const string& k, const string& v) {
    clave = k;
    valor = v;
    izquierda = nullptr;
    derecha = nullptr;
}

// Constructor del árbol
DecisionTree::DecisionTree() {
    raiz = nullptr;
}

// Destructor del árbol
DecisionTree::~DecisionTree() {
    liberar(raiz);
}

// Construye un árbol de ejemplo fijo
void DecisionTree::construirArbolEjemplo() {
    // Ejemplo simple: si la pista contiene "sol", es cueva; si no, es bosque.
    raiz = new NodoDecision("sol", "");

    raiz->izquierda = new NodoDecision("agua", "bosque");      // si no tiene "sol" pero tiene "agua"
    raiz->izquierda->izquierda = new NodoDecision("", "playa"); // si no tiene "agua" → playa
    raiz->izquierda->derecha = new NodoDecision("", "lago");   // si tiene "agua" → lago

    raiz->derecha = new NodoDecision("", "cueva");             // si contiene "sol"
}

// Función recursiva para interpretar la pista
string DecisionTree::interpretarRecursivo(NodoDecision* nodo, const string& pista) const {
    if (nodo == nullptr) return "desconocido";

    if (nodo->clave == "") return nodo->valor;

    // Si la pista contiene la palabra clave → derecha
    if (pista.find(nodo->clave) != string::npos) {
        return interpretarRecursivo(nodo->derecha, pista);
    } else {
        return interpretarRecursivo(nodo->izquierda, pista);
    }
}

// Punto de entrada para interpretar la pista completa
string DecisionTree::interpretarPista(const string& pista) const {
    return interpretarRecursivo(raiz, pista);
}

// Libera recursivamente memoria del árbol
void DecisionTree::liberar(NodoDecision* nodo) {
    if (nodo == nullptr) return;
    liberar(nodo->izquierda);
    liberar(nodo->derecha);
    delete nodo;
}
