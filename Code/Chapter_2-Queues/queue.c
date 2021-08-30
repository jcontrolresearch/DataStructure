//queue.cpp
//Definicion de funciones para el uso de colas
//Autor: Julio M
//


//#ifndef queue.h
//#define queue.h

#include <stdio.h>
#include <stdlib.h>

// Contexto: Imagine una linea de pedidos de comida (tipo uber eats/rappi).
// La linea de pedidos puede contener las siguientes estructuras

typedef struct Producto {
	int id_producto;
	int cantidad;
	float precio_unidad;
}Producto;

typedef struct NodoProducto {
	Producto producto;
	struct NodoProducto* siguiente;
}NodoProducto;

typedef struct Pedido {
	int id_cliente;
	NodoProducto* lista_productos;
}Pedido;

// Estructuras de la cola

typedef struct NodoPedido {
	Pedido* pedido;
	struct NodoPedido* siguiente;
} NodoPedido;

// por que es importante declarar el principio y el final de la cola?
typedef struct Cola {
	NodoPedido* primer;
	NodoPedido* ultimo;
} Cola;

//********************* Definicion de funciones*******************

// Funciones para crear/destruir un nodo
NodoPedido* CrearNodo(Pedido* pedido);
void DestruirNodo(NodoPedido* pedido);

//Funciones para crear / destruir colas
Cola* CrearCola();
void DestruirCola(Cola* cola);

// Funciones para hacer operaciones con las colas
void Encolar(Cola* cola, Pedido* pedido);
Pedido* Consultar(Cola* cola);
void Eliminar(Cola* cola);

Pedido* Despachar(Cola* cola);

// *************** Implementacion de funciones  **********************

NodoPedido* CrearNodo(Pedido* pedido){
	//Primer paso es definir la memoria dinamica que va a ocupar el nodo
	//El tama~no de memoria para el nodo esta definido por el tama~no de la estructura nodo en "lista.h"
	NodoPedido* nodo = (NodoPedido *)malloc(sizeof (NodoPedido));
	nodo->pedido = pedido;
	nodo->siguiente = NULL;
	return nodo;
}


// Funcion para eliminar un nodo

void DestruirNodo(NodoPedido* nodo){
	// Como se libera memoria en lenguaje C?
	// Usar free para liberar o "quitar" espacios de memoria previamente llenados con unciones malla(), calloc() o realloc()
	nodo->pedido = NULL;
	nodo->siguiente = NULL;
	free(nodo);
}

// Funcion para crear una cola

Cola* CrearCola(){
	Cola* cola = (Cola *)malloc(sizeof(Cola));
	cola->primer = cola->ultimo;
	return cola;
}

// Funcion para elimanr cola

void DestruirCola(Cola* cola){
	while(cola->primer){
		Eliminar(cola);
	}
	free(cola);
}

// Funcion para Encolar

void Encolar(Cola* cola, Pedido* pedido){
	NodoPedido* nodo = CrearNodo(pedido);
	if(!cola->primer) {
		cola->primer = nodo;
		cola->ultimo = nodo;
	} else {
		cola->ultimo->siguiente = nodo;
		cola->ultimo=nodo;
	}
}


// Funcion para consultar un pedido/cola

Pedido* Consultar(Cola* cola) {
	if (cola->primer) {
		return cola->primer->pedido;
	} else {
		return NULL;
	}
}

// Funcion para eliminar una cola

void Eliminar(Cola* cola){
	if (cola->primer){
		NodoPedido * eliminado = cola->primer;
		cola->primer = cola->primer->siguiente;
		DestruirNodo(eliminado);
		if (!cola->primer){
			cola->ultimo = NULL;
		}
	}
}



int main(){
	return 0;
}

//#endif /*queue.h*/
