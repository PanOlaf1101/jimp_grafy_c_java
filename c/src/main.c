#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "utils.h"
#include "config.h"
#include "graph.h"
#include "triangulation.h"
#include "vector.h"

//All structures using dynamic memory allocation must be declared herein exclusively

struct Config conf;
Graph g;
double **sl_matrix, **help_mat;
Vector eigenvalues;

void cleanup(void) {
	if(sl_matrix != NULL) {
		for(int i = 0; i < g.n_vertices && sl_matrix[i] != NULL; ++i)
			free(sl_matrix[i]);
		free(sl_matrix);
	}
	if(help_mat != NULL) {
		for(int i = 0; i < g.n_vertices && help_mat[i] != NULL; ++i)
			free(help_mat[i]);
		free(help_mat);
	}
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
    double w; //etykiety , wieszchołkiy i waga-odległość

    while (fscanf(conf.input_file, "%s %d %d %lf", name, &u, &v, &w) == 4)
        add_edge(&g, u, v, w); 

    triangulate(&g); //z triangulation.c

    for(int i = 1; i <= g.n_vertices; i++) {
        fprintf(conf.output_file, "%d %.6f %.6f\n", g.vertices[i].id, g.vertices[i].x, g.vertices[i].y);
    }

    free_graph(&g); // koniec programu i grafu
	
	cleanup();
	return 0;
}
