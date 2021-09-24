//Angel Hernandez Gomez, Octavio Hernandez Luna
//Roberto Quintana Ramirez, Alan Guzman Serret
//Angel Hiram Torres Santiago
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estructuras
//estructura producto
typedef struct Producto {
	int id_producto;
	int cantidad;
	float precio_unidad;
}Producto;

// Estructura para agregar el producto en un nodo
typedef struct NodoProducto {
	Producto producto;
	struct NodoProducto* siguiente;
}NodoProducto;

//Estructura carrito -- Nueva
typedef struct Carrito {
	NodoProducto* primero;
	int longitud;
} Carrito;

// Estructura para agregar un pedido
typedef struct Pedido {
	int id_cliente;
	float precio;
	Carrito* lista_productos;
}Pedido;

//***********************************************************************************
//estructura nodo pedido
typedef struct NodoPedido {
	Pedido* pedido;
	struct NodoPedido* siguiente;
} NodoPedido;

//estrcutura cola
typedef struct Cola {
	NodoPedido* primer;
	NodoPedido* ultimo;
} Cola;

//*************************************************************************************
// Funciones de nodos

// Como sabes que simepre va a eliminar al principio, no es necesario pasar como argumento algun pedido
//Despachar elementos de la cola
// Esta funcion es una combinacion de Consultar y ELiminar, previamente definidas
// Pedido* Despachar(Cola* cola)


// Funcion para crear un NodoPedido
NodoPedido* CrearNodo(Pedido* pedido){
	//Definir el tamaño del NodoPedido
	NodoPedido* nodo = (NodoPedido *)malloc(sizeof (NodoPedido));
	//Asignar valores a nuestro nodo pedido conforme a la estructura
	nodo->pedido = pedido;
	nodo->siguiente = NULL;
}
//Funcion nodo producto -- Nueva
	NodoProducto* CrearNodoProducto(Producto* producto){
		//Primer paso es definir la memoria dinamica que va a ocupar el nodo
		//El tamañno de memoria para el nodo esta definido por el NodoProducto
		NodoProducto* nodo = (NodoProducto *)malloc(sizeof (NodoProducto));
		//Apuntar a los datos de la estructura
		nodo->producto.id_producto = producto->id_producto;
		nodo->producto.cantidad = producto->cantidad;
		nodo->producto.precio_unidad = producto->precio_unidad;
		nodo->siguiente = NULL;
		return nodo;
	}

	// Funcion para eliminar un nodo
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

			// Funcion para eliminar de una cola
				void Eliminar(Cola* cola){
					// 1. Verificar que la cola tenga al menos el primer pedido
					if(cola->primer){
						// Asignamos el nodo a eliminar en un nodo temporal
						NodoPedido* eliminado = cola->primer;
						// Cambiamos el primero de la cola al siguiente del primero
						cola->primer = cola->primer->siguiente;	
						// se borra el nodo
						DestruirNodo(eliminado);
						//SI el nodo que se borro era el unico de la cola -> tambien era el ultimo
						if(!cola->primer){
							cola->ultimo = NULL;
						}
					}
				}

					// Funcion para destruir una cola
					void DestruirCola(Cola* cola){
						while(cola->primer){
							Eliminar(cola);
						}
						free(cola);
					}

	//Funcion agregar carrito -- Nueva
	void InsertarFinal(Carrito* carrito, Producto* producto){
		// 1.- Crear un nuevo nodo
		NodoProducto* nodo = CrearNodoProducto(producto);
		//Si no hay elementos en la lista
		if(carrito->primero == NULL){
			nodo->siguiente = carrito->primero;
			carrito->primero = nodo; 
			carrito->longitud = carrito->longitud+1;
		} else{
			// 2.- Recorrer la lista hasta el final
			// Creamos una variable auxiliar para recorer la lista desde el principio
			NodoProducto* puntero = carrito->primero;
			while(puntero->siguiente){
				puntero = puntero->siguiente;
			}
			//Paso 3.- Hacer que el ultimo objeto de la lista apunte al nodo nuevo
			puntero->siguiente = nodo;
			nodo->siguiente = NULL;
			carrito->longitud=carrito->longitud+1;
		}
	}

		void Encolar(Cola* cola, Pedido* pedido){
			NodoPedido* nodo = CrearNodo(pedido);
			//printf("\n%d\n", pedido->id_cliente);
			// Si el campo primer de la cola esta vacio, quiere decir que la cola no tiene ningun pedido
			if(!cola->primer){
				cola->primer = nodo;
				cola->ultimo = nodo;
			} else{
				cola->ultimo->siguiente=nodo;
				cola->ultimo = nodo;
			}
		}
		
		// Funcion para consultar un pedido
		Pedido* Consultar(Cola* cola){
			if(cola->primer){
				int id_cl_p = cola->primer->pedido->id_cliente;
				int id_cl_f = cola->ultimo->pedido->id_cliente;
				return cola->primer->pedido;
			} else{
				return NULL;
			}
		}
		
int main(int argc, char *argv[]) {
	int selec=0;
	float preciototal=0;
	int op;
	// Crear una lista ligada - Carrito conforme a la estructura
	Carrito carrito = {NULL, 0};
	//Crear una cola - Cola conforme a la estructura
	Cola cola = {NULL,NULL}; //Definimos que esta vacia
	Pedido pedido={0,0,NULL}; //Definimos que esta vacio
	
	//Asignar estrecturas de los productos
		//========== 1 ============//
		Producto Iphone12 = {
			56,
			1,
			19999
		};
		//========== 2 ============//
		Producto Samsung_GalaxyS21 = {
			57,
			5,
			16499
		};
		//========== 3 ============//
		Producto Xiaomi_Mi11 = {
			58,
			3,
			8799
		};
		//========== 4 ============//
		Producto Samsung_GalaxyA21s = {
			59,
			5,
			4017
		};
		//========== 5 ============//
		Producto Redmi_Note10 = {
			60,
			5,
			5999
		};
		printf(" \t=========Bienvenido========= \n");
		printf("\n");
do{	
	do{
			printf(" | [1]Iphone 12 ........... Precio: 19,999 | \n");
			printf(" | [2]Samsung GalaxyS21 ... Precio: 16,499 |\n");
			printf(" | [3]Xiaomi Mi11 ......... Precio: 8,799  |\n");
			printf(" | [4]Samsung GalaxyA21s .. Precio: 4,017  |\n");
			printf(" | [5]Redmi Note 10 ....... Precio: 5,999  |\n");
			printf("\n");
			
			printf("Seleccione el producto a añadir:\n");
			printf("Ingrese [-1] para finalizar pedido\n");
			//debug: para saber si los productos se estan agregando a carrito
			printf("\nProductos en el carrito: %d\n", carrito.longitud);
			
			scanf("%d", &selec);
			printf("\n");
			
		if(selec==1){
			InsertarFinal(&carrito, &Iphone12);
			preciototal+= Iphone12.precio_unidad;
			fflush(stdin);
		}
		if(selec==2){
			InsertarFinal(&carrito, &Samsung_GalaxyS21);
			preciototal+= Samsung_GalaxyS21.precio_unidad;
			fflush(stdin);
		}
		if(selec==3){
			InsertarFinal(&carrito, &Xiaomi_Mi11);
			preciototal+= Xiaomi_Mi11.precio_unidad;
			fflush(stdin);
		}
		if(selec==4){
			InsertarFinal(&carrito, &Samsung_GalaxyA21s);
			preciototal+= Samsung_GalaxyA21s.precio_unidad;
			fflush(stdin);
		}
		if(selec==5){
			InsertarFinal(&carrito, &Redmi_Note10);
			preciototal+= Redmi_Note10.precio_unidad;
			fflush(stdin);
		}
		
	}while(selec!=-1);

	// Una vez que se termine de hacer el Pedido
	//Crear una estructura Pedido
	int id1 = rand(); //Genera ID aleatorio
	printf("%d \n", id1);
	pedido.id_cliente = id1;
	pedido.precio = preciototal;
	pedido.lista_productos = &carrito;
	//Agregar pedido a una cola
	Encolar(&cola, &pedido); //añadi un pedido a la cola

	printf("%d \n", cola.primer->pedido->id_cliente);
	printf("Total de los pedidos: %.2f\n", cola.primer->pedido->precio);
	
	printf("\nIngrese [0] para terminar");
	printf("\nIngrese [1] para hacer otro pedido\n");
	scanf("%i", &op);
	printf("\n");
}while(op!=0);

Pedido* Despachar;
Despachar = Consultar(&cola);

Eliminar(&cola);
printf("\n%d", Despachar->id_cliente);
	return 0;
}

