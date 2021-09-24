//lista.cpp
//


#include <stdlib.h>
#include <string.h>

#include <stdio.h>

//#include maxchar[50]
//#include minchar[20]
#define maxchar 50
#define minchar 50

#include <iostream>
#include <stdio.h>
using namespace std;
char maxchar[50];
char minchar[20];

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
void menu(void)
{
     cout<<"\n\n\t\t[ Registro de libros ]\n";
     cout<<"\t\t----------------------\n\n";
     cout<<"1. Registrar Libros"<<endl;
     cout<<"2. Listar los libros"<<endl;
     cout<<"3. Elminar libros"<<endl;
     cout<<"4. Desplegar libros"<<endl;
     cout<<"5. Salir"<<endl;
     cout<<"\n Ingrese opcion: ";
}

int main ()
{
         int des = 0,respa,resp;
         system("color0a");
         Lista lista[30];
         Libro libro[30];
         //Lista lista; //= {.primero = NULL};
        //Libro libro; //= {.titulo = "",.autor = "",.isbn = ""};
         int opcion;
         
         do{
                    menu();
                    cin>>opcion;
                    switch(opcion){
                                   case 1:
                                        do{
                                              cout<<"\n\n\t\t[ En que posicion desea imprimir: ]\n";
                                              cout<<"\t\t---------------------------------------\n";
                                              cout<<"1. Inicio de la lista"<<endl;
                                              cout<<"2. En medio de la lista"<<endl;
                                              cout<<"3. Fin de la Lista"<<endl;
                                              cout<<"\n Ingresa opcion: ";
                                              cin>>respa;
                                              }while((respa < 0)||(respa>3));
                                              if(respa == 1){
                                                       cout<<"\n\n\t\t[ REGISTRO ]\n";
                                                       cout<<"\t\t------------------";
                                                       cout<<"\n\t Datos del Libro";
                                                       cin.ignore();cout<<"\n\t Titulo: "; 
                                                       cin.getline(&libro->titulo,maxchar);
                                                       cin.ignore();cout<<"\n\t Autor: "; 
                                                       cin.getline(&libro->autor,maxchar);
                                                       cin.ignore();cout<<"\n\t ISBN: "; 
                                                       cin.getline(&libro->isbn,minchar);
                                                       InsertarPrincipio(lista,libro);
                                                       }else if(respa == 2){
                                                             int n = (ObtenerLongitud(lista))/2;
                                                              cout<<"\n\n\t\t[ RESGITRO ]\n";
                                                       cout<<"\t\t------------------";
                                                       cout<<"\n\t Datos del Libro";
                                                       cin.ignore();cout<<"\n\t Titulo: "; cin.getline(&libro->titulo,maxchar);
                                                       cin.ignore();cout<<"\n\t Autor: "; cin.getline(&libro->autor,maxchar);
                                                       cin.ignore();cout<<"\n\t ISBN: "; cin.getline(&libro->isbn,minchar);
                                                       InsertarMedio(n,lista,libro);
                                                       }else if(respa == 3){
                                                        cout<<"\n\n\t\t[ RESGITRO ]\n";
                                                       cout<<"\t\t------------------";
                                                       cout<<"\n\t Datos del Libro";
                                                       cin.ignore();cout<<"\n\t Titulo: "; cin.getline(&libro->titulo,maxchar);
                                                       cin.ignore();cout<<"\n\t Autor: "; cin.getline(&libro->autor,maxchar);
                                                       cin.ignore();cout<<"\n\t ISBN: "; cin.getline(&libro->isbn,minchar);
                                                       InsertarFinal(lista,libro);
                                                       }
                                                       break;
                                                       case 2:
                                                            //MostrarLibros(lista,libro);
                                                            break;
                                                       case 3:
//                                                            do{
//                                                                  cout<<"\n\n\t\t[ En que posicion desea elimniar: ]\n";
//                                                                  cout<<"\t\t---------------------------------------\n";
//                                                                  cout<<"1. Inicio De La Lista"<<endl;
//                                                                  cout<<"2. En medio de la lista"<<endl;
//                                                                  cout<<"3. Final de la Lista"<<endl;
//                                                                  cout<<"\n Ingrese opcion: ";
                                                                  //cin>>respb;
//                                                                  }while((respb < 0)||(respb > 3));
//                                                                  if(respb == 1){
//                                                                           EliminarPrincipio(&lista);
//                                                                           }else if (respb == 2){
//                                                                                 int n = (ObtenerLongitud(lista))/2;
//                                                                                 EliminarMedio(n,lista);
//                                                                                 }else if(respb == 3){
//                                                                                       EliminiarFinal(lista);
//                                                                                       }
                                                                                       break;
                                                       case 4: 
                                                            int ObtenerLongitud(Lista*lista);
                                                            cout<<"\n\t El numero de elementos dentro de la lista es: \n"<<ObtenerLongitud;
                                                            break;
                                                       case 5:
                                                            return 0;
                                                            
                                                       default: cout<<"\n Ingrese una opcion valida.\n";
                                                       break;
                                                       }
                                                       system("pause"); 
                                                       system("cls");
                                                       }while(opcion !=6);
                                                       system("pause");
                                                       return 0;
                                                       }
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
//	return 0;
//}
