#include<iostream>
#include "mautrix.h"
using namespace std;

void menu(){
    cout<<"Opciones: \n _________"<<endl;
    cout<<"1.  Ingresar contenido"<<endl;
    cout<<"2.  Saltar a la celda"<<endl;
    cout<<"3.  Copiar"<<endl;
    cout<<"4.  Cortar"<<endl;
    cout<<"5.  Pegar"<<endl;
    cout<<"6.  Mover a la izquierda"<<endl;
    cout<<"7.  Mover a la derecha"<<endl;
    cout<<"8.  Mover arriba"<<endl;
    cout<<"9.  Mover abajo"<<endl;
    cout<<"10. Guardar"<<endl;
    cout<<"11. Salir"<<endl;
}

int main(){
    string contenido = "0";
    int opc = 0;
    int fila = 1;
    int col = 1;
    insertar(1,1, "0");
    insertar(5,5, "0");

    do{
        menu();
        mostrarMatriz();
        cin>>opc;
        switch (opc)
        {
        case 1:
            cout<<"Ingrese el contenido de la celda"<<endl;
            cin>>contenido;
            insertar(fila, col, contenido);
            break;
        case 2:
            cout<<"Ingrese el numero de fila de la celda a la que desea saltar: ";
            cin>>fila;
            cout<<"Ingrese el numero de columna de la celda a la que desea saltar: ";
            cin>>col;
            saltar(fila,col,"_");
            break;
        case 3:
            cout<<"ACopiar"<<endl;
            break;
        case 4:
            cout<<"Cortar"<<endl;
            break;
        case 5:
            cout<<"Pegar"<<endl;
            break;
        case 6:
            cout<<"Mover a la izquierda"<<endl;
           if (buscarDato(fila,col) == "0" || buscarDato(fila,col) == "_"){
                insertar(fila, col, "0");
            }
            col--;
            saltar(fila,col,"_");
            break;
        case 7:
            cout<<"Mover a la derecha"<<endl;
            if (buscarDato(fila,col) == "0" || buscarDato(fila,col) == "_"){
                insertar(fila, col, "0");
            }
            cout<<buscarDato(fila,col);
            col++;
            saltar(fila,col,"_");
            break;
        case 8:
            cout<<"Mover arriba"<<endl;
            if (buscarDato(fila,col) == "0" || buscarDato(fila,col) == "_"){
                insertar(fila, col, "0");
            }
            fila--;
            saltar(fila,col,"_");
            break;
        case 9:
            cout<<"Mover abajo"<<endl;
            if (buscarDato(fila,col) == "0" || buscarDato(fila,col) == "_"){
                insertar(fila, col, "0");
            }
            fila++;
            saltar(fila,col,"_");
            break;
        case 10:
            cout<<"Guardar"<<endl;
            break;
        case 11:
            cout<<"Salir"<<endl;
            break;
        default:
            cout<<"Seleccione una opcion valida"<<endl;
            break;
        }
        //system("cls");
    }while(opc != 11);

    return 0;
}
