#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ciudad{
	char nombre[20];
	int x;
	int y;
	int gas_station;
}Ciudad;

typedef struct nodo{
	Ciudad ciudad;
	struct nodo* izquierdo;
	struct nodo* derecho;
	struct nodo* padre;
} Nodo;

typedef Nodo Arbol;

Nodo*  CrearNodo(Ciudad ciudad,Nodo* padre){
	Nodo* nuevoNodo = (Nodo *) malloc(sizeof(Nodo));
	nuevoNodo->izquierdo = nuevoNodo->derecho = NULL;
	strncpy(nuevoNodo->ciudad.nombre, ciudad.nombre,20);
	nuevoNodo->ciudad.x=ciudad.x;
	nuevoNodo->ciudad.y=ciudad.y;
	nuevoNodo->ciudad.gas_station=ciudad.gas_station;
	nuevoNodo->izquierdo = nuevoNodo->derecho = NULL;
	nuevoNodo->padre = padre;
	return nuevoNodo;
}

void DestruirNodo(Nodo* nodo){
	nodo->izquierdo = nodo->derecho = NULL;
	free(nodo);
}

static void InsertarConPadre(Nodo** arbol,Nodo* padre,Ciudad ciudad){
	if(*arbol == NULL){
	   *arbol = CrearNodo(ciudad,padre);
	} else{
		int valorRaiz = (*arbol)->ciudad.x;
		if(ciudad.x < valorRaiz){
			InsertarConPadre(&(*arbol)->izquierdo,*arbol,ciudad);
		} else{
			InsertarConPadre(&(*arbol)->derecho,*arbol,ciudad);
		}
	}
}

void Insertar(Nodo** arbol, Ciudad ciudad){
	InsertarConPadre(arbol,NULL,ciudad);
}

void Existe(Nodo* arbol, Ciudad ciudad){
	if(arbol == NULL){
		printf("No existe en el arbol\n");
	} else if(ciudad.x < arbol->ciudad.x){
		Existe(arbol->izquierdo,ciudad);
		printf("si existe %s en el arbol izquierdo\n",ciudad.nombre);
		printf("%d,%d",ciudad.x,arbol->ciudad.x);
	} else{
		Existe(arbol->derecho,ciudad);
		printf("si existe %s en el arbol derecho\n",ciudad.nombre);
		printf("%d,%d",ciudad.x,arbol->ciudad.x);
	}
}

Nodo* Obtener(Nodo* arbol,Ciudad ciudad){
	if(arbol == NULL){
		return NULL;
	} else if(arbol->ciudad.x == ciudad.x){
		return arbol;
	} else if(ciudad.x < arbol->ciudad.x){
		return Obtener(arbol->izquierdo,ciudad);
	} else {
		return Obtener(arbol->derecho,ciudad);
	}
}

//void DeterminarExistencia(Nodo* arbol,Ciudad ciudad){
//	if(Existe(arbol,ciudad)){
//		printf("La ciudad %s existe en el arbol.\n",ciudad.nombre);
//	} else{
//		printf("La ciudad %s no existe en el arbol.\n",ciudad.nombre);
//	}
//}

static void Reemplazar(Nodo* arbol, Nodo* nuevoNodo,Ciudad ciudad){
	if(arbol->padre){
		//Procedemos a colocar en el padre de arbol el nuevoNodo como nuevo hijo.
		if(arbol->ciudad.nombre == arbol->padre->izquierdo->ciudad.nombre){
			arbol->padre->izquierdo = nuevoNodo;
		} else if(arbol->ciudad.nombre == arbol->padre->derecho->ciudad.nombre){
			arbol->padre->derecho = nuevoNodo;
		}
		
	}
	if(nuevoNodo){
		//Procedemos a poner como padre de nuevoNodo a arbol->padre.
		nuevoNodo->padre = arbol->padre;
	}
}

static Nodo* Minimo(Nodo*arbol){
	if(arbol  == NULL)
	   return NULL;
	if(arbol->izquierdo){
		return Minimo(arbol->izquierdo);
	} else {
		return arbol;
	}
}

static void EliminarNodo(Nodo* nodoEliminar,Ciudad ciudad){
	if(nodoEliminar->izquierdo && nodoEliminar->derecho){
		//Tratar de eliminar con 2 hijos.
		Nodo* minimo = Minimo(nodoEliminar->derecho);
		nodoEliminar->ciudad = minimo->ciudad;
		EliminarNodo(minimo,ciudad);
	} else if(nodoEliminar->izquierdo){
		//Tratar de eliminar con 1 hijo.
		Reemplazar(nodoEliminar,nodoEliminar->izquierdo,ciudad);
		DestruirNodo(nodoEliminar);
	} else if(nodoEliminar->derecho){
		//Tratar de eliminar con 1 hijo.
		Reemplazar(nodoEliminar,nodoEliminar->derecho,ciudad);
		DestruirNodo(nodoEliminar);
	} else{
		//Tratar de eliminar con 0 hijo.
		Reemplazar(nodoEliminar,NULL,ciudad);
		DestruirNodo(nodoEliminar);
	}
}

void Eliminar(Nodo* arbol, Ciudad ciudad){
	if (arbol == NULL)
		return;
	else if(ciudad.x < arbol->ciudad.x)
	    Eliminar(arbol->izquierdo,ciudad);
	else if(ciudad.x > arbol->ciudad.x)
	    Eliminar(arbol->derecho,ciudad);
    else
        EliminarNodo(arbol,ciudad);
	
}

void Preorden(Nodo* arbol){
     if(arbol == NULL){
     	printf("-");
	 } else{
	 	printf("(%s",arbol->ciudad.nombre);
	 	Preorden(arbol->izquierdo);
	 	Preorden(arbol->derecho);
	 	printf(")");
	 }
}

void Inorden(Nodo* arbol){
	if(arbol == NULL){
		printf("-");
	} else{
		printf("(");
		Inorden(arbol->izquierdo);
		printf("%s", arbol->ciudad.nombre);
		Inorden(arbol->derecho);
		printf(")");
	}
}

void Postorden(Nodo* arbol){
	if(arbol == NULL){
		printf("-");
	} else {
		printf("(");
		Postorden(arbol->izquierdo);
		Postorden(arbol->derecho);
		printf("%s)",arbol->ciudad.nombre);
	}
}

int main(){
	Nodo* arbol = NULL;
	Ciudad puerto_l = {.nombre = "puerto",.x = 52,.y = 67,.gas_station = 45};
	Ciudad oaxaca = {.nombre = "oaxaca",.x = 26,.y = 29,.gas_station = 22};
	Ciudad puerto_c = {.nombre = "puerto",.x = 2,.y = 3,.gas_station = 1};
	Ciudad Zimatlan_de_Alvarez = {.nombre = "Zimatlan de Alvarez",.x = 12,.y = 10,.gas_station = 5};
	Ciudad Sola_de_Vega = {.nombre = "Sola de Vega",.x = 18,.y = 16,.gas_station = 12};
	Ciudad San_Pedro_Mixtepec = {.nombre = "San Pedro Mixtepec",.x = 22,.y = 24,.gas_station = 18};
	Ciudad Santiago_Matatlan = {.nombre = "Santiago Matatlan",.x = 38,.y = 40,.gas_station = 26};
	Ciudad Tehuantepec = {.nombre = "Tehuantepec",.x = 43,.y = 52,.gas_station = 35};
	Ciudad San_Pedro_Pochutla = {.nombre = "San Pedro Pochutla",.x = 48,.y = 59,.gas_station = 40};
	
	Insertar(&arbol,oaxaca);                       Inorden(arbol); printf("\n");
	Insertar(&arbol,puerto_l);                     Inorden(arbol); printf("\n");
	Insertar(&arbol,puerto_c);                     Inorden(arbol); printf("\n");
	Insertar(&arbol,Zimatlan_de_Alvarez);          Inorden(arbol); printf("\n");
	Insertar(&arbol,Sola_de_Vega);                 Inorden(arbol); printf("\n");
	Insertar(&arbol,San_Pedro_Mixtepec);           Inorden(arbol); printf("\n");
	Insertar(&arbol,Santiago_Matatlan);            Inorden(arbol); printf("\n");
	Insertar(&arbol,Tehuantepec);                  Inorden(arbol); printf("\n");
	Insertar(&arbol,San_Pedro_Pochutla);           Inorden(arbol); printf("\n\n\n");
	Eliminar(arbol,Sola_de_Vega);                  Inorden(arbol); printf("\n");
	Eliminar(arbol,Santiago_Matatlan);             Inorden(arbol); printf("\n");
	Eliminar(arbol,oaxaca);                        Inorden(arbol); printf("\n");
	return 0;
}
