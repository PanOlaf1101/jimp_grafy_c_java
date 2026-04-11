#include <stdio.h>
#include <stdlib.h>
#include "config.h"

extern struct Config conf;

void read_config(char *args[], int n)
{
    if(n < 3){
        printf("Użycie programu: %s <plik_wejściowy> <plik_wyjściowy>\n", args[0]);
        exit(1);
    }

    conf.input_file = fopen(args[1], "r");
    if(!conf.input_file){
        printf("Błąd: nie można otworzyć pliku wejściowego %s\n", args[1]);
        exit(1);
    }

    conf.output_file = fopen(args[2], "w");
    if(!conf.output_file){
        printf("Błąd: nie można utworzyć pliku wyjściowego %s\n", args[2]);
        fclose(conf.input_file);
        exit(1);
    }
