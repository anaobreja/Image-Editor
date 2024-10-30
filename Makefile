#Copyright 2022-2023 Obreja Ana-Maria Grupa 311CA
# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -lm

# define targets
TARGETS=image_editor

build: $(TARGETS)

image_editor: image_editor.c
	$(CC) $(CFLAGS) image_editor.c functie_load.c aux.c functie_select.c functie_crop.c functie_histogram.c functie_save.c functie_apply.c functie_rotate.c -o image_editor

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
