#include <iostream>
#include <string>

#include "assignments/dg/graph.h"

// hello i am testing too - gary

// Note: At the moment, there is no client.sampleout. Please do your own testing
// Carter test 1
int main() {
  
  gdwg::Graph<std::string, int> g;
  g.InsertNode("hello");
  g.InsertNode("how");
  g.InsertEdge("hello", "how", 4);
  g.InsertEdge("how", "hello", 4);
  g.GetNodes();
  /*
  gdwg::Graph<std::string, int> h;
  h.InsertNode("hello");
  h.InsertNode("how");
  h.InsertEdge("hello", "how", 4);
  h.InsertEdge("how", "hello", 4);
  
  if (g == h) {
      std::cout << "they are equal\n";
  } else {
      std::cout << "they arent equal\n";
  }*/
  
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
