//Copyright 2022-2023 Obreja Ana-Maria Grupa 311CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"
#include "aux.h"

void rotate(img *imagine)
{
	img imagine_noua;
	int x1, x2, y1, y2, ok = 0;

	x1 = imagine->x1;
	x2 = imagine->x2;
	y1 = imagine->y1;
	y2 = imagine->y2;

	//calculam dimensiunile cadranului ce urmeaza sa fie rotit
	imagine_noua.linii = x2 - x1;
	imagine_noua.coloane = y2 - y1;

	alloc_matrix(&imagine_noua);

	//verificare daca selectia este facuta pe intreaga imagine
	if (y2 - y1 == imagine->linii && x2 - x1 == imagine->coloane)
		ok = 1;

	if ((x2 - x1) != (y2 - y1) && ok == 0) {
		printf("The selection must be square\n");
		return;
	}

	int i, j;
	//ne folosim de o matrice auxiliara
	img imagine_aux;
	imagine_aux.linii = y2 - y1;
	imagine_aux.coloane = x2 - x1;

	alloc_matrix(&imagine_aux);
	//copiem valorile cadranului selectat
	for (i = 0; i < imagine_aux.linii; i++)
		for (j = 0; j < imagine_aux.coloane; j++)
			imagine_aux.mat[i][j] = imagine->mat[i + y1][j + x1];
	//redimensionam matricea, daca selectia este pe intreaga imagine
	if (ok) {
		free_matrix(imagine);
		imagine->linii = imagine_noua.linii;
		imagine->coloane = imagine_noua.coloane;
		imagine->x1 = y1;
		imagine->x2 = y2;
		imagine->y1 = x1;
		imagine->y2 = x2;
		alloc_matrix(imagine);
	}
	//rotirea spre dreapta, la 90 de grade
	for (i = 0; i < imagine_aux.linii; i++)
		for (j = 0; j < imagine_aux.coloane; j++)
			imagine_noua.mat[j][i] = imagine_aux.mat[y2 - y1 - 1 - i][j];
	//copiem valorile
	for (i = 0; i < imagine_aux.coloane; i++)
		for (j = 0; j < imagine_aux.linii; j++)
			imagine->mat[i + y1][j + x1] = imagine_noua.mat[i][j];

	free_matrix(&imagine_noua);
	free_matrix(&imagine_aux);
}

void functie_rotate(char *comanda, img *imagine)
{
	if (imagine->stare == 0) {
		printf("No image loaded\n");
		return;
	}
	//verificare numar (pozitiv/negativ)
	char *p;
	int aux, ok = 0;
	p = strtok(comanda, "\n ");
	p = strtok(NULL, "\n ");
	if (p[0] == '-') {
		ok = 1;
		p++;
	}

	transformare_numar(&aux, p);
	//echivalam rotatiile necesare ale unghiurilot negative cu unele pozitive
	if (ok)
		aux = 360 - aux;
	if (aux % 90 || aux > 360) {
		printf("Unsupported rotation angle\n");
		return;
	}
	//calculam cate rotatii sunt necesare
	int rotatii = 0;
	if (aux == 90)
		rotatii = 1;
	else if (aux == 180)
		rotatii = 2;
	else if (aux == 270)
		rotatii = 3;

	for (int i = 0; i < rotatii; i++)
		rotate(imagine);

	if (ok) {
		aux = aux - 360;
		printf("%s %d\n", "Rotated", aux);
	} else {
		printf("%s %d\n", "Rotated", aux);
	}
}
