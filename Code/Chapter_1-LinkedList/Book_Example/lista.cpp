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

int ObtenerLongitud(Lista* lista){
	//Variable para contar la longitud de la lista
	int longitud = 0;
	// Como recorremos la lista y contamos cuantos elementos tiene
	Nodo* puntero = lista->primero;
	while(puntero->siguiente != NULL){
		puntero = puntero->siguiente;
		longitud++;
	}

	return longitud;

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

// Funciones de eliminacion

// *************************************

// Funciones de eliminacion


//Como eliminamos al princio?

void EliminarPrincipio(Lista* lista){
	if(lista->primero != NULL){
		//1.- Crear un nodo temporal
		//1.5.- Asignar el nodo.primero a una variable temporal
		Nodo* eliminar = lista->primero; 
		//2.- Cambiar el nodo.primero por el nodo.primero.siguiente
		lista->primero = lista->primero->siguiente;
		//3.- Eliminar / liberar la memoria del nodo.primero o nodo temporal
		EliminarNodo(eliminar);
	}
}

// Como eliminamos al final?

void EliminarFinal(Lista* lista){

	// 1.- Crear un nodo temporal para guardar el ultimo actual
	// 2.- Recorrer la lista hasta el penultimo
	// 3.- Liberar memoria o quitar el ultimo nodo
	if(lista->primero != NULL){
		if (lista->primero->siguiente != NULL){
			Nodo* puntero = lista->primero;
			while (puntero->siguiente->siguiente != NULL){
				puntero = puntero->siguiente;
			}

			Nodo* eliminar = puntero->siguiente;
			// De esta forma cambiamos el apuntador siguiente del penultimo a NULL y lo definimos como ultimo
			puntero->siguiente = NULL;
			// Se libera espacion en memoria
			EliminarNodo(eliminar);
		} else{
			EliminarPrincipio(lista);
		}
	}
}


// Eliminar un nodo que este en algun lugar especifico de la lista


void EliminarMedio(int n, Lista* lista){
	//Pasos para eliminar de enmedio de la lista
	//1.-Crear un nodo apuntador
	//2.-Crear una variable que cuente en donde estamos en la lista
	//3.- Recorrer la lista hasta n-1
	//4.- Cambiar o asignar el apuntador de nodo n-1 a n+1
	//5.- Eliminar el nodo n

	//Consideraciones
	// C1.- Que pasa si la lista esta vacia
	int longitud = 0;
	if(lista->primero != NULL){
		// C2.- Que pasa si la lista tiene una longitud menor al elemento que se pide eliminar
		longitud = ObtenerLongitud(lista);
		if (n < longitud){
			Nodo* puntero = lista->primero;
			Nodo* eliminar = lista->primero;
			int posicion = 0;
			while(posicion < (n-1)){
				puntero = puntero->siguiente;
				eliminar = puntero-> siguiente->siguiente;
				posicion = posicion ++;
			}
			puntero->siguiente = eliminar->siguiente;
			EliminarNodo(eliminar);	
		}
	}
}

int main () {

	//incializar la lista vacia
	Libro book; //= {.titulo= "", .autor="", .isbn=""};
	Lista list; //= {.primero = 0, .longitud = 0};
	//Libro book;
	//Lista list;

	int seleccion;
		do
		    {
		    	printf("\n|----------------------------------------|");
				printf("\n|          ° LISTAS ENLAZADAS °          |");
				printf("\n|----------------------------------------|");
				printf("\n| 1. Insertar      | 4. Obtener Longitud |");
				printf("\n| 2. Listar        | 5. Salir            |");
				printf("\n| 3. Eliminar      |                     |");
				printf("\n|------------------|---------------------|");
				printf("\n\n Escoja una Opcion: ");
		        scanf( "%d", &seleccion);
		        switch ( seleccion )
		        {
		            case 1:
		            
		            	fflush(stdin); 
		          		printf("\n Ingresa el titulo del libro :  ");
		                gets(book.titulo);
		                fflush(stdin);
			            printf("\n Ingresa el autor del libro : ");
		                gets(book.autor);
		                fflush(stdin);
			            printf("\n Ingresa el isbn del libro : ");
		                gets(book.isbn);
		                fflush(stdin);
		                
		                printf("%s el libro",book.autor);
		                
		           	    InsertarPrincipio(&book,&list);
		
		               
		           		break;
		           	case 2:
		           		Listar(&book,&list);
		           	break;
		           	case 3:
		           		EliminarFinal(&list);
		           	break;
		           	case 4:
		    	
		    			printf("La longitud es:%d", ObtenerLongitud(&list));
		    			break;
		         }
		    } while ( seleccion != 5 );



	
	// Lineamientos del programa
	// Hacer un menu de biblioteca: Las opciones van a ser las siguientes
	// [1] Agregar un nuevo libro: Preguntar al usuario el titulo, autor e isbn 
	// [2] Listar los libros: titulo | autor | isbn / si no hay elementos, desplegar: tu biblioteca esta vacia
	// [3] Eliminar libro: Preguntar donde lo queremos eliminar. 1) Usar un submenu / 2) Pedir n y verificar si n=0 eliminar el principio, si n = long(lista) elimanr el final sino eliminan en la posicion n
	// [4] Cuantos libros tengo? : Desplegar los libros
	
	//Criterio:
	// agregar 10 libros (sugerencia: libros reales)
	// En un one_pager mostrar las siguientes puntos:
	// 1.- Agregar un libro
	// 2.- Listar los libros
	// ... Listar hasta tener 10 libros. Se pude agregar al final, al princio o en medio
	
	// Eliminar los libros...  igual que agregar libros, utilizar todos las funciones
	
	// Listar cuantos libros tengo al final
	
	
	//EL one_pager tiene que contener:
	//Titulo. Listas enlazada,
	//Ejecucion 1.
	// Resultados
	//Ejecucion 2.
	// Resultados
	//etc
	
	// TODO: Enviar una tabla de evaluacion de las funciones de listas ligadas 
	// Se entregara en binas
	// 
	return 0;
}


