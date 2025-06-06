#ifndef GRAFO_H
#define GRAFO_H

#include <string>
using namespace std;

const int MAX_NODOS = 100;

struct Arista {
    string destino;
    int costo;
    Arista* siguiente;

    Arista(const string& dest, int c, Arista* sig = nullptr)
        : destino(dest), costo(c), siguiente(sig) {}
};

struct Nodo {
    string nombre;
    string pista;
    Arista* adyacentes;

    Nodo() : nombre(""), pista(""), adyacentes(nullptr) {}
};

class Grafo {
private:
    Nodo nodos[MAX_NODOS];
    int cantidadNodos;

    int buscarIndice(const string& nombre) const;

public:
    Grafo();

    void agregarNodo(const string& nombre, const string& pista = "");
    void agregarArista(const string& origen, const string& destino, int costo);
    void cargarDesdeArchivo(const string& ruta);        // Cargar conexiones del mapa
    void asignarPistas(const string& rutaPistas);       // Cargar pistas por nodo

    int getCantidad() const;
    Nodo* getNodo(int indice);
    int getIndice(const string& nombre) const;
    bool existe(const string& nombre) const;
};

#endif
