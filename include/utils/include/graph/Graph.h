//
// Created by Alan de Freitas on 30/03/17.
//

#ifndef TREE_GRAPH_H
#define TREE_GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/visitors.hpp>
#include <vector>

// reference: http://www.boost.org/doc/libs/1_63_0/libs/graph/doc/table_of_contents.html
class Graph {
public:
    /*
     *  Datatypes
     */
    // graph
    using graph = boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS, boost::no_property, boost::no_property>;
    // iterators
    using iterator = graph::vertex_iterator;
    using vertex_iterator = graph::vertex_iterator;
    using edge_iterator = graph::edge_iterator;
    using out_edge_iterator = graph::out_edge_iterator;
    using in_edge_iterator = graph::in_edge_iterator;
    using adjacency_iterator = graph::adjacency_iterator;
    // objects
    using vertex = graph::vertex_descriptor;
    using edge = graph::edge_descriptor;

    /*
     * Altering the graph
     */
    vertex add_vertex();
    edge add_edge(vertex,vertex);
    void clear(){g.clear();}

    size_t size_vertices() {return boost::num_vertices(g);};
    size_t size_edges() {return boost::num_edges(g);};

    /*
     * Algorithms
     */



    /*
     * Getting iterators
     */
    // Non-modifying: get iterators to vertices and edges
    std::pair<iterator,iterator> get_vertices();
    iterator begin();
    iterator end();

    std::pair<adjacency_iterator,adjacency_iterator> get_adjacent_vertices(vertex);
    adjacency_iterator begin_adjacent(vertex);
    adjacency_iterator end_adjacent(vertex);

    std::pair<out_edge_iterator,out_edge_iterator> get_out_edges(vertex);
    out_edge_iterator begin_out_edges(vertex);
    out_edge_iterator end_out_edges(vertex);

    std::pair<in_edge_iterator,in_edge_iterator> get_in_edges(vertex);
    in_edge_iterator begin_in_edges(vertex);
    in_edge_iterator end_in_edges(vertex);

    std::pair<edge_iterator,edge_iterator> get_edges();
    edge_iterator begin_edges();
    edge_iterator end_edges();

    /*
     * Display
     */
    // Non-modifying to get edges
    void print_vertices();
    void print_edges();
    void print_in_edges(vertex);
    void print_out_edges(vertex);
    void print_adjacent(vertex);



private:
    // graph g
    graph g;
};

using iterator = Graph::iterator;
using edge_iterator = Graph::edge_iterator;
using in_edge_iterator = Graph::in_edge_iterator;
using out_edge_iterator = Graph::out_edge_iterator;
using adjacency_iterator = Graph::adjacency_iterator;
using vertex_iterator = Graph::vertex_iterator;
using vertex = Graph::vertex;
using edge = Graph::edge;

vertex Graph::add_vertex() {
    return boost::add_vertex(g);
}

edge Graph::add_edge(vertex v1, vertex v2) {
    return boost::add_edge(v1, v2, g).first;
}


std::pair<iterator,iterator> Graph::get_vertices(){
    return boost::vertices(g);
};

std::pair<edge_iterator,edge_iterator> Graph::get_edges(){
    return boost::edges(g);
};

edge_iterator Graph::begin_edges(){
    return boost::edges(g).first;
}

edge_iterator Graph::end_edges(){
    return boost::edges(g).second;
}

iterator Graph::begin(){
    return boost::vertices(g).first;
};

iterator Graph::end(){
    return boost::vertices(g).second;
};

std::pair<adjacency_iterator,adjacency_iterator> Graph::get_adjacent_vertices(vertex v){
    return boost::adjacent_vertices(v,g);
};

std::pair<in_edge_iterator,in_edge_iterator> Graph::get_in_edges(vertex v){
    return boost::in_edges(v,g);
};

std::pair<out_edge_iterator,out_edge_iterator> Graph::get_out_edges(vertex v){
    return boost::out_edges(v,g);
};


adjacency_iterator Graph::begin_adjacent(vertex v){
    return boost::adjacent_vertices(v,g).first;
}

adjacency_iterator Graph::end_adjacent(vertex v){
    return boost::adjacent_vertices(v,g).second;
}


void Graph::print_vertices(){
    std::pair<iterator,iterator> vs = get_vertices();
    std::copy(vs.first, vs.second, std::ostream_iterator<vertex>{std::cout, "\n"});
}

void Graph::print_adjacent(vertex v){
    std::pair<adjacency_iterator,adjacency_iterator> es = get_adjacent_vertices(v);
    std::copy(es.first, es.second, std::ostream_iterator<vertex>{std::cout, "\n"});
}


void Graph::print_edges(){
    std::pair<edge_iterator,edge_iterator> es = get_edges();
    std::copy(es.first, es.second, std::ostream_iterator<edge>{std::cout, "\n"});
}

void Graph::print_in_edges(vertex v){
    std::pair<in_edge_iterator,in_edge_iterator> es = get_in_edges(v);
    std::copy(es.first, es.second, std::ostream_iterator<edge>{std::cout, "\n"});

}
void Graph::print_out_edges(vertex v){
    std::pair<out_edge_iterator,out_edge_iterator> es = get_out_edges(v);
    std::copy(es.first, es.second, std::ostream_iterator<edge>{std::cout, "\n"});

}


#endif //TREE_GRAPH_H
