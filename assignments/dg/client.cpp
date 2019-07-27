#include <iostream>
#include <string>

// Change this back to absolute path, only for IDE
//#include "assignments/dg/graph.h"
#include "graph.h"

// hello i am testing too - gary

// Note: At the moment, there is no client.sampleout. Please do your own testing
// Carter test 1
int main() {

    std::vector<std::string> vec{"hello"};
    gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
    std::cout << graph;
    graph.Replace("hello", "yes");
    std::cout << graph;


}
