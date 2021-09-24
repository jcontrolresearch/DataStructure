// Estructuras necesarias

#include <stdio.h>
#include <stdlib.h>

// **********************************************************************************
// Para definir las estructuras de los productos

// Estructura producto.
// Representa un producto con su identificador (nombre) | cantidad | precio unitario
typedef struct Producto {
	int id_producto;
	int cantidad;
	float precio_unidad;
}Producto;

// Estructura para embeber el producto en un nodo
typedef struct NodoProducto {
	Producto producto;
	struct NodoProducto* siguiente;
}NodoProducto;

// Estructura para embutir un pedido
typedef struct Pedido {
	int id_cliente;
	float precio;
	NodoProducto* lista_productos;
}Pedido;

//***********************************************************************************
// Definicion de la estructura nodo pedido
typedef struct NodoPedido {
	Pedido* pedido;
	struct NodoPedido* siguiente;
} NodoPedido;

// Definicion de la estrcutura cola
typedef struct Cola {
	NodoPedido* primer;
	NodoPedido* ultimo;
} Cola;

//*************************************************************************************

// Funciones de nodos
NodoPedido* CrearNodo(Pedido* pedido);
void DestruirNodo(NodoPedido* pedido);

// Funciones de colas
Cola* CrearCola();
void DestruirCola(Cola* cola);

// Funciones para hacer operaciones con las colas

void Encolar(Cola* cola, Pedido* pedido);
Pedido* Consultar(Cola* cola);
// Como sabes que simepre va a eliminar al principio, no es necesario pasar como argumento algun pedido
void Eliminar(Cola* cola);

// Esta funcion es una combinacion de Consultar y ELiminar, previamente definidas
// Pedido* Despachar(Cola* cola)


// Funcion para crear un NodoPedido
NodoPedido* CrearNodo(Pedido* pedido){
	NodoPedido* nodo = (NodoPedido *)malloc(sizeof (NodoPedido));
	nodo->pedido = pedido;
	nodo->siguiente = NULL;
}

// Funcion para eliminar memoria

void DestruirNodo(NodoPedido* nodo){
	// Hacer que los datos de la estructura pedido apunten a NULL para eliminar los posibles valores del pedido
	nodo->pedido = NULL;
	// El siguiente de NodoPedido apunte a NULL por que siempre se procesa al princio de la cola
	nodo->siguiente = NULL;
	// Se libera la memoria
	free(nodo);
}


// Funcion para crear una cola

Cola* CrearCola(){
	Cola* cola = (Cola *)malloc(sizeof (Cola));
	// Como deben ser los valores de los campos de la estructura Cola
	cola->primer = cola->ultimo;
	return cola;
}

// Funcion para destruir una cola

void DestruirCola(Cola* cola){
	while(cola->primer){
		Eliminar(cola);
	}
	free(cola);
}

// Funcion para a;adir elementos a la cola
void Encolar(Cola* cola, Pedido* pedido){
	NodoPedido* nodo = CrearNodo(pedido);
	// Si el campo primer de la cola esta vacio, quiere decir que la cola no tiene ningun pedido
	if(!cola->primer){
		cola->primer = nodo;
		cola->ultimo = nodo;
	} else{
		cola->ultimo->siguiente = nodo;
		cola->ultimo = nodo;
	}
}

// Funcion para consultar un pedido
Pedido* Consultar(Cola* cola){
	if(cola->primer){
		return cola->primer->pedido;	
	} else{
		return NULL;
	}
}

// Funcion para eliminar de una cola
void Eliminar(Cola* cola){
	// 1. Verificar que la cola tenga ala menos el primer pedido 
	if(cola->primer){
		// Asignamos el nodo a elimanr en un nodo temporal
		NodoPedido* eliminado = cola->primer;
		// Cambiamos el primer de la cola al suigiente del primero
		cola->primer = cola->primer->siguiente;	
		// se borra el nodo
		DestruirNodo(eliminado);
		//SI el nodo que se borro era el unico de la cola -> tambien era el ultimo
		if(!cola->primer){
			cola->ultimo = NULL;
		}
	}
}



int main(){
	/*
	[lineamientos del programa]
	[1] Cliente
	*/
	return 0;
}

