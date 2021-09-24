#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

typedef struct Libro 
{
	char titulo[50];
	char autor[50];
	char isbn;
}Libro;

typedef struct Nodo 
{
	Libro libro;
	struct Nodo* siguiente;
}Nodo;

typedef struct Nodo2 
{
	int num;
	struct Nodo* siguiente;
}Nodo2;

typedef struct Lista 
{
	Nodo* primero;
}Lista;

Nodo* CrearNodo(Libro* libro)
{
	Nodo* nodo = (Nodo *)malloc(sizeof (Nodo));
	strcpy(nodo->libro.titulo, libro->titulo);
	strcpy(nodo->libro.autor, libro->autor);
	strcpy(nodo->libro.isbn, libro->isbn);
    nodo->siguiente = NULL;
	return nodo;
}
void EliminarNodo(Nodo* nodo)
{
	free(nodo);
}
	
int ObtenerLongitud(Lista* lista)
{
	int longitud = 0;
	Nodo* puntero = lista->primero;
	while(puntero->siguiente != NULL)
	{
		puntero = puntero->siguiente;
		longitud++;
	}
	return longitud;
}
void InsertarPrincipio(Lista* lista, Libro* libro)
	{
		Nodo* nodo = CrearNodo(libro);
		nodo->siguiente = lista->primero;
		lista->primero = nodo;
	}
void InsertarFinal(Lista* lista, Libro* libro)
	{
		Nodo* nodo = CrearNodo(libro);
		if(lista->primero == NULL)
		{
			lista->primero = nodo;
		}
		else
		{
			Nodo* puntero = lista->primero;
			while(puntero->siguiente == NULL)
			{
				puntero = puntero->siguiente;
			}
			puntero->siguiente = nodo;
			nodo->siguiente = NULL;
		}
	}
void InsertarMedio(int n, Lista* lista, Libro* libro)
{
	Nodo* nodo = CrearNodo(libro);
	if(lista->primero == NULL)
	{
		lista->primero = nodo;
	} 
	else
	{
		int posicion = 0;
		Nodo* puntero = lista->primero;
		while(puntero->siguiente != NULL && posicion < n)
		{
			puntero = puntero->siguiente;
			posicion ++;
		}
		nodo->siguiente = puntero->siguiente;
		puntero->siguiente = nodo;
	}
}
Libro* ObternerLibro(int n, Lista* lista)
{
	if(lista->primero == NULL)
	{
		return NULL;
	} 
	else 
	{
		Nodo* puntero = lista->primero;
		int pos = 0;
		while( pos < n && puntero->siguiente )
		{
			puntero = puntero->siguiente;
			pos ++;
		}
		return &puntero->libro;	
	}
}
void EliminarPrincipio(Lista* lista)
{
	if(lista->primero != NULL)
	{
		Nodo* eliminar = lista->primero; 
		lista->primero = lista->primero->siguiente;
		EliminarNodo(eliminar);
	}
}
void EliminarFinal(Lista* lista)
{
	if(lista->primero != NULL)
	{
		if (lista->primero->siguiente != NULL)
		{
			Nodo* puntero = lista->primero;
			while (puntero->siguiente->siguiente != NULL)
			{
				puntero = puntero->siguiente;
			}
			Nodo* eliminar = puntero->siguiente;
			puntero->siguiente = NULL;
			EliminarNodo(eliminar);
		} 
		else
		{
			EliminarPrincipio(lista);
		}
	}
}
void EliminarMedio(int n, Lista* lista)
{
	int longitud = 0;
	if(lista->primero != NULL)
	{
		longitud = ObtenerLongitud(lista);
		if (n < longitud)
		{
			Nodo* puntero = lista->primero;
			Nodo* eliminar = lista->primero;
			int posicion = 0;
			while(posicion < (n-1))
			{
				puntero = puntero->siguiente;
				eliminar = puntero-> siguiente->siguiente;
				posicion = posicion ++;
			}
			puntero->siguiente = eliminar->siguiente;
			EliminarNodo(eliminar);	
		}
	}
}


int main()
{
	Libro book = {.titulo=' ', .autor=' ', .isbn=' '}; 
	Lista list={.primero=NULL};
	int opcion, opcion_colocar, opcion_posicion;
	
	do
	{
		printf( "\n----------------------Menu-------------------------\n");
		printf( "\n   a. Agregar un nuevo libro.");
		printf( "\n   b. Listar los libros.");
		printf( "\n   c. Eliminar libro.");
		printf( "\n   d. ¿Cuantos libros tengo?");
		printf( "\n   e. Preciona 5 para salir.");
		printf( "\n\n   Introduzca opcion (1-5):");
		
		scanf( "%d", &opcion );
		
		
		switch ( opcion )
		{
		case 'a': printf("\n Titulo del libro:");
		gets(book.titulo);
		fflush(stdin);
		printf("\n Autor del libro:");
		gets(book.autor);
		fflush(stdin);
		printf("\n Isbn del libro: ");
		gets(book.isbn);
		fflush(stdin);
		printf("\nDonde lo quieres colocar? \n1) inicio\n2) medio\n3) final\n\n>> ");
		scanf("%i",&opcion_colocar);
		if(opcion_colocar==1)
        {
		    InsertarPrincipio(&list,&book);
		}
        else if(opcion_colocar==2)
        {
			printf("\nÂ¿En donde lo quieres poner? >> ");
			scanf("%i",&opcion_posicion);
			InsertarMedio(opcion_posicion,&list,&book);
		}
        else if(opcion_colocar==3)
        {
			InsertarFinal(&list,&book);
		}
		Libro book={.titulo=' ',.autor=' ',.isbn=' '};
		break;
		
		case 'b': Listar(&book,&list);
		break;
		
		case 'c': EliminarFinal(&list);
		break;
		
		case 'd': printf("El numero de libros es:%d", ObtenerLongitud(&list));
		break;
		}
		
		
		
	} while ( opcion != 5 );
	
	return 0;
}
// listas enlzadas 
// autor: Rafael Santiago Avendaño
// Hola maestro le quiero pedir una disculpa por no terminarlo, aun asi lo voy a terminar
