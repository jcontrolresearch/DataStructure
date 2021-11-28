//-------------------------Proyecto ordinario----------------------------------
//Integrantes:
//Angel Hernandez Gomez, Alan Jafet Ruiz Pacheco
//Octavio Hernandez Luna, Roberto Quintana Ramirez
//Alan Guzman Serret
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Estructura de la cola
typedef struct Nodo {
    int dato; //ID
    struct Nodo *ptrSig; //nodo siguiente
} Nodo;


//Prortotipo de funciones
void insertar();
void mostrar();
void ordenarB();
void ordenarS();
void intercambia(Nodo *a, Nodo *b);
void menu();
void liberarMemoria();

//Nodos de referencia - cola
Nodo *inicio = NULL; //inicio de la cola
Nodo *fin = NULL; //Fin de la cola



//Crear nuevo nodo para insertarlo por Cola
void insertar() {
    int dato;
    dato = rand()%(99999-10000+1)+10000; //Para generar los 5 digitos o numeros de ID
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo)); //Reservamos espacio en memoria dinamica
    nuevo->dato = dato;
    nuevo->ptrSig = NULL;
    if (inicio == NULL){ //En este caso la lista apenas se le ingreso un nuevo elemento
        inicio = nuevo; //primer elemento
        fin = nuevo;    //primer elemento
    } else {
        fin->ptrSig = nuevo; //Apuntar al siguiente 
        fin = nuevo;
        nuevo->ptrSig = NULL; //El puntero del nuevo nodo apunta a null
    }
}


//Mostrar elementos de la cola
void mostrar(){
    Nodo *i = NULL;
    i = inicio;
    if (i == NULL){ //cuando no hay elementos
        printf("\nLista vacia\n");
        return ;
    }
    else {
        printf("\nLa Cola es: \n");
        while (i != NULL) //imprimir los datos hasta llegar a NULL
        {
            printf("[%d] -> ", i->dato);
            i = i->ptrSig;
        }
    }
    printf("NULL"); //Fin de la cola, apunta a NULL (demostrativo)
}
	
//ordenamiento por seleccion
void ordenarS(){
	Nodo *p = inicio; //primer elemento de la cola
	while(p != NULL){
		Nodo *j = p->ptrSig; //siguiente elemento
		while(j != NULL){
			if(p->dato > j->dato){ //Busca el numero menor
				//lamar a la funcion intercambiar, que es elemental del ordenamiento
                intercambia(p,j); //Lo cambia por el valor en la p esima posicion
                mostrar(); //llamar a funcion mostrar
			}
			j = j->ptrSig;
		}
		p = p->ptrSig;
	}
	printf("\nDatos ordenados por metodo Seleccion\n");
	printf("\nCerrar y volver a ejecutar si necesita otro ordenamiento\n");
}

//intercambiar valores de una cola para ordenars()
void intercambia(Nodo *a, Nodo *b){
	//Parte para el ordenamiento de seleccion
    int aux = a->dato; //una variable temporal para hacer el cambio
    a->dato = b->dato;
    b->dato = aux;
}
	
//ordenamiento burbuja
void ordenarB(){
	int aux;//una variable temporal para hacer el cambio
	Nodo *p = inicio;
	while(p != NULL){
		Nodo *j = p->ptrSig;
		while(j != NULL){
			if(p->dato > j->dato){ //busqueda del minimo
				aux = j->dato; //intercambio de los datos
				j->dato = p->dato;
				p->dato = aux;
				mostrar(); //mostrar IDs ordenados
			}
			j = j->ptrSig;
		}
		p = p->ptrSig;
	}
	printf("\nDatos ordenados por metodo Burbuja\n");
	printf("\nCerrar y volver a ejecutar si necesita otro ordenamiento\n");
}

//Funcion Liberar la cola
//Funcion extra, para evitar conflictos de memoria
void liberarMemoria(){
    Nodo *liberar = inicio;
    if (liberar == NULL){ //Lista vacia
        printf("\nCola Vacia\n");
    } else {
        while (liberar != NULL)
        {
            inicio = liberar->ptrSig; //Mover la cabeza al siguiente nodo
            free(liberar);            //Liberamos el primer nodo que antes era la cabeza
            liberar = inicio;         // Liberar ahora es la cabeza
        }                             //Se hace el mismo proceso hasta liberar todos los nodos
        printf(" Cola liberada correctamente. \n");
    }
}

//Menu de opciones como funcion, fuera del main
void menu(){
    int mmenu = 0, cant = 0, mmenuID = 1;
	int opcion, i;
    while (!mmenu)//ciclo para mostrar menu, hasta que mmenu sea diferente de si mismo
    {
        printf("Menu De Opciones\n");
        printf("[1.] Generar ID de manera aleatoria.\n");
        printf("[2.] Mostrar ID Lista Completa.\n");
        printf("[3.] Ordenar Por burbuja.\n");
        printf("[4.] Ordenar Por Seleccion.\n");
        printf("[5.] Salir.\n");
        printf("Elige una Opcion: ");
        scanf("%d", &opcion); //seleccion del menu para pasar al case
        switch (opcion)
        {
        case 1:
        	if(mmenuID){ //introducir la cantidad de IDs a generar
        		printf("Introduce la cantidad de ID a generar: ");
	        	scanf("%d",&cant);
	        	i=0;
	        	mmenuID = 0;
	        	srand(time(NULL)); //numeros aleatorios
	        	for(i=0; i<cant; i++){ //Generar ID de 5 numeros de manera aleatoria
	        		insertar(); //funcion encolar
				}
	            printf("Elementos generados satisfactoriamente\n\n");
			}else{ //si ya existen IDs mostrar esto
				printf("\nYa se han generado de manera correcta los ID.\n\n");
			}
            break;
        case 2:
            mostrar();//llamar a la funcion para mostrar los ID
            printf("\n\n");
            break;
        case 3:
            ordenarB(); //llamar a ordenamiento burbuja
            printf("\n\n");
            break;
        case 4:
            ordenarS(); //llamar ordenamiento por seleccion
            printf("\n\n");
            break;
        case 5:
            mmenu = 1; //Finalizar el ciclo
            printf("\n Fin de programa. Hasta luego :) \n");
            break;
        default: //casos erroneos de seleccion
            printf("\n Opcion incorrecta, vuelve a intentarlo. \n\n");
            break;
        }
    }
}
//Main
int main(){
	menu();
	liberarMemoria();
	mostrar();
	return 0;
}
