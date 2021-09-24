#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estructuras necesarias
typedef struct Url {
	char dire[50];
}Url;

typedef struct NodoUrl {
	Url url;
	struct NodoUrl* siguiente;
}NodoUrl;

typedef struct Pila {
	//NodoUrl* primero;
	NodoUrl* ultimo;
	int longitud;
}Pila;


//Funciones
NodoUrl* CrearNodoUrl(Url* url){
	//Primer paso es definir la memoria dinamica que va a ocupar el nodo
	//El tamañno de memoria para el nodo esta definido por el NodoUrl
	NodoUrl* nodo = (NodoUrl *)malloc(sizeof (NodoUrl));
	//Apuntar a los datos de la estructura
	strcpy(nodo->url.dire, url->dire);
	nodo->siguiente = NULL;
	return nodo;
}
	
	void DestruirNodo(NodoUrl* nodo){
		// Hacer que los datos de la estructura pedido apunten a NULL para eliminar los posibles valores del pedido
		//nodo->url.dire = " ";
		//nodo->siguiente = NULL;
		// Se libera la memoria
		free(nodo);
	}


	Pila* CrearPila(){
		Pila* pila = (Pila *)malloc(sizeof (Pila));
		pila->ultimo = NULL;
		return pila;
	}
	
		void Apilar(Pila* pila, Url* url){
			NodoUrl* nodo = CrearNodoUrl(url);
			nodo->siguiente = pila->ultimo;
			pila->ultimo = nodo;
			pila->longitud=pila->longitud+1;
			
		}

			void Desapilar (Pila * pila){
				if (pila->ultimo != NULL){
					NodoUrl* eliminar = pila-> ultimo;
					pila->ultimo = pila->ultimo->siguiente;
					pila->longitud--;
				}
			}

int main(int argc, char *argv[]) {
	Pila pila = {NULL,0};
	int selec=0;
	int so=5;
	Url url1 = {"google"};
	Url url2 = {"youtube"};
	Url url3 = {"gmail"};
	
	printf(" \t=========Ingrese el Url========= \n");
	printf("\n");
do{	
	printf(" | [1]Google   |\n");
	printf(" | [2]Youtube  |\n");
	printf(" | [3]Gmail    |\n");
	printf("\n");
	scanf("%d", &selec);

if(pila.longitud < so){	
	if(selec==1){
		Apilar(&pila, &url1);
		fflush(stdin);
		printf("%s\n", pila.ultimo->url.dire);
	}
	if(selec==2){
		Apilar(&pila, &url2);
		fflush(stdin);
		printf("%s\n", pila.ultimo->url.dire);
	}
	if(selec==3){
		Apilar(&pila, &url3);
		fflush(stdin);
		printf("%s\n", pila.ultimo->url.dire);
	}
}
/*}else{*/
/*	printf("\nStock overflow\n");*/
/*}*/
}while(pila.longitud!=5);
printf("\nStack overflow\n");
printf("\n");
printf("%s\n", pila.ultimo->url.dire);
Desapilar(&pila);
printf("%s\n", pila.ultimo->url.dire);
Desapilar(&pila);
printf("%s\n", pila.ultimo->url.dire);
Desapilar(&pila);
printf("%s\n", pila.ultimo->url.dire);
Desapilar(&pila);
printf("%s\n", pila.ultimo->url.dire);
Desapilar(&pila);
	return 0;
}

