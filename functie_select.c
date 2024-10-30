//Copyright 2022-2023 Obreja Ana-Maria Grupa 311CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"
#include "aux.h"

//verificam daca in comanda a fost dat un numar
void verificare_numar(char *p, img *imagine, coord c, int *ok)
{
	for (int i = 0; i < (int)strlen(p); i++)
		if ((p[i] < '0' || p[i] > '9') && p[i] != '-') {
			imagine->x1 = c.x1;
			imagine->y1 = c.y1;
			imagine->x2 = c.x2;
			imagine->y2 = c.y2;
			*ok = 0;
		}
	if (!*ok)
		printf("Invalid command\n");
}

//afisarea valorilor selectate
void afisare(coord c, img *imagine, int *ok)
{
	if (imagine->y1 == imagine->y2 || imagine->x1 == imagine->x2) {
		printf("Invalid set of coordinates\n");
		imagine->x1 = c.x1;
		imagine->y1 = c.y1;
		imagine->x2 = c.x2;
		imagine->y2 = c.y2;
		imagine->y2 = c.y2;
		*ok = 0;
		return;
	}
	printf("%s %d %d ", "Selected", imagine->x1, imagine->y1);
	printf("%d %d\n", imagine->x2, imagine->y2);
}

void functie_select(char *comanda, img *imagine)
{
	if (imagine->stare == 0) {
		printf("No image loaded\n");
		return;
	}
	//declararea unei structuri de coordonate, pentru a pastra valorile
	//precedente, in caz ca a aparut o eroare (comanda nevalida)
	coord c;
	char *p;
	int aux, ok = 1;
	c.x1 = imagine->x1, c.x2 = imagine->x2;
	c.y1 = imagine->y1, c.y2 = imagine->y2;

	//preluarea elementelor din comanda
	p = strtok(comanda, " ");
	p = strtok(NULL, " ");

	//verificarea corectitudinii elementului
	verificare_numar(p, imagine, c, &ok);
	if (!ok)
		return;
	//transformarea unui sir de cifre in intreg
	transformare_numar(&aux, p);
	//verificarea incadrarii
	if (aux < 0 || aux > imagine->coloane) {
		printf("Invalid set of coordinates\n");
		imagine->x1 = c.x1, imagine->y1 = c.y1;
		imagine->x2 = c.x2, imagine->y2 = c.y2;
		return;
	}
	//preluarea valorii
	imagine->x1 = aux;

	p = strtok(NULL, " ");
	verificare_numar(p, imagine, c, &ok);
	if (!ok)
		return;
	transformare_numar(&aux, p);
	if (aux < 0 || aux > imagine->linii) {
		printf("Invalid set of coordinates\n");
		imagine->x1 = c.x1, imagine->y1 = c.y1;
		imagine->x2 = c.x2, imagine->y2 = c.y2;
		return;
	}
	imagine->y1 = aux;

	p = strtok(NULL, " ");
	verificare_numar(p, imagine, c, &ok);
	if (!ok)
		return;
	transformare_numar(&aux, p);

	if (aux < 0 || aux > imagine->coloane) {
		imagine->x1 = c.x1, imagine->y1 = c.y1;
		imagine->x2 = c.x2, imagine->y2 = c.y2;
		printf("Invalid set of coordinates\n");
		return;
	}
	imagine->x2 = aux;

	p = strtok(NULL, "\n");
	verificare_numar(p, imagine, c, &ok);
	if (!ok)
		return;
	transformare_numar(&aux, p);
	if (aux < 0 || aux > imagine->linii) {
		imagine->x1 = c.x1, imagine->y1 = c.y1;
		imagine->x2 = c.x2, imagine->y2 = c.y2;
		printf("Invalid set of coordinates\n");
		return;
	}
	imagine->y2 = aux;

	//interschimbarea valorilor
	if (imagine->x1 > imagine->x2)
		swap(&imagine->x1, &imagine->x2);
	if (imagine->y1 > imagine->y2)
		swap(&imagine->y1, &imagine->y2);

	afisare(c, imagine, &ok);
}

//functie pentru selectarea completa a imaginii
void functie_select_all(img *imagine)
{
	if (imagine->stare == 0)
		return;

	imagine->x1 = 0;
	imagine->y1 = 0;

	imagine->x2 = imagine->coloane;
	imagine->y2 = imagine->linii;
}
