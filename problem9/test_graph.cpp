#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "graph.hpp"

TEST_CASE("Test Construction", "[construction]")
{
  Graph<int> g;
  REQUIRE(g.getNumVertices() == 0);
  REQUIRE(g.getNumEdges() == 0);
}

/* add more tests for other stuff below */

TEST_CASE("Graph<int> Basic Operations and Edge Cases") {
  Graph<int> g1;

  // add and check number of vertices and edges
  REQUIRE(g1.add(1, 2) == true);
  REQUIRE(g1.getNumVertices() == 2);
  REQUIRE(g1.getNumEdges() == 1);

  REQUIRE(g1.add(2, 3) == true);
  REQUIRE(g1.getNumVertices() == 3);
  REQUIRE(g1.getNumEdges() == 2);

  // add invalid edges
  g1.add(1, 2);
  REQUIRE(g1.add(1, 1) == false); // self-loop
  REQUIRE(g1.add(1, 2) == false); // duplicate edge

  Graph<int> g2;
  // add edge with only one node existing
  REQUIRE(g2.add(10, 20) == true);  // first connection always succeeds    FAILS HERE
  // this is not correct
  REQUIRE(g2.add(30, 40) == false); // neither node is connected to the graph

  Graph<int> g3;
  // remove and check number of vertices and edges
  g3.add(1, 2);
  g3.add(2, 3);
  REQUIRE(g3.remove(1, 2) == true);
  REQUIRE(g3.getNumEdges() == 1);
  REQUIRE(g3.getNumVertices() == 2); // node 1 is removed due to isolation

  REQUIRE(g3.remove(2, 3) == true);
  REQUIRE(g3.getNumVertices() == 0); // all nodes removed

  Graph<int> g4;
  // remove non-existent edges
  REQUIRE(g4.remove(1, 2) == false);
  g4.add(1, 2);
  REQUIRE(g4.remove(2, 3) == false);
}


TEST_CASE("double graph") {
    Graph<double> g1;

    // adding and removing
    REQUIRE(g1.add(1.1, 2.2) == true);
    REQUIRE(g1.add(2.2, 3.3) == true);
    REQUIRE(g1.getNumVertices() == 3);
    REQUIRE(g1.getNumEdges() == 2);

    REQUIRE(g1.remove(1.1, 2.2) == true);
    REQUIRE(g1.getNumEdges() == 1);

    Graph<double> g2;
    // add duplicate
    g2.add(4.4, 5.5);
    REQUIRE(g2.add(4.4, 5.5) == false);
    REQUIRE(g2.add(4.4, 4.4) == false);

    // only one node on edge
    REQUIRE(g2.add(5.5, 6.6) == true); // can't be separate from the rest
    REQUIRE(g2.add(6.6, 7.7) == true); // valid, one shared node
    REQUIRE(g2.add(8.8, 9.9) == false); // isolated nodes
}

TEST_CASE("Graph<std::string> Operations") {
    Graph<std::string> g;

    // adding and removing
    REQUIRE(g.add("gavin", "ece302") == true);
    REQUIRE(g.add("ece302", "ece301") == true);
    REQUIRE(g.getNumVertices() == 3);
    REQUIRE(g.getNumEdges() == 2);

    REQUIRE(g.remove("gavin", "ece302") == true);
    REQUIRE(g.getNumEdges() == 1);
    REQUIRE(g.remove("ece302", "ece301") == true);
    REQUIRE(g.getNumVertices() == 0); // they don't connect to each other, exist in separate spaces

    // invalid edge cases
    g.add("hey", "gavin");
    REQUIRE(g.add("hey", "gavin") == false);
    REQUIRE(g.add("hey", "gavin") == false);
    REQUIRE(g.remove("hey", "not gavin") == false);
    REQUIRE(g.remove("not gavin", "not gavin") == false);

    // connection with one node only
    g.add("gavin", "engr12");
    REQUIRE(g.add("engr12", "gavin student") == true);
    REQUIRE(g.add("not gavin student1", "not gavin student2") == false);
}
