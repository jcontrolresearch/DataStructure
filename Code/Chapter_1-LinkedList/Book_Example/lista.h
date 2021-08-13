//lista.h
//Clase para describir una lista
//Autor: Julio M
//

#ifdef lista_h
#define lista_h

#include <stdio.h>
#include "libro.h"

// Para crear una estructura de nodo
typedef struct Nodo {
	Libro libro;
	struct Nodo* siguiente;
} Nodo;

typedef struct Nodo2 {
	int num;
	struct Nodo* siguiente;
} Nodo;

//Para crear una lista

typedef struct Lista {
	Nodo* primero;
} Lista;


#endif
