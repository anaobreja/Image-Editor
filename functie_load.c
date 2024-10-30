//Copyright 2022-2023 Obreja Ana-Maria Grupa 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"
#include "aux.h"

//citirea dintr-un fisier binar, in functie de tip (alb-negru/color)
void citire_binar(FILE *in, img *imagine)
{
	int i, j;
	unsigned char element;
	for (i = 0; i < imagine->linii; i++)
		for (j = 0; j < imagine->coloane; j++) {
			if (imagine->tip == 5) {
				fread(&element, sizeof(unsigned char), 1, in);
				imagine->mat[i][j].gray = (double)element;
			} else {
				fread(&element, sizeof(unsigned char), 1, in);
				imagine->mat[i][j].r = (double)element;

				fread(&element, sizeof(unsigned char), 1, in);
				imagine->mat[i][j].g = (double)element;

				fread(&element, sizeof(unsigned char), 1, in);
				imagine->mat[i][j].b = (double)element;
			}
		}
}

//citirea dintr-un fisier text, in functie de tip (alb-negru/color)
void citire_text(FILE *in, img *imagine)
{
	int i, j;
	for (i = 0; i < imagine->linii; i++)
		for (j = 0; j < imagine->coloane; j++) {
			if (imagine->tip == 2) {
				fscanf(in, "%lf", &imagine->mat[i][j].gray);
			} else {
				fscanf(in, "%lf", &imagine->mat[i][j].r);
				fscanf(in, "%lf", &imagine->mat[i][j].g);
				fscanf(in, "%lf", &imagine->mat[i][j].b);
			}
		}
}

void functie_load(char *comanda, img *imagine)
{
	//verificare daca a mai existat o imagine incarcata anterior
	if (imagine->stare == 1) {
		free_matrix(imagine);
		imagine->stare = 0;
	}

	char *nume_fisier, *p;
	//aflarea numelui fisierului din car se face citire
	p = strtok(comanda, "\n ");
	p = strtok(NULL, "\n");
	nume_fisier = p;

	FILE *in = fopen(nume_fisier, "rb");
	if (!in) {
		printf("%s %s\n", "Failed to load", nume_fisier);
		return;
	}

	char *sir = (char *)malloc(MAX * sizeof(char));
	//schimbarea starii
	imagine->stare = 1;

	fgets(sir, MAX, in);
	//extragerea caracteristicilor imaginii
	if (strstr(sir, "P2"))
		imagine->tip = 2;
	else if (strstr(sir, "P3"))
		imagine->tip = 3;
	else if (strstr(sir, "P5"))
		imagine->tip = 5;
	else if (strstr(sir, "P6"))
		imagine->tip = 6;

	fgets(sir, MAX, in);

	char *linii, *coloane, *val_max;

	p = strtok(sir, "\n ");
	coloane = p;

	p = strtok(NULL, "\n ");
	linii = p;
	//transformarea unui sir de cifre in intreg
	transformare_numar(&imagine->coloane, coloane);
	transformare_numar(&imagine->linii, linii);

	fgets(sir, MAX, in);

	p = strtok(sir, "\n ");
	val_max = p;

	transformare_numar(&imagine->val_max, val_max);
	//alocam memorie matricei
	alloc_matrix(imagine);

	printf("%s %s\n", "Loaded", nume_fisier);
	//citire din fisier
	if (imagine->tip == 5 || imagine->tip == 6)
		citire_binar(in, imagine);
	else
		citire_text(in, imagine);
	//intreaga imagine este selectata
	functie_select_all(imagine);

	free(sir);
	fclose(in);
}
