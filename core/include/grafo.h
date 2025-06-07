#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <fstream>
#include <nlohmann/json.hpp> // JSON para exportación
using json = nlohmann::json;
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
    float x, y; // 📍 Coordenadas para visualización

    Nodo() : nombre(""), pista(""), adyacentes(nullptr), x(0), y(0) {}
};

class Grafo {
private:
    Nodo nodos[MAX_NODOS];
    int cantidadNodos;

    int buscarIndice(const string& nombre) const;
    string limpiarTexto(const string& texto) const;

public:
    Grafo();

    void agregarNodo(const string& nombre, const string& pista = "");
    void agregarArista(const string& origen, const string& destino, int costo);
    void cargarDesdeArchivo(const string& ruta);
    void asignarPistas(const string& rutaPistas);

    // 🔄 NUEVO: Asignar coordenadas (manual)
    void asignarCoordenadas();

    // 🌐 NUEVO: Exportar JSON
    void exportarAJson(const string& ruta);

    int getCantidad() const;
    Nodo* getNodo(int indice);
    int getIndice(const string& nombre) const;
    bool existe(const string& nombre) const;
};

#endif
