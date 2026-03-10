#ifndef _CONFIG_H__
#define _CONFIG_H__

#include <stdio.h>

struct Config {
	FILE *input_file, *output_file;
};

void read_config(char *args[], int n);

#endif //_CONFIG_H__
