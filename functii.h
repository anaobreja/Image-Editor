//Copyright 2022-2023 Obreja Ana-Maria Grupa 311CA
#ifndef FUNCTII
#define FUNCTII

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define VAL_MAX_PIXEL 255
#define N 3

typedef struct{
	double gray;
	double r;
	double g;
	double b;
} mat;

typedef struct {
	mat **mat;
	int linii, coloane;
	int tip, val_max;
	int x1, y1, x2, y2;
	//variabila care retine daca este sau nu incarcata in memorie imaginea
	int stare;
} img;

void functie_load(char *comanda, img *imagine);
void functie_select(char *comanda, img *imagine);
void functie_select_all(img *imagine);
void functie_crop(img *imagine);
void functie_rotate(char *comanda, img *imagine);
void functie_apply(char *comanda, img *imagine);
void functie_save(char *comanda, img imagine);
void functie_histogram(char *comanda, img imagine);
void functie_equalize(img imagine);

#endif
