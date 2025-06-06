#include "grafo.h"
#include <fstream>

Grafo::Grafo() {
    cantidadNodos = 0;
}

// Buscar índice de un nodo por su nombre
int Grafo::buscarIndice(const string& nombre) const {
    for (int i = 0; i < cantidadNodos; i++) {
        if (nodos[i].nombre == nombre) {
            return i;
        }
    }
    return -1; // no encontrado
}

// Agrega nodo si no existe
void Grafo::agregarNodo(const string& nombre, const string& pista) {
    if (cantidadNodos >= MAX_NODOS || existe(nombre)) return;

    nodos[cantidadNodos].nombre = nombre;
    nodos[cantidadNodos].pista = pista;
    nodos[cantidadNodos].adyacentes = nullptr;
    cantidadNodos++;
}

// Agrega una arista (bidireccional)
void Grafo::agregarArista(const string& origen, const string& destino, int costo) {
    int idxOrigen = buscarIndice(origen);
    int idxDestino = buscarIndice(destino);
    if (idxOrigen == -1 || idxDestino == -1) return;

    // Agrega a lista del origen
    Arista* nueva = new Arista(destino, costo, nodos[idxOrigen].adyacentes);
    nodos[idxOrigen].adyacentes = nueva;

    // Y también a la inversa
    Arista* nueva2 = new Arista(origen, costo, nodos[idxDestino].adyacentes);
    nodos[idxDestino].adyacentes = nueva2;
}

// Lee archivo de mapa: playa montaña 5
void Grafo::cargarDesdeArchivo(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return;

    string origen, destino;
    int costo;

    while (archivo >> origen >> destino >> costo) {
        if (!existe(origen)) agregarNodo(origen);
        if (!existe(destino)) agregarNodo(destino);
        agregarArista(origen, destino, costo);
    }

    archivo.close();
}

// Lee archivo de pistas: playa: busca al sol
void Grafo::asignarPistas(const string& rutaPistas) {
    ifstream archivo(rutaPistas);
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        size_t pos = linea.find(':');
        if (pos != string::npos) {
            string nombre = linea.substr(0, pos);
            string pista = linea.substr(pos + 1);
            int idx = buscarIndice(nombre);
            if (idx != -1) {
                nodos[idx].pista = pista;
            }
        }
    }

    archivo.close();
}

int Grafo::getCantidad() const {
    return cantidadNodos;
}

Nodo* Grafo::getNodo(int indice) {
    if (indice >= 0 && indice < cantidadNodos) {
        return &nodos[indice];
    }
    return nullptr;
}

int Grafo::getIndice(const string& nombre) const {
    return buscarIndice(nombre);
}

bool Grafo::existe(const string& nombre) const {
    return buscarIndice(nombre) != -1;
}
