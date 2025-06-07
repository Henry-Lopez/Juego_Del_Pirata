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

    arbol.construirArbolEjemplo(); // ¡Importante! sin esto no interpreta pistas

    do {
        cout << "\n+===========================================+\n";
        cout << "|        TESORO DEL PIRATA - MENU           |\n";
        cout << "+-------------------------------------------+\n";
        cout << "| 1.   Cargar grafo desde archivo           |\n";
        cout << "| 2.   Cargar pistas desde archivo          |\n";
        cout << "| 3.   Mostrar pistas interpretadas         |\n";
        cout << "| 4.   Abrir visualizador interactivo       |\n";
        cout << "| 5.   Buscar ruta con BFS                  |\n";
        cout << "| 6.   Buscar ruta con DFS                  |\n";
        cout << "| 7.   Buscar ruta con Dijkstra             |\n";
        cout << "| 8.   Mostrar ruta encontrada              |\n";
        cout << "| 9.   Guardar ruta en archivo              |\n";
        cout << "| 0.   Salir                                |\n";
        cout << "+===========================================+\n";
        cout << "Seleccione una opcion: ";

        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "Seleccione grafo:\n";
                cout << "a) Isla del Pirata\n";
                cout << "b) Tierra Media\n";
                cout << "Opcion: ";
                char tipo;
                cin >> tipo;

                if (tipo == 'a') {
                    grafo.cargarDesdeArchivo("datos/isla.txt");
                } else if (tipo == 'b') {
                    grafo.cargarDesdeArchivo("datos/tierra_media.txt");
                    grafo.asignarPistas("datos/tierra_media_pistas.txt");
                    grafo.asignarCoordenadas();
                    grafo.exportarAJson("visualizador/grafo.json");
                    cout << "⚙️ Grafo de Tierra Media exportado a visualizador/grafo.json\n";
                    pistasCargadas = true;
                } else {
                    cout << "Opcion invalida.\n";
                    break;
                }

                if (grafo.getCantidad() > 0) {
                    cout << "Grafo cargado con exito. Total nodos: " << grafo.getCantidad() << endl;
                    grafoCargado = true;
                } else {
                    cout << "Error: No se cargaron nodos. Revisa el archivo.\n";
                }
                break;
            }

            case 2:
                cout << "Seleccione archivo de pistas:\n";
                cout << "a) pistas.txt\n";
                cout << "b) tierra_media_pistas.txt\n";
                cout << "Opcion: ";
                char pistasTipo;
                cin >> pistasTipo;

                if (pistasTipo == 'a') {
                    grafo.asignarPistas("datos/pistas.txt");
                } else if (pistasTipo == 'b') {
                    grafo.asignarPistas("datos/tierra_media_pistas.txt");
                } else {
                    cout << "Opcion invalida.\n";
                    break;
                }

                cout << "Pistas asignadas a los nodos.\n";
                pistasCargadas = true;
                grafo.exportarAJson("visualizador/grafo.json");
                break;

            case 3:
                if (!grafoCargado || !pistasCargadas) {
                    cout << "Debe cargar el grafo y las pistas primero.\n";
                    break;
                }
                cout << "\nPistas interpretadas:\n";
                for (int i = 0; i < grafo.getCantidad(); i++) {
                    Nodo* n = grafo.getNodo(i);
                    if (!n) continue;
                    string pista = aMinusculas(n->pista);
                    string lugar = arbol.interpretarPista(pista);
                    cout << "- Nodo: " << n->nombre << " | Pista: \"" << n->pista << "\" ---> Tesoro??? " << lugar << endl;
                }
                break;

            case 4:
                cout << "Abriendo visualizador en el navegador...\n";

                // 1. Abre una consola nueva que arranca el servidor HTTP en la carpeta 'visualizador'
                system("start cmd /k \"cd visualizador && python -m http.server 8080\"");

                // 2. Abre automáticamente el navegador apuntando al visualizador en localhost:8080
                system("start http://localhost:8080/index.html");
                break;

            case 5:
            case 6:
            case 7:
                if (!grafoCargado) {
                    cout << "Debe cargar el grafo primero.\n";
                    break;
                }

                cout << "Ingrese ubicacion inicial: ";
                cin >> inicio;
                cout << "Ingrese ubicacion objetivo: ";
                cin >> objetivo;

                inicio = aMinusculas(inicio);
                objetivo = aMinusculas(objetivo);

                if (opcion == 5)
                    rutaEncontrada = buscador.buscarBFS(grafo, inicio, objetivo);
                else if (opcion == 6)
                    rutaEncontrada = buscador.buscarDFS(grafo, inicio, objetivo);
                else
                    rutaEncontrada = buscador.buscarDijkstra(grafo, inicio, objetivo);

                if (rutaEncontrada.tamano() > 0) {
                    cout << "Ruta encontrada:\n";
                    imprimirRuta(rutaEncontrada);

                    string metodo = (opcion == 5) ? "bfs" : (opcion == 6) ? "dfs" : "dijkstra";
                    exportarRutaJSON(rutaEncontrada, "visualizador/ruta.json", metodo);

                    cout << "Ruta exportada a visualizador/ruta.json (" << metodo << ")\n";
                } else {
                    cout << "No se encontro ruta entre " << inicio << " y " << objetivo << ".\n";
                }
                break;

            case 8:
                if (rutaEncontrada.tamano() > 0) {
                    imprimirRuta(rutaEncontrada);
                } else {
                    cout << "No hay ruta cargada.\n";
                }
                break;

            case 9:
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
