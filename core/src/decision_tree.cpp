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

void DecisionTree::construirArbolEjemplo() {
    raiz = new NodoDecision("mina", "");  // ➤ minas antiguas → ruinas
    raiz->derecha = new NodoDecision("", "ruinas");

    raiz->izquierda = new NodoDecision("ruina", "");
    raiz->izquierda->derecha = new NodoDecision("", "ruinas");

    raiz->izquierda->izquierda = new NodoDecision("pantano", "");
    raiz->izquierda->izquierda->derecha = new NodoDecision("", "pantano");

    raiz->izquierda->izquierda->izquierda = new NodoDecision("cueva", "");
    raiz->izquierda->izquierda->izquierda->derecha = new NodoDecision("", "cueva");

    raiz->izquierda->izquierda->izquierda->izquierda = new NodoDecision("fortaleza", "");
    raiz->izquierda->izquierda->izquierda->izquierda->derecha = new NodoDecision("", "templo");

    raiz->izquierda->izquierda->izquierda->izquierda->izquierda = new NodoDecision("ciudad", "");
    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->derecha = new NodoDecision("", "ciudad");

    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda = new NodoDecision("torre", "");
    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->derecha = new NodoDecision("", "torre");

    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda = new NodoDecision("jinetes", "");
    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->derecha = new NodoDecision("", "llanura");

    // 🌞 compatibilidad con pistas antiguas (isla del pirata)
    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda = new NodoDecision("sol", "");
    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->derecha = new NodoDecision("", "cueva");

    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda = new NodoDecision("agua", "");
    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->derecha = new NodoDecision("", "lago");

    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda = new NodoDecision("antiguas", "");
    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->derecha = new NodoDecision("", "ruinas");

    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda = new NodoDecision("altura", "");
    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->derecha = new NodoDecision("", "montana");

    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda = new NodoDecision("mapa", "");
    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->derecha = new NodoDecision("", "cima");

    // 🌲 default: bosque
    raiz->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda->izquierda = new NodoDecision("", "bosque");
}


// Recorre recursivamente el árbol para interpretar la pista
string DecisionTree::interpretarRecursivo(NodoDecision* nodo, const string& pista) const {
    if (nodo == nullptr) return "desconocido";
    if (nodo->clave == "") return nodo->valor;

    if (pista.find(nodo->clave) != string::npos) {
        return interpretarRecursivo(nodo->derecha, pista);
    } else {
        return interpretarRecursivo(nodo->izquierda, pista);
    }
}

// Punto de entrada
string DecisionTree::interpretarPista(const string& pista) const {
    return interpretarRecursivo(raiz, pista);
}

// Libera memoria
void DecisionTree::liberar(NodoDecision* nodo) {
    if (nodo == nullptr) return;
    liberar(nodo->izquierda);
    liberar(nodo->derecha);
    delete nodo;
}
