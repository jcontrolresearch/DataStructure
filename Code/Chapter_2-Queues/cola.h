// Cola.h
//
//
// Created by Julio Martinez
// Copyright @ 2021 Julio Martinez. All rights reserved
//

#ifndef cola_h
#define cola_h

#include <stdio.h>
#include "pedido.h"

typedef struct NodoPedido {
	Pedido* pedido;
	struct NodoPedido* siguiente;
}NodoPedido;

typedef struct Cola {
	NodoPedido* primero;
	NodoPedido* ultimo;
}Cola;

// Funciones para usan en las colas

// Funciones primitivas
// Definicion de funcion para crear cola
Cola* CrearCola();

//Definicion de funcion para Destruir cola
void DestruirCola(Cola* cola);

//Definicion de funcion para funciones basicas de colas, como se vio en diapositivas

//Definicion de funcion para encolar
void Encolar(Cola* cola, Pedido* pedido);
Pedido* Consultar(Cola* cola);
void Eliminar(Cola* cola);

// Funciones compuestas
// Definicion de funcion despachar

Pedido* Despachar(Cola* cola);


#endif /*cola_h*/