#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <locale.h>

//All structures using dynamic memory allocation must be declared herein exclusively

struct Config {
	FILE *input_file, *output_file;
};

struct Config conf;

void read_config(char *arg[], int n) {
	for(int i = 0; i < n; ++i) {
		if(strcmp(arg[i], "-i") == 0) {
			if(++i >= n)
				error_msg("Nie podano nazwy pliku wejściowego");
			if(conf.input_file != NULL)
				error_msg("Plik wejściowy został już podany");

			conf.input_file = fopen(arg[i], "r");
			if(conf.input_file == NULL)
				verror_msg("Nie można otworzyć pliku \"%s\"", arg[i]);
		} else if(strcmp(arg[i], "-o") == 0) {
			if(++i >= n)
				error_msg("Nie podano nazwy pliku wyjściowego");
			if(conf.output_file != NULL)
				error_msg("Plik wyjśćiowy został już podany");

			conf.output_file = fopen(arg[i], "w");
			if(conf.output_file == NULL)
				verror_msg("Nie można otworzyć pliku \"%s\"", arg[i]);
		} else
			verror_msg("Podano niepoprawny argument: \"%s\"", arg[i]);
	}
}

void cleanup(void) {
	if(conf.input_file != NULL && conf.input_file != stdin)
		fclose(conf.input_file);
	if(conf.output_file != NULL && conf.output_file != stdout)
		fclose(conf.output_file);
}

int main(int argc, char *argv[]) {
	setlocale(LC_CTYPE, "C.UTF-8");

	read_config(argv+1, argc-1);

	cleanup();
	return 0;
}
