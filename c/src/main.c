#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <locale.h>

//All structures using dynamic memory allocation must be declared herein exclusively

struct Config {
	FILE *input_file, *output_file;
	char algo;
};

#define ALG_SL 1 //Spectral laytout
#define ALG_TR 2 //Triangulation

struct Config conf;

void read_config(char *arg[], int n) {
	for(int i = 0; i < n; ++i) {
		if(arg[i][0] == '-') {
			switch(arg[i][1]) {
			case 'i':
				if(++i >= n)
					error_msg("Nie podano nazwy pliku wejściowego");
				if(conf.input_file != NULL)
					error_msg("Plik wejściowy został już podany");

				conf.input_file = fopen(arg[i], "r");
				if(conf.input_file == NULL)
					verror_msg("Nie można otworzyć pliku wejściowego \"%s\"", arg[i]);
				break;
			case 'o':
				if(++i >= n)
					error_msg("Nie podano nazwy pliku wyjściowego");
				if(conf.output_file != NULL)
					error_msg("Plik wyjśćiowy został już podany");

				conf.output_file = fopen(arg[i], "w");
				if(conf.output_file == NULL)
					verror_msg("Nie można otworzyć pliku wyjściowego \"%s\"", arg[i]);
				break;
			case 'a':
				if(++i >= n)
					error_msg("Nie podano kodu algorytmu");
				if(conf.algo != 0)
					error_msg("Kod algorytmu został już podany");
				if(strcmp(arg[i], "s") == 0)
					conf.algo = ALG_SL;
				else if(strcmp(arg[i], "t") == 0)
					conf.algo = ALG_TR;
				else
					verror_msg("Podano niepoprawny kod algorytmu \"%s\"! Wpisz \"t\" lub \"s\"", arg[i]);
				break;
			default:
				goto WRONG_ARG;
			}
		} else {
		WRONG_ARG:
			verror_msg("Podano niepoprawny argument: \"%s\"", arg[i]);
		}
	}
	if(conf.input_file == NULL)
		conf.input_file = stdin;
	if(conf.output_file == NULL)
		conf.output_file = stdout;
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
