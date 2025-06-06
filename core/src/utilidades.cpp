#include "utilidades.h"
#include <fstream>
#include <iostream>

// Convierte texto a minúsculas
string aMinusculas(const string& texto) {
    string resultado = texto;
    for (int i = 0; i < resultado.length(); i++) {
        if (resultado[i] >= 'A' && resultado[i] <= 'Z') {
            resultado[i] = resultado[i] + ('a' - 'A');
        }
    }
    return resultado;
}

// Verifica si texto contiene palabra clave (sin usar STL)
bool contiene(const string& texto, const string& palabra) {
    int lenTexto = texto.length();
    int lenPalabra = palabra.length();

    for (int i = 0; i <= lenTexto - lenPalabra; i++) {
        int j = 0;
        while (j < lenPalabra && texto[i + j] == palabra[j]) {
            j++;
        }
        if (j == lenPalabra) return true;
    }
    return false;
}

// Separa string por delimitador
Lista split(const string& texto, char delimitador) {
    Lista partes;
    string palabra = "";

    for (int i = 0; i < texto.length(); i++) {
        if (texto[i] == delimitador) {
            if (palabra != "") {
                partes.agregar(palabra);
                palabra = "";
            }
        } else {
            palabra += texto[i];
        }
    }

    if (palabra != "") {
        partes.agregar(palabra);
    }

    return partes;
}

// Guarda ruta en archivo línea por línea
void guardarRutaEnArchivo(const string& rutaArchivo, const Lista& ruta) {
    ofstream archivo(rutaArchivo.c_str());
    if (!archivo.is_open()) return;

    for (int i = 0; i < ruta.tamano(); i++) {
        archivo << ruta.obtener(i) << endl;
    }

    archivo.close();
}

// Imprime ruta en consola
void imprimirRuta(const Lista& ruta) {
    for (int i = 0; i < ruta.tamano(); i++) {
        cout << ruta.obtener(i);
        if (i < ruta.tamano() - 1) cout << " -> ";
    }
    cout << endl;
}
