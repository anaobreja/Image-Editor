//Copyright 2022-2023 Obreja Ana-Maria Grupa 311CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"
#include "aux.h"

//dam valorile acceptate pentru efectuarea rotatiei
void coordonate1(coord *coordonate, img *imagine)
{
	if (imagine->x1 == 0)
		coordonate->x1 = 1;
	else if (imagine->x1 == imagine->coloane)
		coordonate->x1 = imagine->coloane - 1;
	else
		coordonate->x1 = imagine->x1;

	if (imagine->y1 == 0)
		coordonate->y1 = 1;
	else if (imagine->y1 == imagine->linii)
		coordonate->y1 = imagine->linii - 1;
	else
		coordonate->y1 = imagine->y1;

	if (imagine->x2 == 0)
		coordonate->x2 = 1;
	else if (imagine->x2 == imagine->coloane)
		coordonate->x2 = imagine->coloane - 1;
	else
		coordonate->x2 = imagine->x2;

	if (imagine->y2 == 0)
		coordonate->y2 = 1;
	else if (imagine->y2 == imagine->linii)
		coordonate->y2 = imagine->linii - 1;
	else
		coordonate->y2 = imagine->y2;
}

void transformare(double *suma)
{
	for (int i = 0; i < 3; i++)
		if (suma[i] < 0)
			suma[i] = 0;
		else if (suma[i] > 255)
			suma[i] = 255;
}

void apply(img *imagine, int tip)
{
	//declaram o structura auxiliara si una pentru coordonate
	img imagine_noua;
	coord coordonate;
	//initializam nucleele specifice fiecarui efect
	double kernel1[N][N] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
	double kernel2[N][N] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
	double kernel3[N][N] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
	double kernel4[N][N] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			kernel3[i][j] /= 9;
			kernel4[i][j] /= 16;
	}
	coordonate1(&coordonate, imagine);

	imagine_noua.linii = imagine->linii;
	imagine_noua.coloane = imagine->coloane;

	alloc_matrix(&imagine_noua);

	int i, j;

	for (i = 0; i < imagine_noua.linii; i++)
		for (j = 0; j < imagine_noua.coloane; j++)
			imagine_noua.mat[i][j] = imagine->mat[i][j];

	for (i = coordonate.y1; i < coordonate.y2; i++)
		for (j = coordonate.x1; j < coordonate.x2 ; j++) {
			//initializam suma pentru ficare pixel
			double suma[N] = {0};
			double kernel[N][N];
			//preluam valorile nucleului
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					if (tip == 1)
						kernel[i][j] = kernel1[i][j];
					else if (tip == 2)
						kernel[i][j] = kernel2[i][j];
					else if (tip == 3)
						kernel[i][j] = kernel3[i][j];
					else
						kernel[i][j] = kernel4[i][j];

			//calculam suma pentru pixelii de pe fiecare canal
			int a = -1, b;
			for (int k = 0; k < N; k++) {
				b = -1;
				for (int l = 0; l < N; l++) {
					suma[0] += kernel[k][l] * imagine->mat[i + a][j + b].r;
					suma[1] += kernel[k][l] * imagine->mat[i + a][j + b].g;
					suma[2] += kernel[k][l] * imagine->mat[i + a][j + b].b;
					b++;
				}
				a++;
			}
				transformare(suma);
				imagine_noua.mat[i][j].r = suma[0];
				imagine_noua.mat[i][j].g = suma[1];
				imagine_noua.mat[i][j].b = suma[2];
		}

	for (int i = 0; i < imagine_noua.linii; i++)
		for (int j = 0; j < imagine_noua.coloane; j++)
			imagine->mat[i][j] = imagine_noua.mat[i][j];

	free_matrix(&imagine_noua);
}

void functie_apply(char *comanda, img *imagine)
{
	if (imagine->stare == 0) {
		printf("No image loaded\n");
		return;
	}
	char *p, *aux;
	int tip;
	//verificam validitatea comenzii si preluam valorile
	p = strtok(comanda, "\n ");
	p = strtok(NULL, "\n ");

	if (!p) {
		printf("Invalid command\n");
		return;
	}
	//caz imagine alb-negru
	if (imagine->tip == 2 || imagine->tip == 5) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}
	aux = p;
	if (!strcmp(aux, "EDGE")) {
		tip = 1;
	} else if (!strcmp(aux, "SHARPEN")) {
		tip = 2;
	} else if (!strcmp(aux, "BLUR")) {
		tip = 3;
	} else if (!strcmp(aux, "GAUSSIAN_BLUR")) {
		tip = 4;
	} else {
		printf("APPLY parameter invalid\n");
		return;
	}
	apply(imagine, tip);
	printf("%s %s %s\n", "APPLY", aux, "done");
}
