#include <iostream>
#include <string>

// Change this back to absolute path, only for IDE
//#include "assignments/dg/graph.h"
#include "graph.h"

// hello i am testing too - gary

// Note: At the moment, there is no client.sampleout. Please do your own testing
// Carter test 1
int main() {

    gdwg::Graph<std::string, std::string> g;
    g.InsertNode("d");
    g.InsertNode("g");
    g.InsertNode("f");
    g.InsertNode("a");
    g.InsertNode("b");
    g.InsertNode("c");
    g.InsertNode("e");

    g.InsertEdge("b", "c", "awo");
    g.InsertEdge("c", "e", "thaee");
    g.InsertEdge("a", "b", "abc");
    g.InsertEdge("a", "b", "abcd");
    g.InsertEdge("a", "b", "abid");
    g.InsertEdge("a", "c", "two");
    g.InsertEdge("e", "d", "thcee");
    g.InsertEdge("g", "f", "thdee");
    g.InsertEdge("d", "f", "thqfee");

    std::cout << g << '\n';


  /*
  g.InsertNode("are");
  g.InsertNode("you?");

  g.InsertEdge("hello", "how", 5);
  g.InsertEdge("hello", "are", 8);
  g.InsertEdge("hello", "are", 2);

  g.InsertEdge("how", "you?", 1);
  g.InsertEdge("how", "hello", 4);

  g.InsertEdge("are", "you?", 3);

  std::cout << g << '\n';

  gdwg::Graph<std::string, int> g2{g};

  std::cout << g2 << "\n";

  // This is a structured binding.
  // https://en.cppreference.com/w/cpp/language/structured_binding
  // It allows you to unpack your tuple.
  for (const auto& [from, to, weight] : g) {
    std::cout << from << " -> " << to << " (weight " << weight << ")\n";
  }*/
}
