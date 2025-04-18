#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "abstract_graph.hpp"

// had to add these libraries
#include <map>
#include <set>

template <typename ItemType>
class Graph : public AbstractGraph<ItemType>
{
private:
    // using an adjacency list
    std::map<ItemType, std::set<ItemType>> adjacency_list;
    
    // for adjacency list, you may use a std::map to map vertices to the set of adjacent vertices
public:
    Graph();

    int getNumVertices() const;

    int getNumEdges() const;

    bool add(ItemType start, ItemType end);

    bool remove(ItemType start, ItemType end);

    void depthFirstTraversal(ItemType start, void visit(ItemType &));

    void breadthFirstTraversal(ItemType start, void visit(ItemType &));
};

#include "graph.tpp"

#endif
