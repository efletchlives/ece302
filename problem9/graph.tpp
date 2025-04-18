#include "graph.hpp"

template <typename ItemType>
// default constructor
Graph<ItemType>::Graph()
{}

template <typename ItemType>
// gets the number of vertices in the graph
int Graph<ItemType>::getNumVertices() const
{
  return adjacency_list.size(); // num of vertices = size of adjacency list
}

template <typename ItemType>
// gets the number of edges in the graph
int Graph<ItemType>::getNumEdges() const
{
  int edge_count = 0;
  for (auto i = adjacency_list.begin(); i != adjacency_list.end(); i++) {
    edge_count += i->second.size();
  }
  return edge_count / 2; // since the function above counts double, divide result by 2
}

template <typename ItemType>
// adds a connection between start and end to the graph
bool Graph<ItemType>::add(ItemType start, ItemType end)
{
  // exception: start = end, there's no connection to make
  if(start == end) {
    return false;
  }

  // checking if connection is possible
  if(adjacency_list.size() != 0) {
    bool poss_connect = false;
    for (auto i = adjacency_list.begin(); i != adjacency_list.end(); i++) {
      if(i->first == start || i->first == end) {
        poss_connect = true;
      }
    }

    // exception: if connection is not possible
    if (poss_connect == false) {
      return false;
    }
  }

  // exception: no duplicates of connections between start and end allowed
  if(adjacency_list[start].count(end) > 0 || adjacency_list[end].count(start) > 0) {
    return false;
  }

  // add connection between start and end using built-in erase map function
  adjacency_list[start].insert(end);
  adjacency_list[end].insert(start);

  return true; // connection made between start and end successful
}

template <typename ItemType>
// removes a connection between start and end in the graph
bool Graph<ItemType>::remove(ItemType start, ItemType end)
{
  // exception: connection does not exist
  if(adjacency_list[start].count(end) == 0 || adjacency_list[end].count(start) == 0) {
    return false;
  }

  // remove connection between start and end using built-in erase map function
  adjacency_list[start].erase(end);
  adjacency_list[end].erase(start);

  // remove start and end
  if(adjacency_list[start].empty()) {
    adjacency_list.erase(start);
  }
  if(adjacency_list[end].empty()) {
    adjacency_list.erase(end);
  }

  return true; // removal of connection between start and end successful
}

template <typename ItemType>
void Graph<ItemType>::depthFirstTraversal(ItemType start, void visit(ItemType &))
{
  // BONUS TODO, you may need a stack and/or a recursive helper function
}

template <typename ItemType>
void Graph<ItemType>::breadthFirstTraversal(ItemType start, void visit(ItemType &))
{
  // BONUS TODO, you may need a queue and/or a recursive helper function
}