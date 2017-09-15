// https://theboostcpplibraries.com/boost.graph-vertices-and-edges

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/random_spanning_tree.hpp>

#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/compressed_sparse_row_graph.hpp>

#include <boost/array.hpp>

#include <array>
#include <utility>
#include <tuple>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "termcolor/termcolor.hpp"
#include <ctime>
#include <cstdint>
#include <utility>

int main() {
    std::cout << termcolor::bold << termcolor::underline << "A graph of type boost::adjacency_list with four vertices" << termcolor::reset << std::endl;
    {
        boost::adjacency_list<> g;

        boost::adjacency_list<>::vertex_descriptor v1 = boost::add_vertex(g);
        boost::adjacency_list<>::vertex_descriptor v2 = boost::add_vertex(g);
        boost::adjacency_list<>::vertex_descriptor v3 = boost::add_vertex(g);
        boost::adjacency_list<>::vertex_descriptor v4 = boost::add_vertex(g);

        std::cout << v1 << ", " << v2 << ", " << v3 << ", " << v4 << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Accessing vertices with boost::vertices()" << termcolor::reset << std::endl;
    {
        boost::adjacency_list<> g;

        boost::add_vertex(g);
        boost::add_vertex(g);
        boost::add_vertex(g);
        boost::add_vertex(g);

        std::pair<boost::adjacency_list<>::vertex_iterator,
                boost::adjacency_list<>::vertex_iterator> vs = boost::vertices(g);

        std::copy(vs.first, vs.second,
                  std::ostream_iterator<boost::adjacency_list<>::vertex_descriptor>{
                          std::cout, "\n"});
    }

    std::cout << termcolor::bold << termcolor::underline << "Accessing edges with boost::edges()" << termcolor::reset << std::endl;
    {
        boost::adjacency_list<> g;

        boost::adjacency_list<>::vertex_descriptor v1 = boost::add_vertex(g);
        boost::adjacency_list<>::vertex_descriptor v2 = boost::add_vertex(g);
        boost::add_vertex(g);
        boost::add_vertex(g);

        std::pair<boost::adjacency_list<>::edge_descriptor, bool> p =
                boost::add_edge(v1, v2, g);
        std::cout.setf(std::ios::boolalpha);
        std::cout << p.second << '\n';

        p = boost::add_edge(v1, v2, g);
        std::cout << p.second << '\n';

        p = boost::add_edge(v2, v1, g);
        std::cout << p.second << '\n';

        std::pair<boost::adjacency_list<>::edge_iterator,
                boost::adjacency_list<>::edge_iterator> es = boost::edges(g);

        std::copy(es.first, es.second,
                  std::ostream_iterator<boost::adjacency_list<>::edge_descriptor>{
                          std::cout, "\n"});
    }

    std::cout << termcolor::bold << termcolor::underline << "boost::adjacency_list with selectors" << termcolor::reset << std::endl;
    {
        typedef boost::adjacency_list<boost::setS, boost::vecS,
                boost::undirectedS> graph;
        graph g;

        boost::adjacency_list<>::vertex_descriptor v1 = boost::add_vertex(g);
        boost::adjacency_list<>::vertex_descriptor v2 = boost::add_vertex(g);
        boost::add_vertex(g);
        boost::add_vertex(g);

        std::pair<graph::edge_descriptor, bool> p =
                boost::add_edge(v1, v2, g);
        std::cout.setf(std::ios::boolalpha);
        std::cout << p.second << '\n';

        p = boost::add_edge(v1, v2, g);
        std::cout << p.second << '\n';

        p = boost::add_edge(v2, v1, g);
        std::cout << p.second << '\n';

        std::pair<graph::edge_iterator,
                graph::edge_iterator> es = boost::edges(g);

        std::copy(es.first, es.second,
                  std::ostream_iterator<graph::edge_descriptor>{std::cout, "\n"});
    }

    std::cout << termcolor::bold << termcolor::underline << "Creating indexes automatically with boost::add_edge()" << termcolor::reset << std::endl;
    {
        typedef boost::adjacency_list<boost::setS, boost::vecS,
                boost::undirectedS> graph;
        graph g;

        enum { topLeft, topRight, bottomRight, bottomLeft };

        boost::add_edge(topLeft, topRight, g);
        boost::add_edge(topRight, bottomRight, g);
        boost::add_edge(bottomRight, bottomLeft, g);
        boost::add_edge(bottomLeft, topLeft, g);

        graph::edge_iterator it, end;
        std::tie(it, end) = boost::edges(g);
        std::copy(it, end,
                  std::ostream_iterator<graph::edge_descriptor>{std::cout, "\n"});
    }

    std::cout << termcolor::bold << termcolor::underline << "boost::adjacent_vertices() and boost::out_edges()" << termcolor::reset << std::endl;
    {
        typedef boost::adjacency_list<boost::setS, boost::vecS,
                boost::undirectedS> graph;
        graph g;

        enum { topLeft, topRight, bottomRight, bottomLeft };

        boost::add_edge(topLeft, topRight, g);
        boost::add_edge(topRight, bottomRight, g);
        boost::add_edge(bottomRight, bottomLeft, g);
        boost::add_edge(bottomLeft, topLeft, g);

        graph::adjacency_iterator vit, vend;
        std::tie(vit, vend) = boost::adjacent_vertices(topLeft, g);
        std::copy(vit, vend,
                  std::ostream_iterator<graph::vertex_descriptor>{std::cout, "\n"});

        graph::out_edge_iterator eit, eend;
        std::tie(eit, eend) = boost::out_edges(topLeft, g);
        std::for_each(eit, eend,
                      [&g](graph::edge_descriptor it)
                      { std::cout << boost::target(it, g) << '\n'; });
    }

    std::cout << termcolor::bold << termcolor::underline << "Initializing boost::adjacency_list with lines" << termcolor::reset << std::endl;
    {
        enum { topLeft, topRight, bottomRight, bottomLeft };

        std::array<std::pair<int, int>, 4> edges{{
                                                         std::make_pair(topLeft, topRight),
                                                         std::make_pair(topRight, bottomRight),
                                                         std::make_pair(bottomRight, bottomLeft),
                                                         std::make_pair(bottomLeft, topLeft)
                                                 }};

        typedef boost::adjacency_list<boost::setS, boost::vecS,
                boost::undirectedS> graph;
        graph g{edges.begin(), edges.end(), 4};

        std::cout << boost::num_vertices(g) << '\n';
        std::cout << boost::num_edges(g) << '\n';

        g.clear();
    }

    std::cout << termcolor::bold << termcolor::underline << "Visiting points from inside to outside with breadth_first_search()" << termcolor::reset << std::endl;
    {
        enum { topLeft, topRight, bottomRight, bottomLeft };

        std::array<std::pair<int, int>, 4> edges{{
                                                         std::make_pair(topLeft, topRight),
                                                         std::make_pair(topRight, bottomRight),
                                                         std::make_pair(bottomRight, bottomLeft),
                                                         std::make_pair(bottomLeft, topLeft)
                                                 }};

        typedef boost::adjacency_list<boost::setS, boost::vecS,
                boost::undirectedS> graph;
        graph g{edges.begin(), edges.end(), 4};

        boost::array<int, 4> distances{{0}};

        boost::breadth_first_search(g, topLeft,
                                    boost::visitor(
                                            boost::make_bfs_visitor(
                                                    boost::record_distances(distances.begin(),
                                                                            boost::on_tree_edge{}))));

        std::copy(distances.begin(), distances.end(),
                  std::ostream_iterator<int>{std::cout, "\n"});
    }

    std::cout << termcolor::bold << termcolor::underline << "Finding paths with breadth_first_search()" << termcolor::reset << std::endl;
    {
        enum { topLeft, topRight, bottomRight, bottomLeft };

        std::array<std::pair<int, int>, 4> edges{{
                                                         std::make_pair(topLeft, topRight),
                                                         std::make_pair(topRight, bottomRight),
                                                         std::make_pair(bottomRight, bottomLeft),
                                                         std::make_pair(bottomLeft, topLeft)
                                                 }};

        typedef boost::adjacency_list<boost::setS, boost::vecS,
                boost::undirectedS> graph;
        graph g{edges.begin(), edges.end(), 4};

        boost::array<int, 4> predecessors;
        predecessors[bottomRight] = bottomRight;

        boost::breadth_first_search(g, bottomRight,
                                    boost::visitor(
                                            boost::make_bfs_visitor(
                                                    boost::record_predecessors(predecessors.begin(),
                                                                               boost::on_tree_edge{}))));

        int p = topLeft;
        while (p != bottomRight)
        {
            std::cout << p << '\n';
            p = predecessors[p];
        }
        std::cout << p << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Finding distances and paths with breadth_first_search()" << termcolor::reset << std::endl;
    {
        enum { topLeft, topRight, bottomRight, bottomLeft };

        std::array<std::pair<int, int>, 4> edges{{
                                                         std::make_pair(topLeft, topRight),
                                                         std::make_pair(topRight, bottomRight),
                                                         std::make_pair(bottomRight, bottomLeft),
                                                         std::make_pair(bottomLeft, topLeft)
                                                 }};

        typedef boost::adjacency_list<boost::setS, boost::vecS,
                boost::undirectedS> graph;
        graph g{edges.begin(), edges.end(), 4};

        boost::array<int, 4> distances{{0}};
        boost::array<int, 4> predecessors;
        predecessors[bottomRight] = bottomRight;

        boost::breadth_first_search(g, bottomRight,
                                    boost::visitor(
                                            boost::make_bfs_visitor(
                                                    std::make_pair(
                                                            boost::record_distances(distances.begin(),
                                                                                    boost::on_tree_edge()),
                                                            boost::record_predecessors(predecessors.begin(),
                                                                                       boost::on_tree_edge{})))));

        std::for_each(distances.begin(), distances.end(),
                      [](int d){ std::cout << d << '\n'; });

        int p = topLeft;
        while (p != bottomRight)
        {
            std::cout << p << '\n';
            p = predecessors[p];
        }
        std::cout << p << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Finding paths with dijkstra_shortest_paths()" << termcolor::reset << std::endl;
    {
        enum { topLeft, topRight, bottomRight, bottomLeft };

        std::array<std::pair<int, int>, 4> edges{{
                                                         std::make_pair(topLeft, topRight),
                                                         std::make_pair(topRight, bottomRight),
                                                         std::make_pair(bottomRight, bottomLeft),
                                                         std::make_pair(bottomLeft, topLeft)
                                                 }};

        typedef boost::adjacency_list<boost::listS, boost::vecS,
                boost::undirectedS, boost::no_property,
                boost::property<boost::edge_weight_t, int>> graph;

        std::array<int, 4> weights{{2, 1, 1, 1}};

        graph g{edges.begin(), edges.end(), weights.begin(), 4};

        boost::array<int, 4> directions;
        boost::dijkstra_shortest_paths(g, bottomRight,
                                       boost::predecessor_map(directions.begin()));

        int p = topLeft;
        while (p != bottomRight)
        {
            std::cout << p << '\n';
            p = directions[p];
        }
        std::cout << p << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "User-defined properties with dijkstra_shortest_paths()" << termcolor::reset << std::endl;
    {
        enum { topLeft, topRight, bottomRight, bottomLeft };

        std::array<std::pair<int, int>, 4> edges{{
                                                         std::make_pair(topLeft, topRight),
                                                         std::make_pair(topRight, bottomRight),
                                                         std::make_pair(bottomRight, bottomLeft),
                                                         std::make_pair(bottomLeft, topLeft)
                                                 }};

        struct edge_properties
        {
            int weight;
        };

        typedef boost::adjacency_list<boost::listS, boost::vecS,
                boost::undirectedS, boost::no_property,
                edge_properties> graph;

        graph g{edges.begin(), edges.end(), 4};

        graph::edge_iterator it, end;
        boost::tie(it, end) = boost::edges(g);
        g[*it].weight = 2;
        g[*++it].weight = 1;
        g[*++it].weight = 1;
        g[*++it].weight = 1;

        boost::array<int, 4> directions;
        boost::dijkstra_shortest_paths(g, bottomRight,
                                       boost::predecessor_map(directions.begin()).
                                                                                         weight_map(boost::get(&edge_properties::weight, g)));

        int p = topLeft;
        while (p != bottomRight)
        {
            std::cout << p << '\n';
            p = directions[p];
        }
        std::cout << p << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Initializing user-defined properties at graph definition" << termcolor::reset << std::endl;
    {
        enum { topLeft, topRight, bottomRight, bottomLeft };

        std::array<std::pair<int, int>, 4> edges{{
                                                         std::make_pair(topLeft, topRight),
                                                         std::make_pair(topRight, bottomRight),
                                                         std::make_pair(bottomRight, bottomLeft),
                                                         std::make_pair(bottomLeft, topLeft)
                                                 }};

        struct edge_properties
        {
            int weight;
        };

        typedef boost::adjacency_list<boost::listS, boost::vecS,
                boost::undirectedS, boost::no_property,
                edge_properties> graph;

        boost::array<edge_properties, 4> props{{2, 1, 1, 1}};

        graph g{edges.begin(), edges.end(), props.begin(), 4};

        boost::array<int, 4> directions;
        boost::dijkstra_shortest_paths(g, bottomRight,
                                       boost::predecessor_map(directions.begin()).
                                                                                         weight_map(boost::get(&edge_properties::weight, g)));

        int p = topLeft;
        while (p != bottomRight)
        {
            std::cout << p << '\n';
            p = directions[p];
        }
        std::cout << p << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Random paths with random_spanning_tree()" << termcolor::reset << std::endl;
    {
        enum { topLeft, topRight, bottomRight, bottomLeft };

        std::array<std::pair<int, int>, 4> edges{{
                                                         std::make_pair(topLeft, topRight),
                                                         std::make_pair(topRight, bottomRight),
                                                         std::make_pair(bottomRight, bottomLeft),
                                                         std::make_pair(bottomLeft, topLeft)
                                                 }};

        struct edge_properties
        {
            int weight;
        };

        typedef boost::adjacency_list<boost::listS, boost::vecS,
                boost::undirectedS> graph;

        graph g{edges.begin(), edges.end(), 4};

        boost::array<int, 4> predecessors;

        std::mt19937 gen{static_cast<uint32_t>(std::time(0))};
        boost::random_spanning_tree(g, gen,
                                    boost::predecessor_map(predecessors.begin()).
                                                                                        root_vertex(bottomLeft));

        int p = topRight;
        while (p != -1)
        {
            std::cout << p << '\n';
            p = predecessors[p];
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Graphs with boost::adjacency_matrix" << termcolor::reset << std::endl;
    {
        enum { topLeft, topRight, bottomRight, bottomLeft };

        std::array<std::pair<int, int>, 4> edges{{
                                                         std::make_pair(topLeft, topRight),
                                                         std::make_pair(topRight, bottomRight),
                                                         std::make_pair(bottomRight, bottomLeft),
                                                         std::make_pair(bottomLeft, topLeft)
                                                 }};

        typedef boost::adjacency_matrix<boost::undirectedS> graph;
        graph g{edges.begin(), edges.end(), 4};
    }

    std::cout << termcolor::bold << termcolor::underline << "Graphs with boost::compressed_sparse_row_graph" << termcolor::reset << std::endl;
    {
        enum { topLeft, topRight, bottomRight, bottomLeft };

        std::array<std::pair<int, int>, 4> edges{{
                                                         std::make_pair(topLeft, topRight),
                                                         std::make_pair(topRight, bottomRight),
                                                         std::make_pair(bottomRight, bottomLeft),
                                                         std::make_pair(bottomLeft, topLeft)
                                                 }};

        typedef boost::compressed_sparse_row_graph<boost::bidirectionalS> graph;
        graph g{boost::edges_are_unsorted_multi_pass, edges.begin(),
                edges.end(), 4};
    }
}