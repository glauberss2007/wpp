//
// Created by Alan de Freitas on 30/03/17.
//

#ifndef TREE_TREE_H
#define TREE_TREE_H

#include <boost/graph/adjacency_list.hpp>

class Tree {
public:
    // add vertex to graph
    void add_vertex();
private:
    // graph g
    boost::adjacency_list<> g;
};

void Tree::add_vertex() {
    boost::add_vertex(g);
}


#endif //TREE_TREE_H
