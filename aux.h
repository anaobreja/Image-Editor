//Copyright 2022-2023 Obreja Ana-Maria Grupa 311CA
#ifndef AUX
#define AUX

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

typedef struct coordonate {
	int x1, y1, x2, y2;
} coord;

void alloc_matrix(img *imagine);
void free_matrix(img *imagine);
void swap(int *n, int *m);
void transformare_numar(int *nr, char *sir);
void functie_exit(img *imagine, int *ok);

#endif
