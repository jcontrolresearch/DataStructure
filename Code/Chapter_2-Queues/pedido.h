// Pedido.h
//
//
// Created by Julio Martinez
// Copyright @ 2021 Julio Martinez. All rights reserved
//

#ifdef pedido_h
#define pedido_h

#include <stdio.h>


// Estructura que define un pedido, esta puede incluir:
// el id del producto
// la cantidad de producto
// el precio unitario del producto
typedef struct LineaPedido {
	int id_producto;
	int cantidad;
	float precio_unitario;
} LineaPedido;

// Funcion que define un nodo en la linea de pedido
typedef struct NodoLineaPedido {
	LineaPedido linea;
	struct NodoLineaPedido* siguiente;
} NodoLineaPedido;

// Funcion que defin un cliente/pedido en la linea de pedido
typedef struct Pedido {
	int id_cliente;
	NodoLineaPedido* lista_productos;
} Pedido;

#endif /*pedido_h*/