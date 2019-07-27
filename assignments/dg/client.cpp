#include <iostream>
#include <string>
#include <map>

// Change this back to absolute path, only for IDE
//#include "assignments/dg/graph.h"
#include "graph.h"

// hello i am testing too - gary

// Note: At the moment, there is no client.sampleout. Please do your own testing
// Carter test 1
int main() {
/*
    std::vector<std::string> vec{"hello"};
    gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
    std::cout << graph;
    graph.Replace("hello", "yes");
    std::cout << graph;

*/
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertEdge("hi", "bye", 3);
    graph.InsertEdge("hi", "bye", 2);
    graph.InsertEdge("bye", "hi", 3);
    graph.InsertEdge("bye", "hi", 2);
    
    std::cout << graph << "\n";
    
    
    
    gdwg::Graph<int, std::string> graph1;
    graph1.InsertNode(4);
    graph1.InsertNode(3);
    graph1.InsertNode(7);
    graph1.InsertEdge(3, 3, "lol");
    graph1.InsertEdge(7, 7, "nooo");
    graph1.InsertEdge(7, 7, "hey");
    graph1.InsertEdge(7, 7, "nood");
    std::cout << graph1 << "\n";
    
    //graph.DeleteNode("bye");
    
    //std::cout << "=====================\n";
    //std::cout << graph << "\n";

    //gdwg::Graph<std::string, int> res;
    //res.InsertNode("hi");
    //REQUIRE(graph == res);
   
  

}
