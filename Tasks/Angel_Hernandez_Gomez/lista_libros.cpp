//Equipo:
//Angel Hernandez Gomez
//Octavio Hernandez Luna

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
	int longitud;
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
	return lista->longitud;

}

void Listar (Lista* lista){
if(lista->primero == 0)
{
printf("La lista esta vacia");
}else{
Nodo* puntero = lista->primero;
printf("\n Titulo: %s | Autor: %s | ISBN: %s \n", puntero->libro.titulo,puntero->libro.autor,puntero->libro.isbn);
				while(puntero->siguiente){
					puntero = puntero->siguiente;
					printf("\n Titulo: %s | Autor: %s | ISBN: %s \n", puntero->libro.titulo,puntero->libro.autor,puntero->libro.isbn);
				}
			}
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
				nodo->siguiente=lista->primero;
				lista->primero = nodo; 
				lista->longitud++;
			} else{
				// 2.- Recorrer la lista hasta el final
				// Creamos una variable auxiliar para recorer la lista desde el principio
				Nodo* puntero = lista->primero;
				while(puntero->siguiente){
					puntero = puntero->siguiente;
				}
				
				puntero->siguiente = nodo;
				nodo->siguiente = NULL;
				lista->longitud++;
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


void EliminarMedio(int n, Lista* lista){
int longitud = 0;
if(lista->primero){
	if(n == 0){
		EliminarPrincipio(lista);	
	}else{
		longitud = ObtenerLongitud(lista);
			if(n < longitud){
							Nodo* puntero = lista->primero;
							int posicion = 0;
							while(posicion <(n-1)){
								
								puntero = puntero->siguiente;
								posicion = posicion++;
							}
							Nodo* eliminar = puntero->siguiente;
							puntero->siguiente=eliminar->siguiente;
							EliminarNodo(eliminar);
							lista->longitud--;
						}
		}
	}
}
	
int main () {
	Libro book;
	Lista list;
	
	int op1;
	int b;
	int insert;
	int eliminate;
	printf ("Seleccione una opcion\n");
	printf("\n [1] Agregar un libro");
	printf("\n [2] Listar libros");
	printf("\n [3] Eliminar un libro");
	printf("\n [4] Obtener la longitud");
	printf("\n [5] Salir");
	printf("\n");
	scanf("%d",&op1);

	do{
		switch (op1)
		{
		case 1:
			fflush(stdin); 
			printf("\n Ingresa el titulo:  ");
			gets(book.titulo);
			fflush(stdin);
			printf("\n Ingresa el autor: ");
			gets(book.autor);
			fflush(stdin);
			printf("\n Ingresa el isbn: ");
			gets(book.isbn);
			fflush(stdin);
			
			printf("\nIngrese la posicion a insertar el libro:");
			printf("\n1 en el inicio");
			printf("\n2 en una posicion especifica");
			printf("\n3 en el final\n");
			scanf("%d",&insert);
			
			if (insert == 1){
				InsertarPrincipio(&list,&book);
				fflush(stdin);
			}
			if(insert == 2){
				printf("\nIngresa la posicion: ");
				scanf("%d",&b);
				InsertarMedio(b,&list,&book);
				fflush(stdin);
			}
			if (insert == 3){
				InsertarFinal(&list,&book);
				fflush(stdin);
			}
			
			break;
		case 2:
			Listar(&list);
			break;
		case 3:
			printf("\nIngrese la posicion a eliminar:");
			printf("\n1 en el inicio");
			printf("\n2 en una posicion especifica");
			printf("\n3 en el final");
			scanf("%d",&eliminate);
			if (eliminate == 1){
				EliminarPrincipio(&list);
				fflush(stdin);
			}
			if(eliminate == 2){
				printf("Ingrese la posicion a eliminar: ");
				scanf("%d",&eliminate);
				EliminarMedio(eliminate,&list);
				fflush(stdin);
				
			}
			if (eliminate == 3){
				EliminarFinal(&list);
				fflush(stdin);
			}
			break;
		case 4:
			printf("El numero de elementos son: %d", ObtenerLongitud(&list));
			break;
		}
	} while ( op1 != 5 );
	
	return 0;
}


