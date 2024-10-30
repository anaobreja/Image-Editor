//Copyright 2022-2023 Obreja Ana-Maria Grupa 311CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"
#include "aux.h"

void functie_histogram1(int bins, int *histogram, int stelute)
{
	//calcularea valorii maxime
	int val_max = 0;
	for (int i = 0; i < bins; i++)
		if (histogram[i] > val_max)
			val_max = histogram[i];

	//calcularea valorilor pentru fiecare interval,
	//in functie de stelute
	for (int i = 0; i < bins; i++) {
		float aux_1 = histogram[i] * stelute;
		aux_1 = (float)(aux_1 / val_max);
		histogram[i] = (int)aux_1;
	}

	//afisarea histogramei
	for (int i = 0; i < bins; i++) {
		printf("%d%c%c%c", histogram[i], 9, 124, 9);
		for (int j = 0; j < histogram[i]; j++)
			printf("*");
		printf("\n");
	}
}

void functie_histogram(char *comanda, img imagine)
{
	if (imagine.stare == 0) {
		printf("No image loaded\n");
		return;
	}
	//verificare imagine color
	int ok = 1;
	if (imagine.tip == 3 || imagine.tip == 6)
		ok = 0;
	char *p, *x, *y;
	int max_stelute, bins;

	//gasirea valorilor date in comanda
	p = strtok(comanda, " ");
	p = strtok(NULL, " ");
	//verificarea corectitudinii comenzi
	if (!p) {
		printf("Invalid command\n");
		return;
	}

	x = p;
	transformare_numar(&max_stelute, x);

	p = strtok(NULL, "\n ");
	y = p;
	if (!p) {
		printf("Invalid command\n");
		return;
	}
	y = p;
	if (strtok(NULL, "\n")) {
		printf("Invalid command\n");
		return;
	}
	if (!ok) {
		printf("Black and white image needed\n");
		return;
	}

	int *frecventa;
	int aux, max = 0, val_max;
	//alocam un vector de frecventa pentru calcularea aparitiilor fiecarui pixel
	//din intervalul [0, 255]
	frecventa = (int *)calloc(VAL_MAX_PIXEL + 1, sizeof(int));
	if (!frecventa) {
		free(frecventa);
		fprintf(stderr, "%s\n", "Malloc failed");
		return;
	}

	for (int i = 0; i < imagine.linii; i++)
		for (int j = 0; j < imagine.coloane; j++) {
			aux = (int)imagine.mat[i][j].gray;
			frecventa[aux]++;
			if (frecventa[aux] > max)
				max = frecventa[aux];
		}

	transformare_numar(&bins, y);
	int *histogram;
	val_max = (VAL_MAX_PIXEL + 1) / bins;
	histogram = (int *)malloc(bins * sizeof(int));
	int nr = 0, suma = 0, n = 0;
	//calculam initial totalul aparitiilor in functie de bins
	for (int i = 0; i <= VAL_MAX_PIXEL; i++) {
		suma += frecventa[i];
		nr++;
		if (nr == val_max) {
			histogram[n] = suma;
			nr = 0;
			suma = 0;
			n++;
		}
	}
	functie_histogram1(bins, histogram, max_stelute);
	free(histogram);
	free(frecventa);
}

void functie_equalize(img imagine)
{
	if (imagine.stare == 0) {
		printf("No image loaded\n");
		return;
	} else if (imagine.tip == 3 || imagine.tip == 6) {
		printf("Black and white image needed\n");
		return;
	}

	int *frecventa;
	int max = 0;
	int aux;
	//analog histogramei, folosim vector de frecventa
	frecventa = (int *)calloc(VAL_MAX_PIXEL + 1, sizeof(int));

	for (int i = 0; i < imagine.linii; i++)
		for (int j = 0; j < imagine.coloane; j++) {
			aux = imagine.mat[i][j].gray;
			frecventa[aux]++;
			if (frecventa[aux] > max)
				max = frecventa[aux];
		}

	int area = imagine.linii * imagine.coloane;

	//calcularea noilor valori pentru fiecare pixel
	for (int i = 0; i < imagine.linii; i++)
		for (int j = 0; j < imagine.coloane; j++) {
			aux = imagine.mat[i][j].gray;
			int suma = 0;
			for (int k = 0; k <= aux; k++)
				suma += frecventa[k];
			aux = VAL_MAX_PIXEL * suma / area;
			imagine.mat[i][j].gray = aux;
		}
	free(frecventa);
	printf("Equalize done\n");
}
