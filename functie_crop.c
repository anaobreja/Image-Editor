//Copyright 2022-2023 Obreja Ana-Maria Grupa 311CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"
#include "aux.h"

void functie_crop(img *imagine)
{
	if (imagine->stare == 0) {
		printf("No image loaded\n");
		return;
	}

	//declaram o noua structura
	img imagine_noua;
	int x1, x2, y1, y2;

	x1 = imagine->x1, x2 = imagine->x2;
	y1 = imagine->y1, y2 = imagine->y2;

	//salvam noile dimensiuni, in functie de valorile selectate
	imagine_noua.coloane = x2 - x1;
	imagine_noua.linii = y2 - y1;

	alloc_matrix(&imagine_noua);

	int i, j;
	//salvam valorile din cadranul seleca
	for (i = 0; i < imagine_noua.linii; i++)
		for (j = 0; j < imagine_noua.coloane; j++)
			imagine_noua.mat[i][j] = imagine->mat[i + y1][j + x1];

	//redimensionarea matricei initiale
	free_matrix(imagine);

	imagine->linii = imagine_noua.linii;
	imagine->coloane = imagine_noua.coloane;

	alloc_matrix(imagine);
	//copiem valorile din cadran
	for (i = 0; i < imagine->linii; i++)
		for (j = 0; j < imagine->coloane; j++)
			imagine->mat[i][j] = imagine_noua.mat[i][j];

	functie_select_all(imagine);

	free_matrix(&imagine_noua);

	printf("Image cropped\n");
}
