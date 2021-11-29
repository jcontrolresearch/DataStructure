#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
//integrantes del equipo
//Uziel Esaú López Ruíz
//José Alberto Carrasco Francisco
//Armando Ayala Lujan
//Florencia Bacilio López
//Isamayi Meyli Velasco Rodriguez
typedef struct Link{
	char url[50];
}Link;

typedef struct NodoLink {
	Link link;
	struct NodoLink* siguiente;
}NodoLink;

typedef struct PilaLink {
	NodoLink* lista_link;
	int longitud;
}PilaLink;

NodoLink* CrearNodo(Link* link);
void DestruirLink(NodoLink* nodo);

NodoLink* CrearNodo(Link* link){
	NodoLink* nodo = (NodoLink *)malloc(sizeof (NodoLink));
	strncpy(nodo->link.url, link->url,50);
	nodo->siguiente = NULL;
}

void DestruirLink(NodoLink* nodo){
	free(nodo);
}

void InsertarPrincipio(PilaLink* pilalink,Link* link){
     NodoLink* nodo = CrearNodo(link);    
     nodo->siguiente = pilalink->lista_link;     
     pilalink->lista_link = nodo;
     pilalink->longitud++;
     printf("cree el nodo");
     }

void InsertarFinal(PilaLink* pilalink,Link* link){
     NodoLink* nodo = CrearNodo(link);
	if(pilalink->lista_link == NULL){
		nodo->siguiente=pilalink->lista_link;
		pilalink->lista_link = nodo; 
		pilalink->longitud++;
	} else{
		NodoLink* puntero = pilalink->lista_link;
		while(puntero->siguiente){
			puntero = puntero->siguiente;
		}
		puntero->siguiente = nodo;
		nodo->siguiente = NULL;
		pilalink->longitud++;
	}
    }

void EliminarPrincipio(PilaLink* pilalink){
     if(pilalink->lista_link){
        NodoLink* eliminado = pilalink->lista_link;
        pilalink->lista_link = pilalink->lista_link->siguiente;
        DestruirLink(eliminado);
        pilalink->longitud--;
        }
     }

void EliminarFinal(PilaLink* pilalink){
     if(pilalink->lista_link){
        if(pilalink->lista_link->siguiente){
         NodoLink* puntero = pilalink->lista_link;
         while(puntero->siguiente->siguiente){
          puntero = puntero->siguiente;
          }
          NodoLink* eliminado = puntero->siguiente;
          puntero->siguiente = NULL;
          DestruirLink(eliminado);
          pilalink->longitud--;
         }else{
             EliminarPrincipio(pilalink);
         }
     }
}

void pushup(PilaLink* pilalink){
	//while(pilalink->lista_link!=NULL){
		if(pilalink->lista_link){
        if(pilalink->lista_link->siguiente){
         NodoLink* puntero = pilalink->lista_link;
         while(puntero->siguiente->siguiente){
          puntero = puntero->siguiente;
          }
          NodoLink* eliminado = puntero->siguiente;
          printf("Link: %s\n",puntero->siguiente);
          puntero->siguiente = NULL;
          DestruirLink(eliminado);
          pilalink->longitud--;
         }else{
         	 printf("Link: %s\n",pilalink->lista_link);
             EliminarPrincipio(pilalink);
			pilalink->longitud--;
         }
         if(pilalink->lista_link==NULL){
         	pilalink->longitud=0;
		 }
     //}
	}
}

void menu(void){

    printf("\n\t\t[    Registro de pila    ]\n");
    printf("\t\t-----------------------------\n\n");
    printf(" 1. Mostrar links                                       \n");
    printf(" 2. Agregar links                          \n");
    printf(" 3. Longitus de pila                             \n");
    printf(" 4. Procesar pila                 \n");
    printf(" 5. Salir                                       \n");
    printf("\n Ingrese opcion : ");
}
void menulink(void){
	printf("\n\t\t[    Lista de opciones de link    ]\n");
    printf("\t\t-----------------------------\n\n");
    printf(" 1.  Link de Google                                       \n");
    printf(" 2.  Link de Facebook                          \n");
    printf(" 3.  Link de Youtube                             \n");
    printf(" 4.  Link de Whatsapp                 \n");
    printf(" 5.  Link de Instagram                                       \n");
    printf(" 6.  Link de Cuevana                                       \n");
    printf(" 7.  Link de Drive                          \n");
    printf(" 8.  Link de Twitter                             \n");
    printf(" 9.  Link de Pdf                 \n");
    printf(" 10. Link de Gmail                                       \n");
    printf(" 11. Link de Spotify                                       \n");
    printf(" 12. Link de Elibro                          \n");
    printf(" 13. Link de Netflix                             \n");
    printf(" 14. Link de Disneyplus                 \n");
    printf(" 15. Link de Maps                                       \n");
    printf("\n Ingrese opcion : ");
}

int main(){
	int opcion,deci;
	char resp;
	Link google = {.url = "Https://www.google.com.mx"};
	Link facebook = {.url = "Https://www.facebook.com.mx"};
	Link youtube = {.url = "https://www.youtube.com/"};
	Link whatsapp = {.url = "https://web.whatsapp.com/"};
	Link instagram = {.url = "https://www.instagram.com/?hl=es"};
	Link cuevana = {.url = "https://cuevana3.io/"};
	Link drive = {.url = "https://drive.google.com/drive/"};
	Link twitter = {.url = "https://twitter.com/?lang=es"};
	Link pdf = {.url = "https://www.ilovepdf.com/es"};
	Link gmail = {.url = "https://mail.google.com/mail/"};
	Link spotify = {.url = "https://www.spotify.com/mx/"};
	Link elibro = {.url = "https://elibro.net/es/lc/ulsaoaxaca"};
	Link netflix = {.url = "https://www.netflix.com/mx/"};
	Link disneyplus = {.url = "https://www.disneyplus.com/es-419/login"};
	Link maps = {.url = "https://www.google.com.mx/maps/preview"};
	Link link = {.url = " "};
	PilaLink pilalink = {.lista_link = NULL,.longitud = 0};
	do{
		menu();
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
				menulink();
				break;
			case 2:
				menulink();
				
				do{
					if(pilalink.longitud<15){
				 printf("Elija su opcion por favor: \n");
				 scanf("%d",&deci);
				 fflush(stdin);
				 if(deci == 1){
				  printf("Link: %s\n",google);
				  link = google;
				  InsertarFinal(&pilalink,&link);	
				 }else if(deci == 2){
				  printf("Link: %s\n",facebook);
				  link = facebook;
				  InsertarFinal(&pilalink,&link);		
				 }else if(deci == 3){
				  printf("Link: %s\n",youtube);
				  link = youtube;
				  InsertarFinal(&pilalink,&link);
				 }else if(deci == 4){
				  printf("Link: %s\n",whatsapp);
				  link = whatsapp;
				  InsertarFinal(&pilalink,&link);
				 }else if(deci == 5){
				  printf("Link: %s\n",instagram);
				  link = instagram;
				  InsertarFinal(&pilalink,&link);	
				 }else if(deci == 6){
				  printf("Link: %s\n",cuevana);
				  link = cuevana;
				  InsertarFinal(&pilalink,&link);	
				 }else if(deci == 7){
				  printf("Link: %s\n",drive);
				  link = drive;
				  InsertarFinal(&pilalink,&link);	
				 }else if(deci == 8){
				  printf("Link: %s\n",twitter);
				  link = twitter;
				  InsertarFinal(&pilalink,&link);	
				 }else if(deci == 9){
				  printf("Link: %s\n",pdf);
				  link = pdf;
				  InsertarFinal(&pilalink,&link);	
				 }else if(deci == 10){
				  printf("Link: %s\n",gmail);
				  link = gmail;
				  InsertarFinal(&pilalink,&link);	
				 }else if(deci == 11){
				  printf("Link: %s\n",spotify);
				  link = spotify;
				  InsertarFinal(&pilalink,&link);	
				 }else if(deci == 12){
				  printf("Link: %s\n",elibro);
				  link = elibro;
				  InsertarFinal(&pilalink,&link);	
				 }else if(deci == 13){
				  printf("Link: %s\n",netflix);
				  link = netflix;
				  InsertarFinal(&pilalink,&link);	
				 }else if(deci == 14){
				  printf("Link: %s\n",disneyplus);
				  link = disneyplus;
				  InsertarFinal(&pilalink,&link);	
				 }else if(deci == 15){
				  printf("Link: %s\n",maps);
				  link = maps;
				  InsertarFinal(&pilalink,&link);	
				 }
				 } else{
					printf("Stackoverflow\n");
					break;
					break;
				}
				   printf("Desea agregar otro link?: [S/N]\n");
				    scanf("%c",&resp);
				    fflush(stdin);
					printf("La longitu es %d\n",pilalink.longitud);
				 }while((resp == 'S'||resp == 's')&&(resp != 'N'||resp != 'n')); 
				
				break;
			case 3:
				printf("La longitud de la pila es: %d\n",pilalink.longitud);
				break;
			case 4:
				pushup(&pilalink);
				break;
			case 5:
				return 0;
                default: printf("\nINGRESE UNA OPCION VALIDA...\n"); 
		        break;
		}
		system("pause");  system("cls");
	}while(opcion!=5);
	return 0;
}
