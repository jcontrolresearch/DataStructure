#include <iostream>
#include "lista.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include "libro.h"

#include <stdio.h>

using namespace std;
Nodo* CrearNodo(Libro* libro){
	Nodo* nodo = (Nodo *) malloc(sizeof(Nodo));
	strncpy(nodo->libro.titulo, libro->titulo,50);
	strncpy(nodo->libro.autor, libro->autor,50);
	strncpy(nodo->libro.isbn, libro->isbn,15);
	nodo->siguiente = NULL;
	return nodo;
}

void EliminarNodo(Nodo* nodo){
	// Como se libera memoria en lenguaje C?
	// Usar free para liberar o "quitar" espacios de memoria previamente llenados con unciones malla(), calloc() o realloc()
	free(nodo);
}

void InsertarPrincipio(Lista* lista, Libro* libro){
	// 1.- Crear el nuevo nodo
	Nodo* nodo = CrearNodo(libro);
	// 2.- Asignar el siguiente del nuevo nodo a la primero de la lista
	// El objeto lista->primero es el primero de la lista
	// El objeto nodo->siguiente es el apuntador al nodo siguiente
	nodo->siguiente = lista->cabeza;
	// 3.- Debemos cambiar la referenia primero de la lista actual al nuevo nodo
	lista->cabeza = nodo;
	lista->longitud++;
}

void InsertarFinal(Lista* lista, Libro* libro){
	// 1.- Crear un nuevo nodo
	Nodo* nodo = CrearNodo(libro);
	
	// Que pasa si la lista esta vacia?
	// para saber si la lista esta vacia basta con revisar el primer elemento
	if(lista->cabeza == NULL){
		lista->cabeza = nodo;
	} else{
		// 2.- Recorrer la lista hasta el final
		// Creamos una variable auxiliar para recorer la lista desde el principio
		Nodo* puntero = lista->cabeza;
		while(puntero->siguiente == NULL){
			puntero = puntero->siguiente;
		}
		//Paso 3.- Hacer que el ultimo objeto de la lista apunte al nodo nuevo
		puntero->siguiente = nodo;
		nodo->siguiente = NULL;
	}
	lista->longitud++;
}

void InsertarDespues(int n,Lista* lista,Libro* libro){
	Nodo* nodo = CrearNodo(libro);
	if(lista->cabeza == NULL){
		lista->cabeza = nodo;
	} else {
		Nodo* puntero = lista->cabeza;
		int posicion = 0;
		while(posicion < n && puntero->siguiente == NULL){
			puntero = puntero->siguiente;
			posicion++;
		}
		nodo->siguiente = puntero->siguiente;
		puntero->siguiente = nodo;
	}
	lista->longitud++;
}

Libro* Obterner(int n, Lista* lista){
	if(lista->cabeza == NULL){
		//la lista no tiene nada
		return NULL;
	} else {
		// Crear un nodo al que llamaremos puntero y le asignamos el primero elemento de la lista
		Nodo* puntero = lista->cabeza;
		int posicion = 0;
		// Recorrer la lista hasta que la posicion sea igual que n y que el siguiente no sea NULL o en otras palabras
		// que eistan elementos en la lista 
		while( posicion < n && puntero->siguiente ){
			puntero = puntero->siguiente;
			posicion ++;
		}
		if(posicion != n){
			return NULL;
		} else {
			return &puntero->libro;
		}
		// Retornar del nodo en la posicion n la estructura libro
		
		
	}
}

int Contar(Lista* lista){
	return lista->longitud;
}

int EstaVacia(Lista* lista){
	return lista->cabeza == NULL;
}

void EliminarPrincipio(Lista* lista){
	if(lista->cabeza != NULL){
		//1.- Crear un nodo temporal
		//1.5.- Asignar el nodo.primero a una variable temporal
		Nodo* eliminado = lista->cabeza; 
		//2.- Cambiar el nodo.primero por el nodo.primero.siguiente
		lista->cabeza = lista->cabeza->siguiente;
		//3.- Eliminar / liberar la memoria del nodo.primero o nodo temporal
		EliminarNodo(eliminado);
		lista->longitud--;
	}
}

void EliminarUltimo(Lista* lista){

	// 1.- Crear un nodo temporal para guardar el ultimo actual
	// 2.- Recorrer la lista hasta el penultimo
	// 3.- Liberar memoria o quitar el ultimo nodo
	if(lista->cabeza != NULL){
		if (lista->cabeza->siguiente != NULL){
			Nodo* puntero = lista->cabeza;
			while (puntero->siguiente->siguiente != NULL){
				puntero = puntero->siguiente;
			}

			Nodo* eliminado = puntero->siguiente;
			// De esta forma cambiamos el apuntador siguiente del penultimo a NULL y lo definimos como ultimo
			puntero->siguiente = NULL;
			// Se libera espacion en memoria
			EliminarNodo(eliminado);
			lista->longitud--;
		} else{
			EliminarPrincipio(lista);
		}
	}
}

void EliminarElemento(int n, Lista* lista){
	//Pasos para eliminar de enmedio de la lista
	//1.-Crear un nodo apuntador
	//2.-Crear una variable que cuente en donde estamos en la lista
	//3.- Recorrer la lista hasta n-1
	//4.- Cambiar o asignar el apuntador de nodo n-1 a n+1
	//5.- Eliminar el nodo n

	//Consideraciones
	// C1.- Que pasa si la lista esta vacia
	int longitud = 0;
	if(lista->cabeza != NULL){
		// C2.- Que pasa si la lista tiene una longitud menor al elemento que se pide eliminar
		longitud = Contar(lista);
		if (n < longitud){
			Nodo* puntero = lista->cabeza;
			Nodo* eliminado = lista->cabeza;
			int posicion = 0;
			while(posicion < (n-1)){
				puntero = puntero->siguiente;
				eliminado = puntero-> siguiente->siguiente;
				posicion = posicion ++;
			}
			puntero->siguiente = eliminado->siguiente;
			EliminarNodo(eliminado);	
		}
	}
}

void menu(void){

    cout<<"\n\t\t[    Registro de libros    ]\n";
    cout<<"\t\t----------------------------\n\n";
    cout<<" 1. Registrar libros                          "<<endl;
    cout<<" 2. Listar los libros                             "<<endl;
    cout<<" 3. Eliminar libros                 "<<endl;
    cout<<" 4. Desplegar libros                 "<<endl;
    cout<<" 5. Salir                                       "<<endl;

    cout<<"\n Ingrese opcion : ";
}

int main () {
	int des = 0;
	system("color 0a");
    struct Lista *lista;
    struct Libro *libro;

    int opcion;
	// [1] Agregar un nuevo libro: Preguntar al usuario el titulo, autor e isbn 
	// [2] Listar los libros: titulo | autor | isbn / si no hay elementos, desplegar: tu biblioteca esta vacia
	// [3] Eliminar libro: Preguntar donde lo queremos eliminar. 1) Usar un submenu / 2) Pedir n y verificar si n=0 eliminar el principio, si n = long(lista) elimanr el final sino eliminan en la posicion n
	// [4] Cuantos libros tengo? : Desplegar los libros
	do{
	    menu();
	    cin>>opcion;
        switch(opcion){

                case 1: 
                        cout<<"\n\n\t\t[  Registro  ]\n";
                        cout<<"\t\t------------";
                        cout<<"\n\tDatos del libro ";
                        cin.ignore();cout<<"\n\tTitulo:"; cin.getline(libro->titulo,50);
                        cin.ignore();cout<<"\tAutor:"; cin.getline(libro->autor,50);
                        cin.ignore();cout<<"\tISBN:"; cin.getline(libro->isbn,15);
                        InsertarPrincipio(lista,libro);
                        break;

                case 2: 
                        break;

                case 3: 
                        break;

                case 4: 
                        break;
                case 5: return 0;


                default: cout<<"\nINGRESE UNA OPCION VALIDA...\n"; break;

            }

            system("pause");  system("cls");
		
	}while(opcion != 6);
	
	system("pause");
	
	return 0;
}
