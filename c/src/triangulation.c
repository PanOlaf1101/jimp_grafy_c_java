#include "triangulation.h"
#include "graph.h"
#include "utils.h"
#include <stdlib.h>
#include <math.h>

#define M_PI acos(-1.0)

static double ccw(double ax, double ay, double bx, double by, double cx, double cy) { // Pomocnicza funkcja do sprawdzania orientacji punktów (iloczyn wektorowy)
    return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
}

static int segments_intersect(double ax, double ay, double bx, double by, // Sprawdza, czy odcinek (a,b) przecina się z odcinkiem (c,d)
                              double cx, double cy, double dx, double dy) {

    if (((ccw(ax, ay, bx, by, cx, cy) > 0) != (ccw(ax, ay, bx, by, dx, dy) > 0)) &&    // Standardowy test przecięcia odcinków oparty na orientacji
        ((ccw(cx, cy, dx, dy, ax, ay) > 0) != (ccw(cx, cy, dx, dy, bx, by) > 0))) {
        return 1;
    }
    return 0;
}

static int count_intersections(Graph *g, int new_idx, Vertex v, int neighbor_j, int neighbor_k) { // Sprawdza, czy dodanie wierzchołka 'v' połączonego z sąsiadami 'j' i 'k' nie łamie planarności
    int intersections = 0;

    for (int i = 0; i < g->n_edges; i++) {     // Sprawdzamy nową krawędź (v, j) oraz (v, k) przeciwko wszystkim istniejącym krawędziom
        int u = g->edges[i].u;
        int w = g->edges[i].v;
       
        if (u < new_idx && w < new_idx) {  // Interesuje program tylko krawędzie, w których oba końce są już narysowane (id < new_idx)
            Vertex *pU = &g->vertices[u];
            Vertex *pW = &g->vertices[w];
            
            if (u != neighbor_j && w != neighbor_j) // Sprawdź krawędź do sąsiada J
                intersections += segments_intersect(v.x, v.y, g->vertices[neighbor_j].x, g->vertices[neighbor_j].y, pU->x, pU->y, pW->x, pW->y);

            if (u != neighbor_k && w != neighbor_k) // Sprawdź krawędź do sąsiada K
                intersections += segments_intersect(v.x, v.y, g->vertices[neighbor_k].x, g->vertices[neighbor_k].y, pU->x, pU->y, pW->x, pW->y);
        }
    }
    return intersections;
}

static double get_weight(Graph *g, int u, int v) {
    for(int i = 0; i < g->n_edges; i++) {
        if((g->edges[i].u == u && g->edges[i].v == v) || (g->edges[i].u == v && g->edges[i].v == u))
            return g->edges[i].w; 
    }
    return -1.0;
}

static int place_vertex_planar(Graph *g, int current_i, int idx_a, int idx_b, double da, double db, Vertex *out) { // Zwraca 1 lub 2 punkty przecięcia  i wybiera jedno z dwóch rozwiązań, które minimalizuje liczbę przecięć krawędzi (planarność)
    Vertex *a = &g->vertices[idx_a];
    Vertex *b = &g->vertices[idx_b];
    double dx = b->x - a->x;
    double dy = b->y - a->y;
    double d = sqrt(dx*dx + dy*dy); // Odległość między środkami okręgów

    if(d == 0 || d > (da + db) || d < fabs(da - db)) return 0;  // Warunek istnienia przecięcia: okręgi muszą na siebie nachodzić i nie mogą być rozłączne

    double x = (da*da - db*db + d*d) / (2*d); // Obliczenia geometryczne punktów przecięcia
    double h = sqrt(fmax(0, da*da - x*x));
    double xm = a->x + x * dx / d;
    double ym = a->y + x * dy / d;

    Vertex v1 = { .id = current_i, .x = xm + (-dy * h / d), .y = ym + (dx * h / d) }; // Generuje dwie możliwości (góra/dół względem linii łączącej)
    Vertex v2 = { .id = current_i, .x = xm - (-dy * h / d), .y = ym - (dx * h / d) };

    if (count_intersections(g, current_i, v1, idx_a, idx_b) <= count_intersections(g, current_i, v2, idx_a, idx_b)) { // Wybiera opcję, która generuje mniej przecięć
        *out = v1;
    } else {
        *out = v2;
    }
    return 1;
}

void triangulate(Graph *g) { // ===Główna funkcja triangulacji: przypisuje współrzędne wszystkim wierzchołkom grafu.===
    int n = g->n_vertices;
    if(n == 0) return;
    g->vertices = alloc(n * sizeof(Vertex));
	
    g->vertices[0] = (Vertex){.id = 0, .x = 0.0, .y = 0.0};// Punkt 0: kotwica w (0,0)
    if(n == 1) return;

    double w01 = get_weight(g, 0, 1); // 1 punkt ustawia na osi X w odległości wynikającej z wagi krawędzi
    if(w01 <= 0) w01 = 1.0;
    g->vertices[1] = (Vertex){.id = 1, .x = w01, .y = 0.0};
    if(n == 2) return;

    for(int i = 2; i < n; i++) { // Pętla dla pozostałych wierzchołków
    	g->vertices[i].id = i;
        int placed = 0;
        int one_neighbor = -1;
        double w_one = 0;

        for(int j = 0; j < i; j++) { // Szuka dwóch sąsiadów, którzy są już narysowani, aby wykonać triangulację
            double wj = get_weight(g, i, j);
            if(wj > 0) {
                if(one_neighbor == -1) { one_neighbor = j; w_one = wj; }
                for(int k = j + 1; k < i; k++) {
                    double wk = get_weight(g, i, k);
                    if(wk > 0) {
                        if(place_vertex_planar(g, i, j, k, wj, wk, &g->vertices[i])) { // Próba postawienia punktu względem pary sąsiadów 'j' i 'k'
                            placed = 1; break;
                        }
                    }
                }
            }
            if(placed) break;
        }

        if(!placed && one_neighbor != -1) { // Jeśli nie znaleziono pary sąsiadów, ustawia punkt względem jednego sąsiada pod kątem
            double angle = (i * M_PI) / 4.0;
            g->vertices[i].x = g->vertices[one_neighbor].x + w_one * cos(angle);
            g->vertices[i].y = g->vertices[one_neighbor].y + w_one * sin(angle);
	
        } else if(!placed) { // Jeśli nie znaleziono pary sąsiadów, ustawia punkt względem jednego sąsiada pod kątem
            g->vertices[i].x = i; g->vertices[i].y = 0;
        }
    }
}
