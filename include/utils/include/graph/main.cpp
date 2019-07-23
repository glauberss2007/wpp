#include <iostream>
#include "Graph.h"

int main() {
    Graph g;
    g.add_vertex();
    g.add_vertex();
    Graph::vertex v1 = g.add_vertex();
    Graph::vertex v2 = g.add_vertex();
    g.add_edge(v1,v2);
    g.add_edge(1,2);
    g.add_edge(1,0);
    g.print_vertices();
    g.print_edges();
    g.print_adjacent(v1);
    g.print_in_edges(v1);
    g.print_out_edges(v1);
    return 0;
}