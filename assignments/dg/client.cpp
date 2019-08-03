#include <iostream>
#include <map>
#include <string>
#include <tuple>

// Change this back to absolute path, only for IDE
//#include "assignments/dg/graph.h"
#include "graph.h"

int main() {
  gdwg::Graph<int, int> g{1, 2, 3, 4, 5, 6};
  g.InsertEdge(1, 5, -1);
  g.InsertEdge(2, 1, 1);
  g.InsertEdge(2, 4, 2);
  g.InsertEdge(3, 2, -8);
  g.InsertEdge(3, 2, 2);
  g.InsertEdge(4, 1, -4);
  g.InsertEdge(4, 5, 3);
  g.InsertEdge(5, 2, 7);
  g.InsertEdge(6, 2, 5);
  g.InsertEdge(6, 3, 10);

  gdwg::Graph<int, int> res{1, 2, 3, 4, 5, 6};
  res.InsertEdge(2, 1, 1);
  res.InsertEdge(2, 4, 2);
  res.InsertEdge(3, 2, -8);
  res.InsertEdge(3, 2, 2);
  res.InsertEdge(4, 1, -4);
  res.InsertEdge(4, 5, 3);
  res.InsertEdge(5, 2, 7);
  res.InsertEdge(6, 2, 5);
  res.InsertEdge(6, 3, 10);
  if (g.erase(1, 5, -1)==true){
    std::cout << "True\n";
  }
  if (g==res){
    std::cout << "True\n";
  } else {
    std::cout << g;
  }

}
