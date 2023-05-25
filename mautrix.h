#ifndef MATRIZ_H
#define MATRIZ_H
#include<iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include "include/dnc/json.hpp"
#include "json.hpp"

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
    int numFilas = 0, numCols = 0;
    NodoFila* fila = head;
    while (fila != nullptr) {
        if (fila->idFil > numFilas) {
            numFilas = fila->idFil;
        }
        NodoColumna* columna = fila->columnas;
        while (columna != nullptr) {
            if (columna->idCol > numCols) {
                numCols = columna->idCol;
            }
            columna = columna->sig;
        }
        fila = fila->sig;
    }

    const int anchoCelda = 10;
    const int anchoSeparador = 2;
    const int anchoLinea = (anchoCelda + anchoSeparador) * numCols + anchoSeparador;

    std::string nombreArchivo;
    std::cout << "Ingrese el nombre del archivo: ";
    std::cin >> nombreArchivo;

    std::ofstream archivoJSON(nombreArchivo + ".json");

    std::stringstream contenidoJSON;

    std::string lineaSeparador(anchoLinea, '-');

    for (int i = 1; i <= numFilas; i++) {
        contenidoJSON << lineaSeparador << "\n";
        contenidoJSON << std::setw(anchoLinea);
        for (int j = 1; j <= numCols; j++) {
            NodoFila* filaActual = head;
            while (filaActual != nullptr && filaActual->idFil != i) {
                filaActual = filaActual->sig;
            }

            if (filaActual == nullptr) {
                if (i == 1 && j == 1) {
                    contenidoJSON << std::setw(anchoCelda) << " ";
                } else if (i == numFilas && j == numCols) {
                    contenidoJSON << std::setw(anchoCelda) << " ";
                } else {
                    contenidoJSON << std::setw(anchoCelda) << "|";
                }
            } else {
                NodoColumna* columnaActual = filaActual->columnas;
                while (columnaActual != nullptr && columnaActual->idCol != j) {
                    columnaActual = columnaActual->sig;
                }

                if (columnaActual == nullptr) {
                    if (i == 1 && j == 1) {
                        contenidoJSON << std::setw(anchoCelda) << " ";
                    } else if (i == numFilas && j == numCols) {
                        contenidoJSON << std::setw(anchoCelda) << " ";
                    } else {
                        contenidoJSON << std::setw(anchoCelda) << "|";
                    }
                } else {
                    std::string dato = columnaActual->dato;
                    if (dato.length() > anchoCelda - 2) {
                        dato = dato.substr(0, anchoCelda - 5) + "...";
                    }
                    contenidoJSON << std::setw(anchoCelda) << dato;
                }
            }

            if (j < numCols) {
                contenidoJSON << " ";
            }
        }
        if (i < numFilas) {
            contenidoJSON << "\n";
        }
    }

    contenidoJSON << "\n";
    contenidoJSON << lineaSeparador;
    contenidoJSON << "\n";
    archivoJSON << contenidoJSON.str();
    archivoJSON.close();

    std::cout << "Hoja de cálculo guardada en el archivo " << nombreArchivo << ".json" << std::endl;
}


void mostrar() {
    std::string directorio = "./"; 
    std::cout << "Archivos guardados en el directorio '" << directorio << "':" << std::endl;

    DIR* dir;
    struct dirent* archivo;
    dir = opendir(directorio.c_str());

    if (dir) {
        int contador = 1;

        while ((archivo = readdir(dir)) != nullptr) {
            std::string nombreArchivo = archivo->d_name;

            if (nombreArchivo.length() >= 5 && nombreArchivo.substr(nombreArchivo.length() - 5) == ".json") {
                std::cout << std::setw(2) << contador << " " << std::left << nombreArchivo << std::endl;
                contador++;
            }
        }

        closedir(dir);

        if (contador > 1) {
            
            int seleccion;
            std::cout << "Seleccione el número del archivo que desea abrir: ";
            std::cin >> seleccion;

            if (seleccion >= 1 && seleccion < contador) {
                dir = opendir(directorio.c_str()); // Abrir el directorio nuevamente para buscar el archivo seleccionado

                int contadorSeleccionado = 1;

                while ((archivo = readdir(dir)) != nullptr) {
                    std::string nombreArchivo = archivo->d_name;

                    if (nombreArchivo.length() >= 5 && nombreArchivo.substr(nombreArchivo.length() - 5) == ".json") {
                        if (contadorSeleccionado == seleccion) {
                            std::ifstream archivoJSON(nombreArchivo);
                            if (archivoJSON.is_open()) {
                                std::cout << "Mostrando el contenido del archivo " << nombreArchivo << ":" << std::endl;

                                std::string linea;
                                while (std::getline(archivoJSON, linea)) {
                                    std::cout << linea << std::endl;
                                }
                                archivoJSON.close();
                            } else {
                                std::cout << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
                            }

                            break;
                        }

                        contadorSeleccionado++;
                    }
                }

                closedir(dir);
            } else {
                std::cout << "Selección inválida." << std::endl;
            }
        } else {
            std::cout << "No hay archivos guardados en el directorio." << std::endl;
        }
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

void limpiarLista() {
    NodoFila* filaActual = head;
    while (filaActual != nullptr) {
        NodoColumna* columnaActual = filaActual->columnas;
        while (columnaActual != nullptr) {
            NodoColumna* columnaSiguiente = columnaActual->sig;
            delete columnaActual;
            columnaActual = columnaSiguiente;
        }
        
        NodoFila* filaSiguiente = filaActual->sig;
        delete filaActual;
        filaActual = filaSiguiente;
    }
    
    // Establecer el puntero head a nullptr para indicar que la lista está vacía.
    head = nullptr;
}


#endif