#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Estructuras necesarias
typedef struct City {
	int distance;
	int x;
	int y;
	char nombre[50];
	bool gas_station;
}City;

typedef struct Arbol {
	City ciudad;
	struct Arbol* Derecho;
	struct Arbol* Izquierdo;
}Arbol;

//Prototipos de funcion, ejemplos
void inorden(Arbol* arbol);
void preorden(Arbol* arbol);
void postorden(Arbol* arbol);
void remplazar(Arbol *arbol, Arbol *nuevo);

//Funciones necesarias


void DestruirNodo(Arbol* arbol){
	arbol->Izquierdo = NULL;
	arbol->Derecho = NULL;
	free(arbol);
}
	
//Funcion Insertar con crear nodo Arbol
void Insertar(Arbol** arbol, City* ciudad){
	Arbol* tmp = NULL;
	if(*arbol==NULL){
		*arbol = (Arbol *)malloc(sizeof (Arbol));
		//Pasar la informacion del url al nodo.url.urlID con string copy -> strcpy
		if(*arbol !=NULL){
			tmp = (Arbol *)malloc(sizeof (Arbol));
			strcpy(tmp->ciudad.nombre, ciudad->nombre);
			tmp->ciudad.x = ciudad->x;
			tmp->ciudad.y = ciudad->y;
			tmp->ciudad.distance = ciudad->distance;
			tmp->ciudad.gas_station = ciudad->gas_station;
			//nodo->padre = padre;
			tmp->Izquierdo = NULL;
			tmp->Derecho = NULL;
			*arbol = tmp;
		}
		//printf("\nNodo primero");
		//CrearNodo(&(*arbol), ciudad)
	}
	else{
		int valorRaiz = (int)&(*arbol)->ciudad.x;
		if(ciudad->x > valorRaiz){
			Insertar(&(*arbol)->Derecho, ciudad);
			//printf("\nEL NODO SE FUE A LA DERECHA");
			fflush(stdin);
		}
		else{
			Insertar(&(*arbol)->Izquierdo, ciudad);
			//printf("\nEL NODO SE FUE A LA IZQUIERDA");
			fflush(stdin);
		}
	}
	
}
	
/*void buscar(Arbol* arbol, City city){*/
/*	if(arbol==NULL){*/
/*		return;*/
/*	}else{*/
/*		if(arbol->ciudad.nombre == city.nombre){*/
/*			printf("La ciudad existe");*/
/*			printf("%s", arbol->ciudad.nombre);*/
/*		}else{*/
/*			if (city.x > arbol->ciudad.x){*/
/*				buscar(arbol->Izquierdo, city);*/
/*			}else{*/
/*				buscar(arbol->Derecho, city);*/
/*			}*/
/*		}*/
/*	}*/
/*}*/
//----------------Eliminacion funciones--------------------------------
//funcion para determinar el nodo mas izquierdo posible
	Arbol* mini(Arbol* arbol){
	if (arbol == NULL){
		return NULL;
	} 
	if(arbol->Izquierdo!=NULL){ //si hay hijo izquierdo
		return mini(arbol->Izquierdo); //buscar lo mas izquierdo posible
	}
	else{ //si no hay hijos izquierdos
		return arbol; //se retorna el mismo nodo
	}
}

void remplazar(Arbol *arbol, Arbol *nuevo){
	//checar si tiene un padre
	if(arbol->ciudad.x){
		//asignar un nuevo hijo al padre
		//Quitar el hijo y pasarle su nieto en su lugar
		if((arbol->ciudad.x == arbol->Izquierdo->ciudad.x)){
			arbol->Izquierdo = nuevo;
		} else{
			if((arbol->ciudad.x == arbol->Derecho->ciudad.x)){
				arbol->Derecho = nuevo;
			}
		}
	}
	if(nuevo){
		//asignar el nuevo padre
		nuevo->ciudad = arbol->ciudad;
	}
}
	
void EliminarNodo(Arbol* arbol){
	if(arbol->Izquierdo!=NULL && arbol->Derecho!=NULL){ //Tiene dos hijos
		//llamar el nodo a eliminar 
		Arbol *menor = mini(arbol->Derecho); //ir a la derecha y despues a lo mas izquierdo posible (con la funcion min)
		arbol->ciudad = menor->ciudad; //remplazar al elemento a eliminar
		EliminarNodo(menor); //eliminar el elemento
	}else{
		if(arbol->Izquierdo == NULL && arbol->Derecho == NULL){ //Si el arbol son hojas, sin hijos
			remplazar(arbol, NULL);
			DestruirNodo(arbol);
		}else{
			if(arbol->Izquierdo!= NULL && arbol->Derecho==NULL){ //Si tiene un hijo izquierdo
				remplazar(arbol, arbol->Izquierdo); //el padre apunta a su nuevo hijo y viceversa
				DestruirNodo(arbol);
			}else{
				if(arbol->Izquierdo == NULL && arbol->Derecho!=NULL){ //si tiene hijo derecho
					remplazar(arbol, arbol->Derecho);
					DestruirNodo(arbol);
				}
			}
		}
	}
}	

void eliminar(Arbol* arbol, City* ciudad){
	if(arbol==NULL){
		return;
	} else{
		if(ciudad->x < arbol->ciudad.x){ //si el valor es menor al otro
			eliminar(arbol->Izquierdo, ciudad); //buscar por el lado izquierdo
		} else{
			if(ciudad->x > arbol->ciudad.x){ //si es mayor al otro
				eliminar(arbol->Derecho, ciudad); //buscar a la derecha
			} else{
				EliminarNodo(arbol);
			}
		}
	}
}	
//-------------Recorridos-------------------------------------------
//Recorrido InOrden
void inorden(Arbol* arbol){
	if(arbol==NULL){
		return;
	}else{
		inorden(arbol->Izquierdo);
		printf("\n%s", arbol->ciudad.nombre);
		inorden(arbol->Derecho);
	}
}
//Recorrido PreOrden
void preorden(Arbol* arbol){
	if(arbol==NULL){
		return;
	}else{
		printf("\n%s", arbol->ciudad.nombre);
		preorden(arbol->Izquierdo);
		preorden(arbol->Derecho);
	}
}
//Recorrido en PostOrden
void postorden(Arbol* arbol){
	if(arbol==NULL){
		return;
	}else{
		preorden(arbol->Izquierdo);
		preorden(arbol->Derecho);
		printf("\n%s", arbol->ciudad.nombre);
	}
}	
	
int main(int argc, char *argv[]) {
	Arbol mapa = {0,0,0};
	Arbol * arbol = NULL;
	City Xoxocotlan={123, 345, -112, "xoxo", true};
	City Ciudad2={123, 345, -312, "santa lucia", true};
	City Ciudad3={21, 145, 113, "san bartolo", false};
	City Ciudad4={123, 385, -112, "oaxaca", true};
	City Ciudad5={12, 383, -512, "san martin", true};
	City Ciudad6={113, 315, -612, "san Jacinto", false};
	
	Insertar(&arbol, &Xoxocotlan);
	Insertar(&arbol, &Ciudad2);
	Insertar(&arbol, &Ciudad3);
	Insertar(&arbol, &Ciudad4);
	Insertar(&arbol, &Ciudad5);
	Insertar(&arbol, &Ciudad6);

	printf("Inorden\n");
	inorden(arbol);
	printf("\npreorden\n");
	preorden(arbol);
	printf("\npreorden\n");
	postorden(arbol);
	
	eliminar(arbol, &Xoxocotlan);
	printf("\nInorden\n");
	inorden(arbol);
	return 0;
}

