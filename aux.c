//Copyright 2022-2023 Obreja Ana-Maria Grupa 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

//alocarea unei matrice si verificarea
void alloc_matrix(img *imagine)
{
	imagine->mat = (mat **)malloc(imagine->linii * sizeof(mat *));

	if (!imagine->mat) {
		free(imagine->mat);
		fprintf(stderr, "%s\n", "Malloc failed");
		return;
	}

	for (int i = 0; i < imagine->linii; i++) {
		imagine->mat[i] = (mat *)malloc(imagine->coloane * sizeof(mat));

		if (!imagine->mat[i]) {
			for (int j = 0; j < i; j++)
				free(imagine->mat[j]);
			free(imagine->mat);
			fprintf(stderr, "%s\n", "Malloc failed");
			return;
		}
	}
}

void free_matrix(img *imagine)
{
	int i;
	for (i = 0; i < imagine->linii; i++)
		free(imagine->mat[i]);
	free(imagine->mat);
}

void swap(int *n, int *m)
{
	int aux;
	aux = *n;
	*n = *m;
	*m = aux;
}

void transformare_numar(int *nr, char *sir)
{
	*nr = 0;

	for (int i = 0; i < (int)strlen(sir); i++)
		*nr = *nr * 10 + sir[i] - '0';
}

//functie de iesire din program
void functie_exit(img *imagine, int *ok)
{
	if (imagine->stare == 0) {
		printf("No image loaded\n");
		*ok = 0;
		return;
	}
	free_matrix(imagine);
	*ok = 0;
}
