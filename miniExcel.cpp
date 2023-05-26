#include <iostream>
#include "mautrix.h"
using namespace std;

void menuPrincipal()
{
    cout << "Menú Principal" << endl;
    cout << "=================" << endl;
    cout << "1. Nuevo." << endl;
    cout << "2. Abrir." << endl;
    cout << "3. Salir." << endl;
    cout << "Ingrese una opción:" << endl;
}

void menuString()
{
    cout << "Opciones: \n _________" << endl;
    cout << "1.  Ingresar contenido" << endl;
    cout << "2.  Saltar a celda o extender hoja" << endl;
    cout << "3.  Copiar" << endl;
    cout << "4.  Cortar" << endl;
    cout << "5.  Pegar" << endl;
    cout << "6.  Mover a la izquierda" << endl;
    cout << "7.  Mover a la derecha" << endl;
    cout << "8.  Mover arriba" << endl;
    cout << "9.  Mover abajo" << endl;
    cout << "10. Guardar" << endl;
    cout << "11. Salir" << endl;
}

void menu()
{
    string contenido = " ";
    string copiedValue;
    int opc = 0;
    int fila = 1;
    int col = 1;
    insertar(1, 1, " ");
    insertar(5, 5, " ");
    system("Color 2");

    do
    {
        menuString();
        mostrarMatriz(fila, col);
        try
        {
            cin >> opc;
            if (cin.fail())
            {
                throw std::invalid_argument("Opción inválida");
            }
            switch (opc)
            {
            case 1:
                cout << "Ingrese el contenido de la celda" << endl;
                cin >> contenido;
                insertar(fila, col, contenido);
                break;
            case 2:
                try
                {
                    cout << "Ingrese el numero de fila de la celda a la que desea saltar: ";
                    cin >> fila;
                    cout << "Ingrese el numero de columna de la celda a la que desea saltar: ";
                    cin >> col;
                    cout << "\nAhora puede ingresar contenido y continuar moviendose antes de agregarlo\n";

                    if (cin.fail())
                    {
                        throw std::invalid_argument("Opción inválida");
                    }
                }
                catch (const std::invalid_argument &e)
                {
                    cout << "Solo puede ingresar valores numericos" << endl;
                    cout << "Ingrese solo valores validos" << endl;
                    cout << "Error: " << e.what() << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            case 3:
                cout << "El elemento se ha copiado" << endl;
                copiedValue = buscarDato(fila, col);
                break;
            case 4:
                cout << "El elemento se ha cortado" << endl;
                copiedValue = buscarDato(fila, col);
                insertar(fila, col, " ");
                break;
            case 5:
                cout << "Pegar" << endl;
                insertar(fila, col, copiedValue);
                break;
            case 6:
                cout << "Mover a la izquierda" << endl;
                if (col > 1)
                {
                    col--;
                    system("Color 2");
                }
                else
                {
                    system("Color 4");
                    cout << "Esta tratando de superar los limites de la hoja\n";
                }
                break;
            case 7:
                cout << "Mover a la derecha" << endl;
                if (col >= 1)
                {
                    system("Color 2");
                }
                col++;
                break;
            case 8:
                cout << "Mover arriba" << endl;
                if (fila > 1)
                {
                    fila--;
                    system("Color 2");
                }
                else
                {
                    system("Color 4");
                    cout << "Esta tratando de superar los limites de la hoja\n";
                }
                break;
            case 9:
                cout << "Mover abajo" << endl;
                if (col >= 1)
                {
                    system("Color 2");
                }
                fila++;
                break;
            case 10:
                guardar();
                break;
            case 11:
                cout << "Salir" << endl;
                limpiarLista();
                menuPrincipal();
                break;
            default:
                cout << "Seleccione una opcion valida" << endl;
                break;
            }
        }
        catch (const std::invalid_argument &e)
        {
            cout << "Ingrese solo valores validos" << endl;
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // system("cls");
    } while (opc != 11);
}

int main()
{
    menuPrincipal();
    int opcion = 0;
    do
    {
        try
        {
            cin >> opcion;
            cin.ignore();
            if (cin.fail())
            {
                throw std::invalid_argument("Opción inválida");
            }
            switch (opcion)
            {
            case 1:
                menu();
                break;
            case 2:
                mostrar();
                break;
            default:
                cout<<"Ingrese solamente opciones validas"<<endl;
                break;
            }
        }
        catch (const std::invalid_argument &e)
        {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (opcion != 3);

    return 0;
}
