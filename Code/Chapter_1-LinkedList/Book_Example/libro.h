//libro.h
//Clase para describir un libro
//Autor: Julio M
//

#ifdef libro_h
#define libro_h

#include<stdio.h>

typedef struct Libro {
	char titulo[50];
	char autor[50];
	char isbn[15];
} Libro;

#endif /*Libro.h*/
