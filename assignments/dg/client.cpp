#include <iostream>
#include <string>
#include <map>

// Change this back to absolute path, only for IDE
//#include "assignments/dg/graph.h"
#include "graph.h"

// hello i am testing too - gary

// Note: At the moment, there is no client.sampleout. Please do your own testing
// Carter test 1
int main(){
/*
    gdwg::Graph<int, int> g;
    g.InsertNode(1);
    g.InsertNode(2);
    g.InsertNode(3);
    g.InsertNode(4);
    g.InsertNode(5);
    g.InsertNode(6);
    g.InsertNode(7);

    g.InsertEdge(1, 5, -1);
    g.InsertEdge(2, 1, 1);
    g.InsertEdge(2, 4, 2);
    g.InsertEdge(2, 4, -2);
    g.InsertEdge(2, 2, -20);
    g.InsertEdge(4, 4, -2);
    g.InsertEdge(2, 4, -3);
    g.InsertEdge(3, 6, -8);
    g.InsertEdge(3, 2, 2);
    g.InsertEdge(4, 1, -4);
    g.InsertEdge(4, 5, 3);
    g.InsertEdge(5, 2, 7);
    g.InsertEdge(6, 2, 5);
    g.InsertEdge(6, 3, 10);
    std::cout<< g;
    std::cout<< "\n\n\n=============================Replace=============================\n\n\n";
    g.Replace(2,10);
    std::cout<< g;

*/


    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertEdge("hi", "bye", 3);
    graph.InsertEdge("hi", "bye", 2);
    graph.InsertEdge("bye", "hi", 3);
    graph.InsertEdge("bye", "hi", 2);
    graph.InsertEdge("bye", "bye", 200);
    graph.InsertEdge("hi", "hi", 100);
    gdwg::Graph<std::string, int> res1=graph;
    graph.Replace("hi","hi");



    std::cout<< graph;
    std::cout<< "\n\n\n=============================Replace=============================\n\n\n";
    graph.Replace("bye","yes");
    std::cout<< graph;

}
