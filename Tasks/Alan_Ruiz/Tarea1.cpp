#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Estructura producto.
// Representa un producto con su identificador (nombre) | cantidad | precio unitario
typedef struct Producto {
    int id_producto;
    char nombre_producto[50];
    int cantidad;
    float precio_unidad;
    float precio_total;
}Producto;

// Para crear una estructura de nodo
typedef struct NodoProducto {
	Producto producto;
	struct NodoProducto* siguiente;
} NodoProducto;

//Para crear una lista de productos
typedef struct Carrito {
	NodoProducto* primero;
	int longitud;
} Carrito;

typedef struct Pedido {
	int id_cliente;
	float precio;
	Carrito* lista_productos;
} Pedido;


//Para crear un nodo pedido
typedef struct NodoPedido {
	Pedido* pedido;
	struct NodoPedido* siguiente;
}NodoPedido;

//Para crear una estructura cola
typedef struct Cola {
	NodoPedido* primer;
	NodoPedido* ultimo;
}Cola;

//Para crear una estructura pedido

NodoProducto* CrearNodoProducto(Producto* producto){

	//Primer paso es definir la memoria dinamica que va a ocupar el nodo
	//El tama~no de memoria para el nodo esta definido por el tama~no de la estructura nodo en "lista.h"
	NodoProducto* nodo = (NodoProducto *)malloc(sizeof (NodoProducto));
	//Pasar la informacion del libro al nodo.libro con string copy -> strcpy
	nodo->producto.id_producto= producto->id_producto;
	strcpy(nodo->producto.nombre_producto, producto->nombre_producto);
	nodo->producto.cantidad = producto->cantidad;
	nodo->producto.precio_unidad = producto->precio_unidad;
	nodo->producto.precio_total = producto->precio_total;

	// Falta copiar los otros campos
	
	return nodo;
}
	
//Funciones
void InsertarFinal(Carrito* carrito, Producto* producto){
// 1.- Crear un nuevo nodo
NodoProducto* nodo = CrearNodoProducto(producto);


// Que pasa si la lista esta vacia?
// para saber si la lista esta vacia basta con revisar el primer elemento
if(carrito->primero == NULL){
nodo->siguiente=carrito->primero;
carrito->primero = nodo;
//carrito->longitud=carrito->longitud+1;
carrito->longitud++;
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
carrito->longitud++;
}
}

int ObtenerLongitud(Carrito* carrito){
    return carrito->longitud;


}

NodoPedido* CrearNodo(Pedido* pedido){
	//Primer paso es definir la memoria dinamica que va a ocupar el nodo
	//El tama~no de memoria para el nodo esta definido por el tama~no de la estructura nodo en "lista.h"
	NodoPedido* nodo = (NodoPedido *)malloc(sizeof (NodoPedido));
	nodo->pedido = pedido;
	nodo->siguiente = NULL;
	return nodo;
}

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

void DestruirNodo(NodoPedido* nodo){
	// Como se libera memoria en lenguaje C?
	// Usar free para liberar o "quitar" espacios de memoria previamente llenados con unciones malla(), calloc() o realloc()
	nodo->pedido = NULL;
	nodo->siguiente = NULL;
	free(nodo);
}

Pedido* Consultar(Cola* cola) {
	if (cola->primer) {
		return cola->primer->pedido;
	} else {
		return NULL;
	}
}

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

int main()
{    
    Carrito car={NULL,0}; 
	Pedido pedido = {0, 0.0, NULL};
	Cola cola = {NULL, NULL};
//    Producto refresco = {nombre_producto=Refresco,.id_producto=8765,.cantidad=10,.precio_unidad=16.5};
	Producto refresco = {8765,"Refresco",10,16.5};
    Producto yoghurt = {4623,"yoghurt",23,8.5};
    Producto sabritas = {7843,"Sabritas",54,12};
    Producto galletas = {9344,"Galletas",34,13.5};
    Producto paleta = {1565,"Paleta",89,3.5};
    Producto leche = {6456,"Leche",53,16.5};
    Producto jugo = {4435,"Jugo",34,8.5};
    Producto mantequilla = {8233,"Mantequilla",34,15.5};
    Producto cereal = {7634,"Cereal",43,30};
    Producto harina = {2334,"Harina",12,13.90};
    Producto gomitas ={7853,"Gomitas",54,10};
float ref, yog, sab, gall, pal, lec, jug, man, cer, har, gom;
int idl, opcion, opcion2, opcion3, contador=0, i;
float total, total_precio;

do {
	do {
	
    printf("|-------------------- Menu ------------------------|\n");
    printf("|------------------- TIENDA -----------------------|\n");
    printf("|--------------------------------------------------|\n");
    printf("|-------------- Escoje un producto ----------------|\n");
    printf("|--------------------------------------------------|\n");
    printf("|[N.][PRODUCTO]----------------------------[PRECIO]|\n");
    printf("|[1]  REFRESCO ---------------------------- $%.02f |\n", refresco.precio_unidad);
    printf("|[2]  YOGHURT ----------------------------- $%.02f  |\n", yoghurt.precio_unidad);
    printf("|[3]  SABRITAS ---------------------------- $%.02f    |\n", sabritas.precio_unidad);
    printf("|[4]  GALLETAS ---------------------------- $%.02f |\n", galletas.precio_unidad);
    printf("|[5]  PALETA ------------------------------ $%.02f  |\n", paleta.precio_unidad);
    printf("|[6]  LECHE ------------------------------- $%.02f |\n", leche.precio_unidad);
    printf("|[7]  JUGO -------------------------------- $%.02f  |\n", jugo.precio_unidad);
    printf("|[8]  MANTEQUILLA ------------------------- $%.02f |\n", mantequilla.precio_unidad);
    printf("|[9]  CEREAL ------------------------------ $%.02f    |\n", cereal.precio_unidad);
    printf("|[10] HARINA ------------------------------ $%.02f |\n", harina.precio_unidad);
    printf("|[11] GOMITAS ----------------------------- $%.02f    |\n", gomitas.precio_unidad);
    printf("----------------------------------------------------\n");
	printf("\nSi desea salir/cancelar su pedido inserte 0");
    printf("\nPor favor ingrese su seleccion: ");
    scanf( "%i", &opcion);

    
    switch (opcion){
	
	case 0: {
		exit(-1);
	break;
	}

    case 1: {
    	printf("[PRODUCTO]     [ID]     [CANTIDAD]   [PRECIO]");
        printf("\n%s      %i,         %i,       $%.02f", refresco.nombre_producto, refresco.id_producto, refresco.cantidad, refresco.precio_unidad);
        printf("\nInserta la cantidad de refrescos a comprar:\n");
        scanf( "%f", &ref );
        if (ref<refresco.cantidad){
            printf("\nOpcion valida\n");
            refresco.precio_total=ref*refresco.precio_unidad;
            printf("\nEl total de su compra es: $%.02f",refresco.precio_total);
            total_precio+=refresco.precio_total;
            InsertarFinal(&car, &refresco);
        }
        else{
            printf("\nNo hay esa cantidad de productos\n");
        }
    break;
    }
    
    case 2:{
    	printf("[PRODUCTO]     [ID]     [CANTIDAD]   [PRECIO]");
        printf("\n%s      %i,         %i,       $%.02f", yoghurt.nombre_producto, yoghurt.id_producto, yoghurt.cantidad, yoghurt.precio_unidad);
        printf("\nInserta la cantidad de yoghurt a comprar:\n");
        scanf("%f",&yog);
        if(yog<yoghurt.cantidad){
            printf("\nOpcion valida");
            yoghurt.precio_total=yog*yoghurt.precio_unidad;
            printf("\nEl total de su compra es: $%.02f",yoghurt.precio_total);
            total_precio+=yoghurt.precio_total;
			InsertarFinal(&car, &yoghurt);
		}
        else
            printf("\nNo hay esa cantidad de productos");       
    }
    break;
    case 3:{
    	printf("[PRODUCTO]     [ID]     [CANTIDAD]   [PRECIO]");
        printf("\n%s      %i,         %i,       $%.02f", sabritas.nombre_producto, sabritas.id_producto, sabritas.cantidad, sabritas.precio_unidad);
        printf("\nInserta la cantidad de sabritas a comprar:\n");
        scanf("%f",&sab);
        if(sab<sabritas.cantidad){
            printf("\nOpcion valida");
            sabritas.precio_total=sab*sabritas.precio_unidad;
            printf("\nEl total de su compra es: $%.02f",sabritas.precio_total);
            total_precio+=sabritas.precio_total;
			InsertarFinal(&car, &sabritas); 
			}
        else
            printf("\nNo hay esa cantidad de productos");          
    }
    break;
    case 4:{
    	printf("[PRODUCTO]     [ID]     [CANTIDAD]   [PRECIO]");
        printf("\n%s      %i,         %i,       $%.02f", galletas.nombre_producto, galletas.id_producto, galletas.cantidad, galletas.precio_unidad);
        printf("\nInserta la cantidad de galletas a comprar:\n");
        scanf("%f",&gall);
        if(gall<galletas.cantidad){
            printf("\nOpcion valida");
            galletas.precio_total=gall*galletas.precio_unidad;
            printf("\nEl total de su compra es: $%.02f",galletas.precio_total);
            total_precio+=galletas.precio_total;
			InsertarFinal(&car, &galletas);  
		}
        else
            printf("\nNo hay esa cantidad de productos");          
    }
    break;
        case 5:{
    	printf("[PRODUCTO]     [ID]     [CANTIDAD]   [PRECIO]");
        printf("\n%s      %i,         %i,       $%.02f", paleta.nombre_producto, paleta.id_producto, paleta.cantidad, paleta.precio_unidad);
        printf("\nInserta la cantidad de paletas a comprar:\n");
        scanf("%f",&pal);
        if(pal<paleta.cantidad){
            printf("\nOpcion valida");
            paleta.precio_total=pal*paleta.precio_unidad;
            printf("\nEl total de su compra es: $%.02f",paleta.precio_total);
            total_precio+=paleta.precio_total;
			InsertarFinal(&car, &paleta);  
		}
        else
            printf("\nNo hay esa cantidad de productos");          
    }
    break;
    case 6:{
    	printf("[PRODUCTO]     [ID]     [CANTIDAD]   [PRECIO]");
        printf("\n%s      %i,         %i,       $%.02f", leche.nombre_producto, leche.id_producto, leche.cantidad, leche.precio_unidad);
        printf("\nInserta la cantidad de leches a comprar:\n");
        scanf("%f",&lec);
        if(lec<leche.cantidad){
            printf("\nOpcion valida");
            leche.precio_total=lec*leche.precio_unidad;
            printf("\nEl total de su compra es: $%.02f",leche.precio_total);
            total_precio+=leche.precio_total;
			InsertarFinal(&car, &leche);  
		}
        else
            printf("\nNo hay esa cantidad de productos");          
    }
    break;
    case 7:{
    	printf("[PRODUCTO]     [ID]     [CANTIDAD]   [PRECIO]");
        printf("\n%s      %i,         %i,       $%.02f", jugo.nombre_producto, jugo.id_producto, jugo.cantidad, jugo.precio_unidad);
        printf("\nInserta la cantidad de jugos comprar:\n");
        scanf("%f",&jug);
        if(jug<jugo.cantidad){
            printf("\nOpcion valida");
            jugo.precio_total=jug*jugo.precio_unidad;
            printf("\nEl total de su compra es: $%.2f",jugo.precio_total);
            total_precio+=jugo.precio_total;
			InsertarFinal(&car, &jugo);  
		}
        else
            printf("\nNo hay esa cantidad de productos");          
    }
    break;
    case 8:{
    	printf("[PRODUCTO]     [ID]     [CANTIDAD]   [PRECIO]");
        printf("\n%s   %i,         %i,       $%.02f", mantequilla.nombre_producto, mantequilla.id_producto, mantequilla.cantidad, mantequilla.precio_unidad);
        printf("\nInserta la cantidad de mantequillas a comprar:\n");
        scanf("%f",&man);
        if(man<mantequilla.cantidad){
            printf("\nOpcion valida");
            mantequilla.precio_total=man*mantequilla.precio_unidad;
            printf("\nEl total de su compra es: $%.02f",mantequilla.precio_total);
            total_precio+=mantequilla.precio_total;
			InsertarFinal(&car, &mantequilla);  
		}
        else
            printf("\nNo hay esa cantidad de productos");          
    }
    break;
    case 9:{
    	printf("[PRODUCTO]     [ID]     [CANTIDAD]   [PRECIO]");
        printf("\n%s      %i,         %i,       $%.02f", cereal.nombre_producto, cereal.id_producto, cereal.cantidad, cereal.precio_unidad);
        printf("\nInserta la cantidad de cereales a comprar:\n");
        scanf("%f",&cer);
        if(cer<cereal.cantidad){
            printf("\nOpcion valida");
			cereal.precio_total=cer*cereal.precio_unidad;
            printf("\nEl total de su compra es: $%.02f",cereal.precio_total);
            total_precio+=cereal.precio_total;
			InsertarFinal(&car, &cereal);  
        }
        else
            printf("\nNo hay esa cantidad de productos");          
    }
    break;
    case 10:{
    	printf("[PRODUCTO]     [ID]     [CANTIDAD]   [PRECIO]");
        printf("\n%s        %i,         %i,       $%.02f", harina.nombre_producto, harina.id_producto, harina.cantidad, harina.precio_unidad);
        printf("\nInserta la cantidad de harina a comprar:\n");
        scanf("%f",&har);
        if(har<harina.cantidad){
            printf("\nOpcion valida"); 
            harina.precio_total=har*harina.precio_unidad;
            printf("\nEl total de su compra es: $%.02f",harina.precio_total);
            total_precio+=harina.precio_total;
			InsertarFinal(&car, &harina); 
		}
        else
            printf("\nNo hay esa cantidad de productos");          
    }
    break;
    case 11:{
    	printf("[PRODUCTO]     [ID]     [CANTIDAD]   [PRECIO]");
        printf("\n%s       %i,         %i,       $%.02f", gomitas.nombre_producto, gomitas.id_producto, gomitas.cantidad, gomitas.precio_unidad);
        printf("\nInserta la cantidad de gomitas a comprar:\n");
        scanf("%f",&gom);
        if(gom<gomitas.cantidad){
            printf("\nOpcion valida");
            gomitas.precio_total=gom*gomitas.precio_unidad;
            printf("\nEl total de su compra es: $%.02f",gomitas.precio_total);
            total_precio+=gomitas.precio_total;
			InsertarFinal(&car, &gomitas);  
		}
        else
            printf("\nNo hay esa cantidad de productos");          
    }
    break;
    }
    
    printf("\nSi quieres terminar tu compra presiona ( 0 ), si desea ir a la lista de productos presiona ( 1 )\n");
	scanf("%i",&opcion2);
	fflush(stdin);
	} while(opcion2!=0);
		idl = rand();
		//printf("\n%i", idl);
		pedido.id_cliente = idl;
		pedido.precio = total_precio;
		pedido.lista_productos=&car;
		//Meter un pedido a la cola
		Encolar(&cola, &pedido);
		
		//Agregar un pedido
		printf("\nSu ID de Cliente es [%i]", cola.primer->pedido->id_cliente);
		printf("\nUsted ha agregado %d productos", ObtenerLongitud(&car));
		fflush(stdin);
		printf("\nEl total de los pedidos es: %.02f",cola.primer->pedido->precio);
		fflush(stdin);
		car={NULL,0};
		contador=contador+1;
	printf("\n¿Desea hacer otro pedido? (1 = Si), (0 = no): ");
	scanf("%i",&opcion3);
	
} while(opcion3==1);
for (i=0; i<=contador; i++){
	printf("\nSu orden ha sido confirmada, gracias.");
	Pedido* Despachar;
	Despachar = Consultar(&cola);
	Eliminar(&cola);
	printf("\nEl id del cliente es: %d", Despachar->id_cliente);
	printf("\n-------------------------------------------------");
}
    return 0;
}



