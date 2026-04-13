#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "utils.h"
#include "config.h"
#include "graph.h"
#include "triangulation.h"

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

    // testowy main-użycie triangulacji
    Graph g = create_graph(1000);

    char name[32];
    int u, v;
    double w; //etukiety , wieszchołkiy i waga-odległość

    while (fscanf(conf.input_file, "%s %d %d %lf",//czyta format
                  name, &u, &v, &w) == 4)
    {
        add_edge(&g, u - 1, v - 1, w);
    }

    triangulate(&g);

    for (int i = 0; i < g.n_vertices; i++) //output
    {

        fprintf(conf.output_file, "%d %.6f %.6f\n",
                g.vertices[i].id + 1,
                g.vertices[i].x,
                g.vertices[i].y);
    }

    free_graph(&g); // koniec programu i grafu


	cleanup();
	return 0;
}
