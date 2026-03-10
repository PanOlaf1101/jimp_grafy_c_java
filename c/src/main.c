#include <stdio.h>
#include "config.h"

//All structures using dynamic memory allocation must be declared herein exclusively

struct Config conf;

void cleanup(void) {
	fclose(conf.input_file);
	fclose(conf.output_file);
}

int main(int argc, char *argv[]) {

}
