#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
#include "lista.h" // Lista propia sin STL
using namespace std;

// Convierte un string a minúsculas
string aMinusculas(const string& texto);

// Verifica si una palabra clave está dentro de la pista
bool contiene(const string& texto, const string& palabra);

// Separa un string por un delimitador y guarda en una Lista
Lista split(const string& texto, char delimitador);

// Guarda una ruta (lista de ubicaciones) en un archivo de texto
void guardarRutaEnArchivo(const string& rutaArchivo, const Lista& ruta);

// Imprime la ruta por consola
void imprimirRuta(const Lista& ruta);

// ✅ Exporta la ruta encontrada como archivo JSON para visualización (con método)
void exportarRutaJSON(const Lista& ruta, const string& archivo, const string& metodo);

#endif
