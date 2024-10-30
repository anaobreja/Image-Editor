//Copyright 2022-2023 Obreja Ana-Maria Grupa 311CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"
#include "aux.h"

//rotunjirea numelor reale la cel mai apropiat intreg
int rotunjire(double a)
{
	int a_1;
	a_1 = (int)a;
	if (a - a_1 >= 0.5)
		return a_1 + 1;
	else
		return a_1;
}

//salvarea unui fisier text in functie de comanda data [ascii]
void scriere_text(FILE *out, img imagine)
{
	//scrierea caracteristicilor imaginii
	if (imagine.tip == 2 || imagine.tip == 5) {
		fprintf(out, "%c%d\n", 'P', 2);
		fprintf(out, "%d %d\n", imagine.coloane, imagine.linii);
		fprintf(out, "%d\n", imagine.val_max);

	//scrierea valorilor pixelilor in fisier, pentru imagine alb-negru
		int i, j, aux;
		for (i = 0; i < imagine.linii; i++) {
			for (j = 0; j < imagine.coloane ; j++) {
				aux = rotunjire(imagine.mat[i][j].gray);
				fprintf(out, "%d ", aux);
			}
			fprintf(out, "\n");
		}
	} else {
		fprintf(out, "%c%d\n", 'P', 3);
		fprintf(out, "%d %d\n", imagine.coloane, imagine.linii);
		fprintf(out, "%d\n", imagine.val_max);

		//scrierea valorilor pixelilor in fisier, pentru imagine color
		int i, j, aux;
		for (i = 0; i < imagine.linii; i++) {
			for (j = 0; j < imagine.coloane; j++) {
				aux = rotunjire(imagine.mat[i][j].r);
				fprintf(out, "%d ", aux);

				aux = rotunjire(imagine.mat[i][j].g);
				fprintf(out, "%d ", aux);

				aux = rotunjire(imagine.mat[i][j].b);
				fprintf(out, "%d ", aux);
			}
			fprintf(out, "\n");
		}
	}
}

//salvarea unui binar text in functie de comanda data
void scriere_binar(FILE *out, img imagine)
{
	//scrierea caracteristicilor imaginii
	if (imagine.tip == 2 || imagine.tip == 5) {
		fprintf(out, "%c%d\n", 'P', 5);
		fprintf(out, "%d %d\n", imagine.coloane, imagine.linii);
		fprintf(out, "%d\n", imagine.val_max);
		//scrierea valorilor pixelilor
		int i, j, aux;
		for (i = 0; i < imagine.linii; i++)
			for (j = 0; j < imagine.coloane; j++) {
				aux = rotunjire(imagine.mat[i][j].gray);
				fwrite(&aux, sizeof(unsigned char), 1, out);
			}
	} else {
		fprintf(out, "%c%d\n", 'P', 6);
		fprintf(out, "%d %d\n", imagine.coloane, imagine.linii);
		fprintf(out, "%d\n", imagine.val_max);

		int i, j, aux;
		for (i = 0; i < imagine.linii; i++) {
			for (j = 0; j < imagine.coloane; j++) {
				aux = rotunjire(imagine.mat[i][j].r);
				fwrite(&aux, sizeof(unsigned char), 1, out);

				aux = rotunjire(imagine.mat[i][j].g);
				fwrite(&aux, sizeof(unsigned char), 1, out);

				aux = rotunjire(imagine.mat[i][j].b);
				fwrite(&aux, sizeof(unsigned char), 1, out);
			}
		}
	}
}

void functie_save(char *comanda, img imagine)
{
	if (imagine.stare == 0) {
		printf("No image loaded\n");
		return;
	}

	char *p, *nume_fisier;
	int format_ascii = 0;
	//preluarea datelor fisierului (nume, text/binar) din comanda
	p = strtok(comanda, " ");
	p = strtok(NULL, "\n");

	if (strstr(p, "ascii"))
		format_ascii = 1;

	char *s;
	s = strtok(p, "\n ");

	nume_fisier = s;

	FILE *out = fopen(nume_fisier, "w");
	if (!out) {
		printf("%s %s\n", "Failed to save", nume_fisier);
		return;
	}

	if (format_ascii)
		scriere_text(out, imagine);
	else
		scriere_binar(out, imagine);

	fclose(out);
	printf("%s %s\n", "Saved", nume_fisier);
}
