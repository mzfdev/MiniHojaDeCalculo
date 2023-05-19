#ifndef MATRIZ_H
#define MATRIZ_H
#include<iostream>
#include <iomanip>

using namespace std;


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