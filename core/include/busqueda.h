#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include "grafo.h"
#include "cola.h"     // Cola propia sin STL
#include "pila.h"     // Pila propia sin STL
#include "lista.h"    // Lista para devolver camino

class Busqueda {
public:
    Busqueda();

    // Retorna camino desde inicio hasta objetivo usando BFS
    Lista buscarBFS(Grafo& grafo, const string& inicio, const string& objetivo);

    // Retorna camino desde inicio hasta objetivo usando DFS
    Lista buscarDFS(Grafo& grafo, const string& inicio, const string& objetivo);

    // Retorna camino más corto (por costo) usando Dijkstra
    Lista buscarDijkstra(Grafo& grafo, const string& inicio, const string& objetivo);
};

#endif
