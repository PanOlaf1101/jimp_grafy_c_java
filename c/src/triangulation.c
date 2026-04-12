#include "triangulation.h"
#include "graph.h"
#include "utils.h"

#include <stdlib.h>
#define _USE_MATH_DEFINES 1
#include <math.h>

static double get_weight(Graph *g, int u, int v)
{
    for(int i = 0; i < g->n_edges; i++)
    {
        if((g->edges[i].u == u && g->edges[i].v == v) ||
           (g->edges[i].u == v && g->edges[i].v == u))
            return g->edges[i].w;
    }
    return -1.0;
}

static int place_vertex(Vertex *a, Vertex *b,
                        double da, double db,
                        Vertex *out)
{
    double dx = b->x - a->x;
    double dy = b->y - a->y;
    double d = sqrt(dx*dx + dy*dy);

    if(d == 0) return 0;

    double x = (da*da - db*db + d*d) / (2*d);
    double h_sq = da*da - x*x;

    if(h_sq < 0) h_sq = 0;
    double h = sqrt(h_sq);

    double xm = a->x + x * dx / d;
    double ym = a->y + x * dy / d;

    out->x = xm + (-dy * h / d);
    out->y = ym + ( dx * h / d);

    return 1;
}

void triangulate(Graph *g)
{
    int n = g->n_vertices;

    g->vertices = alloc((n + 1) * sizeof(Vertex));

    if(n == 0) return;

    g->vertices[1].id = 1;
    g->vertices[1].x = 0.0;
    g->vertices[1].y = 0.0;

    if(n == 1) return;

    double w12 = get_weight(g, 1, 2);
    if(w12 <= 0) w12 = 1.0;

    g->vertices[2].id = 2;
    g->vertices[2].x = w12;
    g->vertices[2].y = 0.0;

    if(n == 2) return;

    double w13 = get_weight(g, 1, 3);
    double w23 = get_weight(g, 2, 3);

    g->vertices[3].id = 3;

    if(w13 > 0 && w23 > 0)
    {
        place_vertex(&g->vertices[1], &g->vertices[2],
                     w13, w23,
                     &g->vertices[3]);
    }
    else if(w13 > 0)
    {
        g->vertices[3].x = g->vertices[1].x;
        g->vertices[3].y = g->vertices[1].y + w13;
    }
    else if(w23 > 0)
    {
        g->vertices[3].x = g->vertices[2].x;
        g->vertices[3].y = g->vertices[2].y + w23;
    }
    else
    {
        g->vertices[3].x = 0;
        g->vertices[3].y = 1;
    }

    for(int i = 4; i <= n; i++)
    {
        g->vertices[i].id = i;

        int placed = 0;
        int one_neighbor = -1;
        double w_one = 0;

        for(int j = 1; j < i; j++)
        {
            double wj = get_weight(g, i, j);

            if(wj > 0)
            {
                if(one_neighbor == -1)
                {
                    one_neighbor = j;
                    w_one = wj;
                }

                for(int k = j+1; k < i; k++)
                {
                    double wk = get_weight(g, i, k);

                    if(wk > 0)
                    {
                        if(place_vertex(&g->vertices[j],
                                        &g->vertices[k],
                                        wj, wk,
                                        &g->vertices[i]))
                        {
                            placed = 1;
                            break;
                        }
                    }
                }
            }
            if(placed) break;
        }

        if(!placed && one_neighbor != -1)
        {
            Vertex *v = &g->vertices[one_neighbor];

            double angle = (i * M_PI) / 4.0;

            g->vertices[i].x = v->x + w_one * cos(angle);
            g->vertices[i].y = v->y + w_one * sin(angle);

            placed = 1;
        }

        if(!placed)
        {
            g->vertices[i].x = i;
            g->vertices[i].y = 0;
        }
    }
}
