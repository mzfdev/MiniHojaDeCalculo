#ifndef MATRIZ_H
#define MATRIZ_H
#include<iostream>
#include <iomanip>
#include <fstream>
#include <dirent.h>
#include "include/dnc/json.hpp"
#include "json.hpp"
#include "csv.h"

namespace joaquinrmi {
    using json = nlohmann::json;
}

using namespace std;
using json = joaquinrmi::json;


struct NodoColumna {
    int idCol;
    string dato;
    NodoColumna *ant;
    NodoColumna *sig;
};

struct NodoFila {
    int idFil;
    NodoFila *ant;
    NodoFila *sig;
    NodoColumna *columnas;
};

NodoFila* head;

void guardar() {
    json matrizJSON;

    NodoFila* fila = head;
    while (fila != nullptr) {
        json filaJSON;
        filaJSON["idFil"] = fila->idFil;

        NodoColumna* columna = fila->columnas;
        while (columna != nullptr) {
            json columnaJSON;
            columnaJSON["idCol"] = columna->idCol;
            columnaJSON["dato"] = columna->dato;

            filaJSON["columnas"].push_back(columnaJSON);

            columna = columna->sig;
        }

        matrizJSON["filas"].push_back(filaJSON);

        fila = fila->sig;
    }

    std::string nombreArchivo;
    std::cout << "Ingrese el nombre del archivo: ";
    std::cin >> nombreArchivo;

    std::ofstream archivoJSON(nombreArchivo + ".json");
    archivoJSON << matrizJSON.dump(4); // Opcional: indentación de 4 espacios
    archivoJSON.close();
}

void mostrar() {
    std::string directorio = "./"; // Directorio actual (puedes cambiarlo por el directorio deseado)
    std::cout << "Archivos guardados en el directorio '" << directorio << "':" << std::endl;

    DIR* dir;
    struct dirent* archivo;
    dir = opendir(directorio.c_str());

    if (dir) {
        int contador = 1;
        std::string** archivos = new std::string*[100]; // Arreglo de punteros para almacenar los nombres de los archivos

        while ((archivo = readdir(dir)) != nullptr) {
            std::string nombreArchivo = archivo->d_name;

            if (nombreArchivo.length() >= 5 && nombreArchivo.substr(nombreArchivo.length() - 5) == ".json") {
                std::cout << std::setw(2) << contador << " " << std::left << nombreArchivo << std::endl;
                archivos[contador - 1] = new std::string(nombreArchivo);
                contador++;
            }
        }

        closedir(dir);

        if (contador > 1) {
            // Solicitar al usuario seleccionar un archivo
            int seleccion;
            std::cout << "Seleccione el número del archivo que desea abrir: ";
            std::cin >> seleccion;

            if (seleccion >= 1 && seleccion < contador) {
                std::string* nombreArchivo = archivos[seleccion - 1];

                // Abrir archivo JSON
                std::ifstream archivoJSON(*nombreArchivo);
                if (archivoJSON.is_open()) {
                    std::cout << "Creando hoja de cálculo con el contenido de " << *nombreArchivo << "..." << std::endl;

                    // Crear hoja de cálculo CSV con el contenido del archivo JSON
                    std::string nombreCSV = nombreArchivo->substr(0, nombreArchivo->length() - 5) + ".csv";
                    std::ofstream archivoCSV(nombreCSV);

                    if (archivoCSV.is_open()) {
                        json jsonData;
                        archivoJSON >> jsonData;
                        archivoJSON.close();

                        for (const auto& fila : jsonData["filas"]) {
                            std::string filaCSV;
                            for (const auto& columna : fila["columnas"]) {
                                filaCSV += columna["dato"].get<std::string>() + ",";
                            }
                            filaCSV.pop_back(); // Eliminar la última coma
                            archivoCSV << filaCSV << std::endl;
                        }

                        archivoCSV.close();
                        std::cout << "Se ha creado la hoja de cálculo " << nombreCSV << " con el contenido del archivo guardado." << std::endl;
                    } else {
                        std::cout << "No se pudo crear la hoja de cálculo." << std::endl;
                    }
                } else {
                    std::cout << "No se pudo abrir el archivo " << *nombreArchivo << std::endl;
                }
            } else {
                std::cout << "Selección inválida." << std::endl;
            }
        } else {
            std::cout << "No hay archivos guardados en el directorio." << std::endl;
        }

        // Liberar la memoria asignada
        for (int i = 0; i < contador - 1; ++i) {
            delete archivos[i];
        }
        delete[] archivos;
    } else {
        std::cout << "Error al abrir el directorio" << std::endl;
    }
}

string buscarDato(int idFila, int idColumna) {
    // buscar el nodo de la fila correspondiente
    NodoFila *fila = head;
    while (fila != NULL && fila->idFil != idFila) {
        fila = fila->sig;
    }

    // si la fila no existe, el dato no existe
    if (fila == NULL) {
        return "0";
    }

    // buscar el nodo de la columna correspondiente
    NodoColumna *columna = fila->columnas;
    while (columna != NULL && columna->idCol != idColumna) {
        columna = columna->sig;
    }

    // si la columna no existe, el dato no existe
    if (columna == NULL) {
        return "0";
    }

    // si la celda existe, devolver el dato
    return columna->dato;
}

void insertar(int idFila, int idColumna, string dato){
    // buscar el nodo de la fila correspondiente
    NodoFila *fila = head;
    while (fila != NULL && fila->idFil != idFila) {
        fila = fila->sig;
    }

    // si la fila no existe, crearla
    if (fila == NULL) {
        fila = new NodoFila;
        fila->idFil = idFila;
        fila->ant = NULL;
        fila->sig = head;
        fila->columnas = NULL;
        if (head != NULL) {
            head->ant = fila;
        }
        head = fila;
    }

    // buscar el nodo de la columna correspondiente
    NodoColumna *columna = fila->columnas;
    while (columna != NULL && columna->idCol != idColumna) {
        columna = columna->sig;
    }

    // si la columna no existe, crearla
    if (columna == NULL) {
        columna = new NodoColumna;
        columna->idCol = idColumna;
        columna->dato = dato;
        columna->ant = NULL;
        columna->sig = fila->columnas;
        if (fila->columnas != NULL) {
            fila->columnas->ant = columna;
        }
        fila->columnas = columna;
    } else {
        // si la columna ya existe, actualizar el dato
        columna->dato = dato;
    }
}

void mostrarMatriz(int f, int c) {
    int numFilas = 0, numCols = 0;
    NodoFila *fila = head;
    while (fila != NULL) {
        if (fila->idFil > numFilas) {
            numFilas = fila->idFil;
        }
        NodoColumna *columna = fila->columnas;
        while (columna != NULL) {
            if (columna->idCol > numCols) {
                numCols = columna->idCol;
            }
            columna = columna->sig;
        }
        fila = fila->sig;
    }

    if (f > numFilas) {
        numFilas = f;
    }
    if (c > numCols) {
        numCols = c;
    }

    const int anchoCelda = 10;

    for (int i = 1; i <= numFilas; i++) {
        for (int j = 1; j <= numCols; j++) {
            NodoFila *fila = head;
            while (fila != NULL && fila->idFil != i) {
                fila = fila->sig;
            }
            if (fila == NULL) {
                if (i == f && j == c) {
                    cout << setw(anchoCelda) << "_";
                } else {
                    cout << setw(anchoCelda) << " ";
                }
            } else {
                NodoColumna *columna = fila->columnas;
                while (columna != NULL && columna->idCol != j) {
                    columna = columna->sig;
                }
                if (columna == NULL) {
                    if (i == f && j == c) {
                        cout << setw(anchoCelda) << "_";
                    } else {
                        cout << setw(anchoCelda) << " ";
                    }
                } else {
                    if (i == f && j == c) {
                        cout << setw(anchoCelda) << "_";
                    } else {
                        string dato = columna->dato;
                        if (dato.length() > anchoCelda - 2) {
                            dato = dato.substr(0, anchoCelda - 5) + "...";
                        }
                        cout << setw(anchoCelda) << dato;
                    }
                }
            }

            if (j < numCols) {
                cout << "|";
            }
        }
        cout << endl;

        if (i < numFilas) {
            for (int k = 1; k <= numCols; k++) {
                cout << setw(anchoCelda) << setfill('-') << "" << setfill(' ');
                if (k < numCols) {
                    cout << "|";
                }
            }
            cout << endl;
        }
    }
}



//Saltar a una celda
void saltar(int idFila, int idColumna, string dato){
        // buscar el nodo de la fila correspondiente
    NodoFila *fila = head;
    while (fila != NULL && fila->idFil != idFila) {
        fila = fila->sig;
    }

    // si la fila no existe, crearla
    if (fila == NULL) {
        fila = new NodoFila;
        fila->idFil = idFila;
        fila->ant = NULL;
        fila->sig = head;
        fila->columnas = NULL;
        if (head != NULL) {
            head->ant = fila;
        }
        head = fila;
    }

    // buscar el nodo de la columna correspondiente
    NodoColumna *columna = fila->columnas;
    while (columna != NULL && columna->idCol != idColumna) {
        columna = columna->sig;
    }

    // si la columna no existe, crearla
    if (columna == NULL) {
        // Solo crear la celda si se ingresó un dato
        if (dato != "") {
            columna = new NodoColumna;
            columna->idCol = idColumna;
            columna->dato = dato;
            columna->ant = NULL;
            columna->sig = fila->columnas;
            if (fila->columnas != NULL) {
                fila->columnas->ant = columna;
            }
            fila->columnas = columna;
        }
    } else {
        // si la columna ya existe, actualizar el dato
        columna->dato = dato;
    }
}

#endif