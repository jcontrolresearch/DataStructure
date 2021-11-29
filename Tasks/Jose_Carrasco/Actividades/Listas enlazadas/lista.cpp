#include <iostream>
#include "lista.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include "libro.h"

#include <stdio.h>
using namespace std;

Nodo* CrearNodo(Libro* libro){
      Nodo* nodo = (Nodo *) malloc(sizeof(Nodo));
      strncpy(nodo->libro.titulo, libro->titulo,50);
      strncpy(nodo->libro.autor, libro->autor,50);
      strncpy(nodo->libro.isbn, libro->isbn,15);
      return nodo;
      }

void DestruirNodo(Nodo* nodo){
     free(nodo);
     }

void InsertarPrincipio(Lista* lista,Libro* libro){
     Nodo* nodo = CrearNodo(libro);    
     nodo->siguiente = lista->cabeza;     
     lista->cabeza = nodo;
     lista->longitud++;
     printf("cree el nodo");
     }

void InsertarFinal(Lista* lista,Libro* libro){
     Nodo* nodo = CrearNodo(libro);


	// Que pasa si la lista esta vacia?
	// para saber si la lista esta vacia basta con revisar el primer elemento
	
	if(lista->cabeza == NULL){
		nodo->siguiente=lista->cabeza;
		lista->cabeza = nodo; 
		lista->longitud++;
		//lista->longitud++;
	} else{
		// 2.- Recorrer la lista hasta el final
		// Creamos una variable auxiliar para recorer la lista desde el principio
		Nodo* puntero = lista->cabeza;
		while(puntero->siguiente){
			puntero = puntero->siguiente;
		}
		//Paso 3.- Hacer que el ultimo objeto de la lista apunte al nodo nuevo
		puntero->siguiente = nodo;
		nodo->siguiente = NULL;
		lista->longitud++;
	}
     }

void InsertarDespues(int n,Lista* lista,Libro* libro){
     Nodo* nodo = CrearNodo(libro);
     if(lista->cabeza == NULL){
        lista->cabeza = nodo;
       }else{
             Nodo* puntero = lista->cabeza;
             int posicion = 0;
             while(posicion < n && puntero->siguiente){
                   puntero = puntero->siguiente;
                   posicion++;                    
                  }
                  nodo->siguiente = puntero->siguiente;
                  puntero->siguiente = nodo;
             }
             lista->longitud++;
     }

Libro* Obtener(int n, Lista* lista){
       if(lista->cabeza == NULL){
          return NULL;
       }else{
             Nodo* puntero = lista->cabeza;
             int posicion = 0;
             while(posicion < n && puntero->siguiente){
                   puntero = puntero->siguiente;
                   posicion++;                    
                  }
             if(posicion != n){
                 return NULL;
                }else{
                  return &puntero->libro;
                  }
             }
       }

int Contar(Lista* lista){
	cout<<"La longitud de la lista es \n"<<lista->longitud;
    return lista->longitud;
    }

int EstaVacia(Lista* lista){
    return lista->cabeza  == NULL;
    }

void EliminarPrincipio(Lista* lista){
     if(lista->cabeza){
        Nodo* eliminado = lista->cabeza;
        lista->cabeza = lista->cabeza->siguiente;
        DestruirNodo(eliminado);
        lista->longitud--;
        }
     }

void EliminarFinal(Lista* lista){
     if(lista->cabeza){
        if(lista->cabeza->siguiente){
         Nodo* puntero = lista->cabeza;
         while(puntero->siguiente->siguiente){
          puntero = puntero->siguiente;
          }
          Nodo* eliminado = puntero->siguiente;
          puntero->siguiente = NULL;
          DestruirNodo(eliminado);
          lista->longitud--;
         }else{
             Nodo* eliminado = lista->cabeza;
             lista->cabeza = NULL;
             DestruirNodo(eliminado);
             lista->longitud--;
         }
     }
}

void EliminarElemento(int n,Lista* lista){
     if(lista->cabeza){
         if(n == 0){
                 Nodo* eliminado = lista->cabeza;
                 lista->cabeza = lista->cabeza->siguiente;
                 DestruirNodo(eliminado);
                 lista->longitud--;
                }else if(n < lista->longitud){
                 Nodo* puntero = lista->cabeza;
                 int posicion = 0;
                 while(posicion < (n-1)){
                    puntero = puntero->siguiente;
                    posicion++;
                    }
                 Nodo* eliminado = puntero->siguiente;
                 puntero->siguiente = eliminado->siguiente;
                 DestruirNodo(eliminado);
                 lista->longitud--;
                 }  
        }
    }
    

void menu(void){

    cout<<"Menu de biblioteca:\n";
    cout<<"1)Agregar un nuevo libro"<<endl;
    cout<<"2)Listar libros"<<endl;
    cout<<"3)Eliminar un libro"<<endl;
    cout<<"4)Total de libros"<<endl;
    cout<<"5)Salir"<<endl;

    cout<<"\nIngrese la opcion:";
}

void MostrarLibros(Lista* lista){
    int i=1;
    Nodo* puntero = lista->cabeza;
    while(puntero->siguiente){
        
        cout<<"\nDatos de los libros";
        cout<<"\nTitulo:"<<puntero->libro.titulo<<endl;
        cout<<"\nAutor:"<<puntero->libro.autor<<endl;
        cout<<"\nISBN:"<<puntero->libro.isbn<<endl;	
				puntero = puntero->siguiente;
        i++;
		}
}

int main () {
	int respuesta;
	int respuesta1;
    Lista lista = {.cabeza=NULL,.longitud=0};
	Libro libro;
    int opcion;
	// [1] Agregar un nuevo libro: Preguntar al usuario el titulo, autor e isbn 
	// [2] Listar los libros: titulo | autor | isbn / si no hay elementos, desplegar: tu biblioteca esta vacia
	// [3] Eliminar libro: Preguntar donde lo queremos eliminar. 1) Usar un submenu / 2) Pedir n y verificar si n=0 eliminar el principio, si n = long(lista) elimanr el final sino eliminan en la posicion n
	// [4] Cuantos libros tengo? : Desplegar los libros
	do{
	    menu();
	    cin>>opcion;
        switch(opcion){
                case 1: 
                        do{
                        	cout<<"Indique la posicion a imprimir:\n";          
                            cout<<"1)Inicio de lista"<<endl;
                            cout<<"2)En medio de la lista"<<endl;
                            cout<<"3)Fin de lista"<<endl;
                            cout<<"\nIngrese la opcion que desea:";
                            cin>>respuesta;     	
						 }while((respuesta<0)||(respuesta>3));
                          if(respuesta == 1){
                            cout<<"Registro\n";
                            cout<<"\nDatos del libro:";
                            cin.ignore();cout<<"\nTitulo:"; cin.getline(libro.titulo,50);
                            cin.ignore();cout<<"Autor:"; cin.getline(libro.autor,50);
                            cin.ignore();cout<<"ISBN:"; cin.getline(libro.isbn,15);                            
                            InsertarPrincipio(&lista,&libro);
                            printf("Libro agregado"); 
						 } else if(respuesta==2){
							int n = (Contar(&lista))/2;
							cout<<"Registro\n";
                            cout<<"\nDatos del libro:";
                            cin.ignore();cout<<"\nTitulo:"; cin.getline(libro.titulo,50);
                            cin.ignore();cout<<"Autor:"; cin.getline(libro.autor,50);
                            cin.ignore();cout<<"ISBN:"; cin.getline(libro.isbn,15);   
                            system("cls");
                            InsertarDespues(n,&lista,&libro);
						 } else if(respuesta==3){
	                        cout<<"Registro\n";
                            cout<<"\nDatos del libro:";
                            cin.ignore();cout<<"\nTitulo:"; cin.getline(libro.titulo,50);
                            cin.ignore();cout<<"Autor:"; cin.getline(libro.autor,50);
                            cin.ignore();cout<<"ISBN:"; cin.getline(libro.isbn,15);                           
                            InsertarFinal(&lista,&libro);
						} 
                        break;
                case 2: 
                        if(&lista==NULL){
                            cout<"\nNo hay libros registrados\n";
                        }else {
                         MostrarLibros(&lista);
						}
                        break;
                case 3: 
                        do{
                        	cout<<"En que posicion desea eliminar:\n";
                            cout<<"1)Inicio de lista"<<endl;
                            cout<<"2)En medio de la lista"<<endl;
                            cout<<"3)Fin de lista"<<endl;
                            cout<<"\nIngrese la opcion que desee:";
                            cin>>respuesta1;     	
						}while((respuesta< 0)||(respuesta1>3));
						 if(respuesta1==1){
                            EliminarPrincipio(&lista);
						 } else if(respuesta1==2){
                            int n = (Contar(&lista))/2;
							EliminarElemento(n,&lista);
						 } else if(respuesta==3){
                            EliminarFinal(&lista);
						 }
                        break;
                case 4: 
                        Contar(&lista);
                        break;
                case 5: 
				return 0;
                default: cout<<"Ingrese una opcion valida\n"; break;
            }
            system("pause");  system("cls");		
	}while(opcion!=6);
	system("pause");
	return 0;
}






























