#include <iostream>
#include "../core/include/grafo.h"
#include "../core/include/busqueda.h"
#include "../core/include/decision_tree.h"
#include "../core/include/utilidades.h"

using namespace std;

int main() {
    Grafo grafo;
    Busqueda buscador;
    DecisionTree arbol;
    Lista rutaEncontrada;

    bool grafoCargado = false;
    bool pistasCargadas = false;

    int opcion;
    string inicio, objetivo;

    arbol.construirArbolEjemplo();

    do {
        cout << "\n===== TESORO DEL PIRATA =====\n";
        cout << "1. Cargar grafo desde archivo\n";
        cout << "2. Cargar pistas desde archivo\n";
        cout << "3. Mostrar pistas interpretadas\n";
        cout << "4. Buscar ruta con BFS\n";
        cout << "5. Buscar ruta con DFS\n";
        cout << "6. Buscar ruta con Dijkstra\n";
        cout << "7. Mostrar ruta encontrada\n";
        cout << "8. Guardar ruta en archivo\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                grafo.cargarDesdeArchivo("datos/isla.txt");
                cout << "Grafo cargado con exito.\n";
                grafoCargado = true;
                break;

            case 2:
                grafo.asignarPistas("datos/pistas.txt");
                cout << "Pistas asignadas a los nodos.\n";
                pistasCargadas = true;
                break;

            case 3:
                if (!grafoCargado || !pistasCargadas) {
                    cout << "Debe cargar el grafo y las pistas primero.\n";
                    break;
                }
                for (int i = 0; i < grafo.getCantidad(); i++) {
                    Nodo* n = grafo.getNodo(i);
                    string pista = aMinusculas(n->pista);
                    string lugar = arbol.interpretarPista(pista);
                    cout << "- " << n->nombre << ": \"" << n->pista << "\" → ¿Tesoro? " << lugar << endl;
                }
                break;

            case 4:
            case 5:
            case 6:
                if (!grafoCargado) {
                    cout << "Debe cargar el grafo primero.\n";
                    break;
                }
                cout << "Ingrese ubicacion inicial: ";
                cin >> inicio;
                cout << "Ingrese ubicacion objetivo: ";
                cin >> objetivo;

                if (opcion == 4)
                    rutaEncontrada = buscador.buscarBFS(grafo, inicio, objetivo);
                else if (opcion == 5)
                    rutaEncontrada = buscador.buscarDFS(grafo, inicio, objetivo);
                else
                    rutaEncontrada = buscador.buscarDijkstra(grafo, inicio, objetivo);

                if (rutaEncontrada.tamano() > 0) {
                    cout << "Ruta encontrada:\n";
                    imprimirRuta(rutaEncontrada);
                } else {
                    cout << "No se encontro ruta entre " << inicio << " y " << objetivo << ".\n";
                }
                break;

            case 7:
                if (rutaEncontrada.tamano() > 0) {
                    imprimirRuta(rutaEncontrada);
                } else {
                    cout << "No hay ruta cargada.\n";
                }
                break;

            case 8:
                guardarRutaEnArchivo("datos/ruta_tesoro.txt", rutaEncontrada);
                cout << "Ruta guardada en datos/ruta_tesoro.txt\n";
                break;

            case 0:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);

    return 0;
}
