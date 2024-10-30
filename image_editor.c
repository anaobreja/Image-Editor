#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"
#include "aux.h"

int main(void)
{
	char *comanda;
	comanda = (char *)malloc(100 * sizeof(char));
	img imagine;
	imagine.stare = 0;
	int ok = 1;

	while (ok) {
		fgets(comanda, MAX, stdin);
		if (strstr(comanda, "LOAD")) {
			functie_load(comanda, &imagine);
		} else if (strstr(comanda, "SELECT ALL")) {
			functie_select_all(&imagine);
		if (imagine.stare == 0)
			printf("No image loaded\n");
		else
			printf("%s\n", "Selected ALL");
		} else if (strstr(comanda, "SELECT")) {
			functie_select(comanda, &imagine);
		} else if (strstr(comanda, "ROTATE")) {
			functie_rotate(comanda, &imagine);
		} else if (strstr(comanda, "CROP")) {
			functie_crop(&imagine);
		} else if (strstr(comanda, "HISTOGRAM")) {
			functie_histogram(comanda, imagine);
		} else if (strstr(comanda, "APPLY")) {
			functie_apply(comanda, &imagine);
		} else if (strstr(comanda, "SAVE")) {
			functie_save(comanda, imagine);
		} else if (strstr(comanda, "EQUALIZE")) {
			functie_equalize(imagine);
		} else if (strstr(comanda, "EXIT")) {
			functie_exit(&imagine, &ok);
		} else {
			printf("%s\n", "Invalid command");
		}
	}
	free(comanda);
	return 0;
}
