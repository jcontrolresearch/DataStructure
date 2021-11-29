// Estructuras necesarias

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

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
Pedido* Despachar(Cola* cola);

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

void menu(void){

    printf("\n\t\t[    Registro de pedidos    ]\n");
    printf("\t\t-----------------------------\n\n");
    printf(" 1. Mostrar productos                                       \n");
    printf(" 2. Registrar pedido                          \n");
    printf(" 3. Mostrar ticket                             \n");
    printf(" 4. Eliminar pedido                 \n");
    printf(" 5. Salir                                       \n");
    printf("\n Ingrese opcion : ");
}

void productos(void){
	printf("\n\t\t[    Hot Fire Burguer    ]\n");
	printf("\t\t-------------------------\n\n");
	printf(" 1.Hamburguesa sencilla    001\n");
	printf(" \tCon un costo de $45 pesos\n\n");
    printf(" 2.Hamburguesa Hawaiana    002\n");
    printf(" \tCon un costo de $55 pesos\n\n");
    printf(" 3.Hamburguesa de Tocino   003\n");
    printf(" \tCon un costo de $55 pesos\n\n");
    printf(" 4.Hamburguesa de Champiñones 004\n");
    printf(" \tCon un costo de $65 pesos\n\n");
    printf(" 5.Hamburguesa Especial    005\n");
    printf(" \tCon un costo de $65 pesos\n\n");
    printf(" 6.Hamburguesa Oaxaqueña   006\n");
    printf(" \tCon un costo de $65 pesos\n\n");
    printf(" 7.Hamburguesa al Pastor   007\n");
    printf(" \tCon un costo de $65 pesos\n\n");
    printf(" 8.Hamburguesa Big Burguer 008\n");
    printf(" \tCon un costo de $75 pesos\n\n");
    printf(" 9.Hamburguesa Cubana      009\n");
    printf(" \tCon un costo de $75 pesos\n\n");
    printf(" 10.Papas a la Francesa    010\n");
    printf(" \tCon un costo de $35 pesos\n\n");
}

void Mostrar_pedido(Cola* cola){
	int i=0;
    NodoPedido* puntero = cola->primer;
    while(puntero->siguiente){
        puntero = puntero->siguiente;
        printf("\n\tDatos del pedido [%d] \n",i+1);
        printf("\t\t------------------------\n\n");
        printf("\t\tId del cliente   : \n");
        printf("\t\t   : \n");
        printf("\t\t   : \n");			
        i++;
		}
}

int main(){
	int opcion,ipedido;
	char repe;
	float costo;
	system("color 0a");
	Cola cola = {.primer = NULL,.ultimo = NULL};
	Producto hamburguesa_sencilla = {.id_producto=001, .cantidad=1, .precio_unidad = 45.00};
	Producto hamburguesa_hawaiana = {.id_producto=002, .cantidad=1, .precio_unidad = 55.00};
	Producto hamburguesa_tocino = {.id_producto=003, .cantidad=1, .precio_unidad = 55.00};
	Producto hamburguesa_champ = {.id_producto=004, .cantidad=1, .precio_unidad = 65.00};
	Producto hamburguesa_especial = {.id_producto=005, .cantidad=1, .precio_unidad = 65.00};
	Producto hamburguesa_oax = {.id_producto=006, .cantidad=1, .precio_unidad = 65.00};
	Producto hamburguesa_pastor = {.id_producto=007, .cantidad=1, .precio_unidad = 65.00};
	Producto hamburguesa_big = {.id_producto=8, .cantidad=1, .precio_unidad = 75.00};
	Producto hamburguesa_cubana = {.id_producto=9, .cantidad=1, .precio_unidad = 75.00};
	Producto papas_francesa = {.id_producto=010, .cantidad=1, .precio_unidad = 75.00};
	Pedido pedido = {.id_cliente = 0,.precio = 0.0,.lista_productos = NULL};
	do{
	menu();
	scanf("%d",&opcion);
	switch(opcion){
                case 1: 
                        productos();
                        break;
                case 2: 
                        productos();
                        do{
                         printf("Elija su opcion por favor   : \n");
                         scanf("%d",&ipedido);
                          if(ipedido == 1){
						 	printf("El id del producto es: %d\n",hamburguesa_sencilla.id_producto);
						 	printf("El costo del producto es: %f\n",hamburguesa_sencilla.precio_unidad);
						 	fflush(stdin);
						 	printf("Cantidad del producto: ");
						 	scanf("%d",&hamburguesa_sencilla.cantidad);
						 	fflush(stdin);
						 	printf("El precio total del producto es %f",hamburguesa_sencilla.cantidad*hamburguesa_sencilla.precio_unidad);
						 	pedido.precio = hamburguesa_sencilla.cantidad*hamburguesa_sencilla.precio_unidad;
						    Encolar(&cola, &pedido);
						  } else if(ipedido == 2){
						 	printf("El id del producto es: %d\n",hamburguesa_hawaiana.id_producto);
						 	printf("El costo del producto es: %f\n",hamburguesa_hawaiana.precio_unidad);
						 	fflush(stdin);
						 	printf("Cantidad del producto: ");
						 	scanf("%d",&hamburguesa_hawaiana.cantidad);
						 	fflush(stdin);
						 	printf("El precio total del producto es %f",hamburguesa_hawaiana.cantidad*hamburguesa_hawaiana.precio_unidad);
						 	pedido.precio = hamburguesa_hawaiana.cantidad*hamburguesa_hawaiana.precio_unidad;
						    Encolar(&cola, &pedido);
						  } else if(ipedido == 3){
						 	printf("El id del producto es: %d\n",hamburguesa_tocino.id_producto);
						 	printf("El costo del producto es: %f\n",hamburguesa_tocino.precio_unidad);
						 	fflush(stdin);
						 	printf("Cantidad del producto: ");
						 	scanf("%d",&hamburguesa_tocino.cantidad);
						 	fflush(stdin);
						 	printf("El precio total del producto es %f",hamburguesa_tocino.cantidad*hamburguesa_tocino.precio_unidad);
						    Encolar(&cola, &pedido);
						  } else if(ipedido == 4){
						 	printf("El id del producto es: %d\n",hamburguesa_champ.id_producto);
						 	printf("El costo del producto es: %f\n",hamburguesa_champ.precio_unidad);
						 	fflush(stdin);
						 	printf("Cantidad del producto: ");
						 	scanf("%d",&hamburguesa_champ.cantidad);
						 	fflush(stdin);
						 	printf("El precio total del producto es %f",hamburguesa_champ.cantidad*hamburguesa_champ.precio_unidad);
						    Encolar(&cola, &pedido);
					      } else if(ipedido == 5){
						 	printf("El id del producto es: %d\n",hamburguesa_especial.id_producto);
						 	printf("El costo del producto es: %f\n",hamburguesa_especial.precio_unidad);
						 	fflush(stdin);
						 	printf("Cantidad del producto: ");
						 	scanf("%d",&hamburguesa_especial.cantidad);
						 	fflush(stdin);
						 	printf("El precio total del producto es %f",hamburguesa_especial.cantidad*hamburguesa_especial.precio_unidad);
						    Encolar(&cola, &pedido);
					      } else if(ipedido == 6){
						 	printf("El id del producto es: %d\n",hamburguesa_oax.id_producto);
						 	printf("El costo del producto es: %f\n",hamburguesa_oax.precio_unidad);
						 	fflush(stdin);
						 	printf("Cantidad del producto: ");
						 	scanf("%d",&hamburguesa_oax.cantidad);
						 	fflush(stdin);
						 	printf("El precio total del producto es %f",hamburguesa_oax.cantidad*hamburguesa_oax.precio_unidad);
						    Encolar(&cola, &pedido);
					      } else if(ipedido == 7){
						 	printf("El id del producto es: %d\n",hamburguesa_pastor.id_producto);
						 	printf("El costo del producto es: %f\n",hamburguesa_pastor.precio_unidad);
						 	fflush(stdin);
						 	printf("Cantidad del producto: ");
						 	scanf("%d",&hamburguesa_pastor.cantidad);
						 	fflush(stdin);
						 	printf("El precio total del producto es %f",hamburguesa_pastor.cantidad*hamburguesa_pastor.precio_unidad);
						    Encolar(&cola, &pedido);
					      } else if(ipedido == 8){
						 	printf("El id del producto es: %d\n",hamburguesa_big.id_producto);
						 	printf("El costo del producto es: %f\n",hamburguesa_big.precio_unidad);
						 	fflush(stdin);
						 	printf("Cantidad del producto: ");
						 	scanf("%d",&hamburguesa_big.cantidad);
						 	fflush(stdin);
						 	printf("El precio total del producto es %f",hamburguesa_big.cantidad*hamburguesa_big.precio_unidad);
						    Encolar(&cola, &pedido);
					      } else if(ipedido == 9){
						 	printf("El id del producto es: %d\n",hamburguesa_cubana.id_producto);
						 	printf("El costo del producto es: %f\n",hamburguesa_cubana.precio_unidad);
						 	fflush(stdin);
						 	printf("Cantidad del producto: ");
						 	scanf("%d",&hamburguesa_cubana.cantidad);
						 	fflush(stdin);
						 	printf("El precio total del producto es %f",hamburguesa_cubana.cantidad*hamburguesa_cubana.precio_unidad);
						    Encolar(&cola, &pedido);
					      } else if(ipedido == 10){
						 	printf("El id del producto es: %d\n",papas_francesa.id_producto);
						 	printf("El costo del producto es: %f\n",papas_francesa.precio_unidad);
						 	fflush(stdin);
						 	printf("Cantidad del producto: ");
						 	scanf("%d",&papas_francesa.cantidad);
						 	fflush(stdin);
						 	printf("El precio total del producto es %f",papas_francesa.cantidad*papas_francesa.precio_unidad);
						    Encolar(&cola, &pedido);
					      }
						 printf("Desea agregar otro pedido? [S/N]");
						  scanf("%c",&repe);
						  fflush(stdin);
						 printf("id del cliente: \n");
						     scanf("%d",&pedido.id_cliente);	
						 	fflush(stdin);
						}while((repe == 'S')&&(repe != 'N'));
                        break;
                case 3: 
                        Mostrar_pedido(&cola);
                        break;
                case 4: 
                        Eliminar(&cola);
                        break;
                case 5:
                	    return 0;
                default: printf("\nINGRESE UNA OPCION VALIDA...\n"); 
				 break;
            }
            system("pause");  system("cls");		
	}while(opcion != 6);
	system("pause");
	return 0;
}

