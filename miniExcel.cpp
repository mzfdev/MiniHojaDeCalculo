#include<iostream>
using namespace std;

struct Nodo{
    int idFil;
    Nodo *ant;
    Nodo *sig;
};
Nodo* head;

void insertar(int n, int pos){
    Nodo *nuevo = new Nodo;
    nuevo->idFil = n;
    if (pos == 1 || head == NULL) {
        nuevo->ant = NULL;
        nuevo->sig = head;
        if (head != NULL) {
            head->ant = nuevo;
        }
        head = nuevo;
    } else {
        Nodo* aux = head;
        int cont = 1;
        while (aux->sig != NULL && cont < pos - 1) {
            aux = aux->sig;
            cont++;
        }
        if (cont < pos - 1) {
            while (cont < pos - 1) {
                Nodo* nodoNull = new Nodo;
                nodoNull->idFil = NULL;
                nodoNull->ant = aux;
                nodoNull->sig = NULL;
                aux->sig = nodoNull;
                aux = nodoNull;
                cont++;
            }
        }
        if (aux->sig == NULL) { // si el siguiente nodo es NULL
            nuevo->ant = aux;
            nuevo->sig = aux->sig;
            if (aux->sig != NULL) {
                aux->sig->ant = nuevo;
            }
            aux->sig = nuevo;
        } else { // si el siguiente nodo no es NULL
            aux->sig->idFil = n; // actualiza el valor del nodo existente
        }
    }
}


void mostrar(){
    Nodo *aux=head;
    while(aux!=NULL){
        cout<<aux->idFil<<"->";
        aux=aux->sig;
    }
    cout<<endl;
}


int main(){

    insertar(1,1);
    insertar(2,2);
    insertar(3,5);
   

    mostrar();

    return 0;
}
