#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "utils.h"
#include "config.h"

//All structures using dynamic memory allocation must be declared herein exclusively

struct Config conf;

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
