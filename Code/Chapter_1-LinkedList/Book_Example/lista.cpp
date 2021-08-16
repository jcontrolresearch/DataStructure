//lista.cpp
//Definicion de funciones para el uso de listas
//Autor: Julio M
//

#include "lista.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include "libro.h"

#include <stdio.h>

typedef struct Libro {
	char titulo[50];
	char autor[50];
	char isbn[15];
} Libro;


// Para crear una estructura de nodo
typedef struct Nodo {
	Libro libro;
	struct Nodo* siguiente;
} Nodo;

typedef struct Nodo2 {
	int num;
	struct Nodo* siguiente;
} Nodo2;

//Para crear una lista

typedef struct Lista {
	Nodo* primero;
} Lista;


//Funcion para crear un nuevo nodo

//Consideraciones
// 1.- La funcion debe regresar un nodo
// 2.- La entrada debe cualquier tipo de dato con el cual se haya definido el nodo

Nodo* CrearNodo(Libro* libro){
	//Primer paso es definir la memoria dinamica que va a ocupar el nodo
	//El tama~no de memoria para el nodo esta definido por el tama~no de la estructura nodo en "lista.h"
	Nodo* nodo = (Nodo *)malloc(sizeof (Nodo));
	//Pasar la informacion del libro al nodo.libro con string copy -> strcpy
	strcpy(nodo->libro.titulo, libro->titulo);
	strcpy(nodo->libro.autor, libro->autor);
	strcpy(nodo->libro.isbn, libro->isbn);
	
	return nodo;
}


// Funcion para eliminar un nodo

void EliminarNodo(Nodo* nodo){
	// Como se libera memoria en lenguaje C?
	// Usar free para liberar o "quitar" espacios de memoria previamente llenados con unciones malla(), calloc() o realloc()
	free(nodo);
}

//*************************** Metodos de insercion ***************************************

// Metodo de insertar al princio
void InsertarPrincipio(Lista* lista, Libro* libro){
	// 1.- Crear el nuevo nodo
	Nodo* nodo = CrearNodo(libro);
	// 2.- Asignar el siguiente del nuevo nodo a la primero de la lista
	// El objeto lista->primero es el primero de la lista
	// El objeto nodo->siguiente es el apuntador al nodo siguiente
	nodo->siguiente = lista->primero;
	// 3.- Debemos cambiar la referenia primero de la lista actual al nuevo nodo
	 lista->primero = nodo;
}

// Metodo de insertar al final

void InsertarFinal(Lista* lista, Libro* libro){
	// 1.- Crear un nuevo nodo
	Nodo* nodo = CrearNodo(libro);
	
	// Que pasa si la lista esta vacia?
	// para saber si la lista esta vacia basta con revisar el primer elemento
	if(lista->primero == NULL){
		lista->primero = nodo;
	} else{
		// 2.- Recorrer la lista hasta el final
		// Creamos una variable auxiliar para recorer la lista desde el principio
		Nodo* puntero = lista->primero;
		while(puntero->siguiente == NULL){
			puntero = puntero->siguiente;
		}
		//Paso 3.- Hacer que el ultimo objeto de la lista apunte al nodo nuevo
		puntero->siguiente = nodo;
		nodo->siguiente = NULL;
	}
}


// Insertar un nuevo nodo en la posicion n de la lista
void InsertarMedio(int n, Lista* lista, Libro* libro){
	// 1.- Crear un nuevo nodo
	Nodo* nodo = CrearNodo(libro);
	if(lista->primero == NULL){
		lista->primero = nodo;
	} else{
		// 2.- Recorrer la lista hasta el n-esimo elemento
		int posicion = 0;
		Nodo* puntero = lista->primero;
		// Evaluamos que la lista tenga suficientes elementos para insertar el nuevo nodo y que lleguemos a la posicion
		// donde queemos insertar le nuevo nodo
		while(puntero->siguiente != NULL && posicion < n){
			puntero = puntero->siguiente;
			posicion ++;
		}
		nodo->siguiente = puntero->siguiente;
		puntero->siguiente = nodo;
	}
}

// Que pasa si quisieramos saber que libro n esta en la lista?

//Funcion para obtener un libro

Libro* ObternerLibro(int n, Lista* lista){
	if(lista->primero == NULL){
		//la lista no tiene nada
		return NULL;
	} else {
		// Crear un nodo al que llamaremos puntero y le asignamos el primero elemento de la lista
		Nodo* puntero = lista->primero;
		int pos = 0;
		// Recorrer la lista hasta que la posicion sea igual que n y que el siguiente no sea NULL o en otras palabras
		// que eistan elementos en la lista 
		while( pos < n && puntero->siguiente ){
			puntero = puntero->siguiente;
			pos ++;
		}
		// Retornar del nodo en la posicion n la estructura libro
		return &puntero->libro;
		
	}
}


int main () {
	printf("Listas enlazadas");
	return 0;
}


