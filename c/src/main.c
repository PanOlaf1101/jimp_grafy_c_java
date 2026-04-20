#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "utils.h"
#include "config.h"
#include "graph.h"
#include "triangulation.h"
#include "spectral.h"
#include "vector.h"
#include "matrix.h"

//All structures using dynamic memory allocation must be declared herein exclusively

struct Config conf;
Graph g;
double **A, **Q, **R;
Vector eigenvalues;

void cleanup(void) {
	free_matrix(A, g.n_vertices);
	free_matrix(Q, g.n_vertices);
	free_matrix(R, g.n_vertices);
	free_graph(&g);
	free_vec(&eigenvalues);
	if(conf.input_file != NULL && conf.input_file != stdin)
		fclose(conf.input_file);
	if(conf.output_file != NULL && conf.output_file != stdout)
		fclose(conf.output_file);
}

int main(int argc, char *argv[]) {
	setlocale(LC_CTYPE, "C.UTF-8");

	read_config(argv+1, argc-1);

	// testowy main-użycie triangulacji
	g = create_graph(1000);

	char name[32];
	int u, v;
	double w; //etukiety , wieszchołkiy i waga-odległość

	while (fscanf(conf.input_file, "%s %d %d %lf",//czyta format
				  name, &u, &v, &w) == 4)
	{
		add_edge(&g, u - 1, v - 1, w);
	}

	if(conf.algo == ALG_SL)
		spectral(&g);
	else
		triangulate(&g);

	for (int i = 0; i < g.n_vertices; i++) //output
	{

		fprintf(conf.output_file, "%d %.6f %.6f\n",
				g.vertices[i].id + 1,
				g.vertices[i].x,
				g.vertices[i].y);
	}

	cleanup();
	return 0;
}
