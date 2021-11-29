#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//Rafael Santiago Avendaño.
//Problema de algoritmos de ordenamiento.
//Profe quiero comentarle que si logre hacer las funciones como puede ver, sin errores,
//pero no pude lograr imprimirlas, igual tuve que hacer desde cero todo el proyecto de colas,
//lo que me llevo mas tiempo porque el que hice en equipo en el segundo parcial estaba incompleto, 
//le doy las gracias por su atencion y espero pueda tomar a consideracion lo elaborado.

//--------------------------ESTRUCTURAS------------------------------

typedef struct Lineapedido {              //se crea una estructura de productos que estaran en nuestros pedidos
    int id_producto;
    int cantidad;
    float precio_unidad;
} Lineapedido;

typedef struct Nodolineapedido {          //creamos la estructura del nodo de los productos
  Lineapedido linea;
  struct Nodolineapedido* siguiente;
} Nodolineapedido;

typedef struct Pedido {                   //es la estructura que contiene el id y la lista con los productos de nuestro pedido
  int id_cliente;
  float precio_total;
  Nodolineapedido* lista;
} Pedido;

//Para crear un nodo pedido
typedef struct NodoPedido {
  Pedido* pedido;
  struct NodoPedido* siguiente;
}NodoPedido;

	
typedef struct Carrito{
    Nodolineapedido* primero;
    int longitud;
    struct Lineapedido;
}Carrito;

//Para crear una estructura cola
typedef struct Cola {
  NodoPedido* primer;
  NodoPedido* ultimo;
}Cola;

//--------------------------FUNCIONES------------------------------

NodoPedido* CrearNodo(Pedido* pedido){
  NodoPedido* nodo = (NodoPedido *) malloc(sizeof (NodoPedido));
  nodo->pedido = pedido;
  nodo->siguiente = NULL;
  return nodo;
}

void DestruirNodo(NodoPedido* nodo){
  nodo->pedido = NULL;
  nodo->siguiente = NULL;
  free(nodo);
}

Cola* CrearCola(){
  Cola* cola = (Cola *) malloc(sizeof(Cola));
  cola->primer = cola->ultimo = NULL;
  return cola;
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

void DestruirCola(Cola* cola){
  while (cola->primer){
    Eliminar(cola);
  }
  free(cola);
}

void Encolar(Cola* cola, Pedido* pedido){
  NodoPedido* nodo = CrearNodo(pedido);
  if(!cola->primer){
    cola->primer = nodo;
    cola->ultimo = nodo;
  }else {
    cola->ultimo->siguiente = nodo;
    cola->ultimo = nodo;
  }
}

int ObtenerLongitud(Cola* cola){
	int longitud = 0;
	NodoPedido* nodo;
	nodo = cola->primer;
	nodo = cola->ultimo;
	while(nodo->siguiente != NULL){
		nodo = nodo->siguiente;
		longitud++;
	}
	return longitud;
}

Pedido* Consultar(Cola* cola){
  if(cola->primer){
    return cola->primer->pedido;
  }else {
    return NULL;
  }
}
void insertar_colas();

void imprimir_colas(Cola* cola){
	NodoPedido *imc = NULL;
	imc = cola->primer;
	if(imc==NULL){
		printf("\nLista vacia\n");
        return ;
	}else {
		while (imc != NULL){ 
            printf("[%i], ", imc->pedido->id_cliente);
            imc = imc->siguiente;
        }
        printf("NULL");
	}
}

//--------------------------FUNCIONES DE ORDENAMIENTO------------------------------


void Seleccion(Cola* cola) {
  NodoPedido *x = cola->primer;
  while(x != NULL) {
    NodoPedido *y = x->siguiente;
    while(y != NULL) {
      if(x->pedido->id_cliente > y->pedido->id_cliente) {
        int tmp = x->pedido->id_cliente; //una variable temporal para hacer el cambio
    	x->pedido->id_cliente = y->pedido->id_cliente;
    	y->pedido->id_cliente = tmp;
      }
      y=y->siguiente;
      
    }
    x=x->siguiente;
    printf("\nLa cola ordenada por selccion es: \n");
  }
}


void Burbuja(Cola* cola) {
 NodoPedido *x = cola->primer;
  while(x != NULL) {
    NodoPedido *y = x->siguiente;
    while(y != NULL) {
      if(x->pedido->id_cliente > y->pedido->id_cliente) {
        int tmp = x->pedido->id_cliente; //una variable temporal para hacer el cambio
    	x->pedido->id_cliente = y->pedido->id_cliente;
    	y->pedido->id_cliente = tmp;
      }
      y=y->siguiente;
      
    }
    x=x->siguiente;
    printf("\nLa cola ordenada por burbuja es: \n");
    NodoPedido *imc = NULL;
	imc = cola->primer;
	if(imc==NULL){
		printf("\nLista vacia\n");
        return ;
	}else {
		while (imc != NULL){ 
            printf("[%i], ", imc->pedido->id_cliente);
            imc = imc->siguiente;
        }
        printf("NULL");
	}
  }
}

int main() {
	
	NodoPedido *nodopedido = NULL;


	int cantidad_producto, eleccion, id_clientepedido,contador=0;
	Cola cola={.primer=NULL,.ultimo=NULL};
		cantidad_producto = 0;
		
		Pedido pedidoA = {056, 342.00, NULL};
		Pedido pedidoB = {015, 1000.99, NULL};
		Pedido pedidoG = {162, 14253.23, NULL};
		Pedido pedidoD = {104, 200.15, NULL};
		
		printf("\n--------------ID PEDIDOS--------------\n");

		Encolar(&cola, &pedidoA);
		printf("\n[%d, ", cola.primer->pedido->id_cliente);
		
		Encolar(&cola, &pedidoB);
		printf("%d, ", cola.ultimo->pedido->id_cliente);
		
		Encolar(&cola, &pedidoG);
		printf("%d, ", cola.ultimo->pedido->id_cliente);
		
		Encolar(&cola, &pedidoD);
		printf("%d]\n", cola.ultimo->pedido->id_cliente);
		
		printf("\n----------------------------\n");
		printf("\nLa cola ordenada por seleccion es: \n");
//		Selecion(&cola, &pedidoA);
//  	printf("\n");
		printf("\nLa cola ordenada por burbuja es: \n");
//  	Burbuja(&cola, &pedidoA);
//  	printf("\n");

  return 0;
}
