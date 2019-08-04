#include <iostream>
#include <map>
#include <string>
#include <tuple>

// Change this back to absolute path, only for IDE
//#include "assignments/dg/graph.h"
#include "graph.h"

int main() {
  gdwg::Graph<std::string, int> graph{"hi", "bye"};
  graph.InsertEdge("hi", "bye", 3);
  graph.InsertEdge("hi", "hi", 10);
  graph.InsertEdge("hi", "hi", 12);
  graph.InsertEdge("bye", "hi", 3);
  gdwg::Graph<std::string, int> ans{"hi", "bye"};
  ans.InsertEdge("hi", "bye", 3);
  ans.InsertEdge("hi", "hi", 12);
  ans.InsertEdge("bye", "hi", 3);
  gdwg::Graph<std::string, int> ans2{"hi", "bye"};
  ans2.InsertEdge("hi", "hi", 12);
  ans2.InsertEdge("bye", "hi", 3);
  gdwg::Graph<std::string, int> ans3{"hi", "bye"};

  graph.erase(graph.find("hi", "hi", 1));

  if (graph.erase(graph.find("hi", "hi", 10)) == graph.find("hi", "hi", 12)) {
    std::cout << "True\n";
  }

  if (ans == graph) {
    std::cout << "ans == graph\n";
  }
}
