#include "busqueda.h"

// Constructor (vacío por ahora)
Busqueda::Busqueda() {}

// ------------------------------
// BFS (recorrido por niveles)
// ------------------------------
Lista Busqueda::buscarBFS(Grafo& grafo, const string& inicio, const string& objetivo) {
    Lista visitados;
    Cola cola;
    string predecesores[MAX_NODOS];
    bool marcados[MAX_NODOS];

    for (int i = 0; i < grafo.getCantidad(); i++) {
        marcados[i] = false;
        predecesores[i] = "";
    }

    int idxInicio = grafo.getIndice(inicio);
    if (idxInicio == -1) return visitados;

    cola.encolar(inicio);
    marcados[idxInicio] = true;

    while (!cola.vacia()) {
        string actual = cola.desencolar();
        visitados.agregar(actual);

        int idxActual = grafo.getIndice(actual);
        Nodo* nodo = grafo.getNodo(idxActual);
        Arista* arista = nodo->adyacentes;

        while (arista != nullptr) {
            int idxDest = grafo.getIndice(arista->destino);
            if (!marcados[idxDest]) {
                cola.encolar(arista->destino);
                marcados[idxDest] = true;
                predecesores[idxDest] = actual;

                if (arista->destino == objetivo) {
                    // reconstruir camino
                    Lista camino;
                    string actualPaso = objetivo;
                    while (actualPaso != "") {
                        camino.agregar(actualPaso);
                        actualPaso = predecesores[grafo.getIndice(actualPaso)];
                    }

                    // invertir camino manualmente
                    Lista invertido;
                    for (int i = camino.tamano() - 1; i >= 0; i--) {
                        invertido.agregar(camino.obtener(i));
                    }

                    return invertido;
                }
            }
            arista = arista->siguiente;
        }
    }

    return Lista(); // vacío si no se encontró
}

// ------------------------------
// DFS (recorrido en profundidad)
// ------------------------------
Lista Busqueda::buscarDFS(Grafo& grafo, const string& inicio, const string& objetivo) {
    Lista visitados;
    Pila pila;
    string predecesores[MAX_NODOS];
    bool marcados[MAX_NODOS];

    for (int i = 0; i < grafo.getCantidad(); i++) {
        marcados[i] = false;
        predecesores[i] = "";
    }

    int idxInicio = grafo.getIndice(inicio);
    if (idxInicio == -1) return visitados;

    pila.apilar(inicio);
    marcados[idxInicio] = true;

    while (!pila.vacia()) {
        string actual = pila.desapilar();
        visitados.agregar(actual);

        int idxActual = grafo.getIndice(actual);
        Nodo* nodo = grafo.getNodo(idxActual);
        Arista* arista = nodo->adyacentes;

        while (arista != nullptr) {
            int idxDest = grafo.getIndice(arista->destino);
            if (!marcados[idxDest]) {
                pila.apilar(arista->destino);
                marcados[idxDest] = true;
                predecesores[idxDest] = actual;

                if (arista->destino == objetivo) {
                    Lista camino;
                    string actualPaso = objetivo;
                    while (actualPaso != "") {
                        camino.agregar(actualPaso);
                        actualPaso = predecesores[grafo.getIndice(actualPaso)];
                    }

                    Lista invertido;
                    for (int i = camino.tamano() - 1; i >= 0; i--) {
                        invertido.agregar(camino.obtener(i));
                    }

                    return invertido;
                }
            }
            arista = arista->siguiente;
        }
    }

    return Lista(); // vacío si no se encontró
}

// ------------------------------
// Dijkstra (mínimo costo)
// ------------------------------
Lista Busqueda::buscarDijkstra(Grafo& grafo, const string& inicio, const string& objetivo) {
    Lista camino;

    int distancias[MAX_NODOS];
    string predecesores[MAX_NODOS];
    bool visitados[MAX_NODOS];

    int n = grafo.getCantidad();

    for (int i = 0; i < n; i++) {
        distancias[i] = 999999;
        predecesores[i] = "";
        visitados[i] = false;
    }

    int idxInicio = grafo.getIndice(inicio);
    distancias[idxInicio] = 0;

    for (int i = 0; i < n; i++) {
        // Buscar nodo no visitado con menor distancia
        int minDist = 999999;
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visitados[j] && distancias[j] < minDist) {
                minDist = distancias[j];
                u = j;
            }
        }

        if (u == -1) break;

        visitados[u] = true;
        Nodo* nodoActual = grafo.getNodo(u);
        Arista* arista = nodoActual->adyacentes;

        while (arista != nullptr) {
            int v = grafo.getIndice(arista->destino);
            int peso = arista->costo;
            if (!visitados[v] && distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                predecesores[v] = nodoActual->nombre;
            }
            arista = arista->siguiente;
        }
    }

    int idxObjetivo = grafo.getIndice(objetivo);
    if (distancias[idxObjetivo] == 999999) {
        return Lista(); // No hay camino
    }

    string paso = objetivo;
    while (paso != "") {
        camino.agregar(paso);
        paso = predecesores[grafo.getIndice(paso)];
    }

    Lista invertido;
    for (int i = camino.tamano() - 1; i >= 0; i--) {
        invertido.agregar(camino.obtener(i));
    }

    return invertido;
}
