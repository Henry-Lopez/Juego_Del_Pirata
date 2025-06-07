#include "grafo.h"
#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;

Grafo::Grafo() {
    cantidadNodos = 0;
}

string Grafo::limpiarTexto(const string& texto) const {
    string limpio = "";
    for (char c : texto) {
        if (c != '\r' && c != '\n' && c != ' ') {
            limpio += tolower(c);
        }
    }
    return limpio;
}

int Grafo::buscarIndice(const string& nombre) const {
    string limpio = limpiarTexto(nombre);
    for (int i = 0; i < cantidadNodos; i++) {
        if (limpiarTexto(nodos[i].nombre) == limpio) {
            return i;
        }
    }
    return -1;
}

void Grafo::agregarNodo(const string& nombre, const string& pista) {
    string limpio = limpiarTexto(nombre);
    if (cantidadNodos >= MAX_NODOS || existe(limpio)) return;

    nodos[cantidadNodos].nombre = limpio;
    nodos[cantidadNodos].pista = pista;
    nodos[cantidadNodos].adyacentes = nullptr;
    nodos[cantidadNodos].x = 0; // Default
    nodos[cantidadNodos].y = 0;
    cantidadNodos++;
}

void Grafo::agregarArista(const string& origen, const string& destino, int costo) {
    string o = limpiarTexto(origen);
    string d = limpiarTexto(destino);
    int idxOrigen = buscarIndice(o);
    int idxDestino = buscarIndice(d);
    if (idxOrigen == -1 || idxDestino == -1) return;

    Arista* nueva = new Arista(d, costo, nodos[idxOrigen].adyacentes);
    nodos[idxOrigen].adyacentes = nueva;

    Arista* nueva2 = new Arista(o, costo, nodos[idxDestino].adyacentes);
    nodos[idxDestino].adyacentes = nueva2;
}

void Grafo::cargarDesdeArchivo(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << ruta << endl;
        return;
    }

    string origen, destino;
    int costo;

    while (archivo >> origen >> destino >> costo) {
        agregarNodo(origen);
        agregarNodo(destino);
        agregarArista(origen, destino, costo);
    }

    archivo.close();

    cout << "Nodos cargados: " << cantidadNodos << endl;
    for (int i = 0; i < cantidadNodos; i++) {
        cout << "- " << nodos[i].nombre << endl;
    }
}

void Grafo::asignarPistas(const string& rutaPistas) {
    ifstream archivo(rutaPistas);
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        size_t pos = linea.find(':');
        if (pos != string::npos) {
            string nombre = limpiarTexto(linea.substr(0, pos));
            string pista = linea.substr(pos + 1);
            int idx = buscarIndice(nombre);
            if (idx != -1) {
                nodos[idx].pista = pista;
            }
        }
    }

    archivo.close();
}

// 🆕 Asignar coordenadas manuales para visualización
void Grafo::asignarCoordenadas() {
    struct Pos {
        string nombre;
        float x, y;
    };

    Pos posiciones[] = {
        {"hobbiton", 160, 515},
        {"bree", 200, 470},
        {"rivendel", 320, 390},
        {"moria", 400, 460},
        {"lothlorien", 470, 440},
        {"rohan", 520, 530},
        {"minas_tirith", 630, 575},
        {"mordor", 770, 580},
        {"tharbad", 250, 530},
        {"fangorn", 500, 500},
        {"edoras", 550, 510},
        {"helms_deep", 520, 550},
        {"isengard", 450, 500},
        {"minas_morgul", 710, 565},
        {"osgiliath", 670, 560}
    };


    for (auto& p : posiciones) {
        int idx = buscarIndice(p.nombre);
        if (idx != -1) {
            nodos[idx].x = p.x;
            nodos[idx].y = p.y;
        }
    }
}

// 🆕 Exportar el grafo completo a grafo.json
void Grafo::exportarAJson(const string& ruta) {
    json j;

    // Nodos
    for (int i = 0; i < cantidadNodos; i++) {
        j["nodos"].push_back({
    {"nombre", nodos[i].nombre},
    {"x", nodos[i].x},
    {"y", nodos[i].y},
    {"pista", nodos[i].pista}
});

    }

    // Conexiones
    for (int i = 0; i < cantidadNodos; i++) {
        Arista* actual = nodos[i].adyacentes;
        while (actual != nullptr) {
            // Para evitar duplicados, solo agregamos si nombre origen < destino
            if (nodos[i].nombre < actual->destino) {
                j["conexiones"].push_back({
                    {"origen", nodos[i].nombre},
                    {"destino", actual->destino},
                    {"peso", actual->costo}
                });
            }
            actual = actual->siguiente;
        }
    }

    ofstream out(ruta);
    if (!out.is_open()) {
        cout << "No se pudo escribir " << ruta << endl;
        return;
    }

    out << j.dump(4);
    out.close();

    cout << "Grafo exportado a " << ruta << endl;
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
