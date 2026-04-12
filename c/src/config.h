#ifndef _CONFIG_H__
#define _CONFIG_H__

struct Config {
	FILE *input_file, *output_file;
	char algo;
};

#define ALG_SL 1 //Spectral laytout
#define ALG_TR 2 //Triangulation

void read_config(char *arg[], int n);

#endif //_CONFIG_H__