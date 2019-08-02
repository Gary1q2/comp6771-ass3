#include <iostream>
#include <string>
#include <map>

// Change this back to absolute path, only for IDE
//#include "assignments/dg/graph.h"
#include "graph.h"

int main(){
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
    
   for (auto omg = g.crbegin(); omg != g.crend(); omg++) {
        std::cout << std::get<0>(*omg) << "-" << std::get<1>(*omg) << "-" << std::get<2>(*omg) << "\n";
    }
    
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
/*

    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("A");
    graph.InsertNode("B");
    graph.InsertNode("C");
    graph.InsertNode("D");
    graph.InsertEdge("A", "B", 1);
    graph.InsertEdge("A", "D", 3);
    graph.InsertEdge("A", "C", 2);

    std::cout<< graph;
    std::cout<< "\n\n\n=============================Replace=============================\n\n\n";
    graph.MergeReplace("A","B");
    std::cout<< graph;
*/
/*
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("A");
    graph.InsertNode("B");
    graph.InsertNode("C");
    graph.InsertNode("D");
    graph.InsertEdge("A", "B", 3);
    graph.InsertEdge("C", "B", 2);
    graph.InsertEdge("D", "B", 4);

    std::cout<< graph;
    std::cout<< "\n\n\n=============================Replace=============================\n\n\n";
    graph.MergeReplace("A","B");
    std::cout<< graph;

*/
/*
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertEdge("hi", "bye", 1);
    graph.InsertEdge("hi", "bye", 2);
    graph.InsertEdge("bye", "hi", 3);
    graph.InsertEdge("bye", "hi", 4);
    graph.InsertEdge("bye", "bye", 200);
    graph.InsertEdge("bye", "bye", 300);
    graph.InsertEdge("hi", "hi", 100);
    graph.InsertEdge("hi", "hi", 400);
    gdwg::Graph<std::string, int> res1 = graph;

    graph.MergeReplace("hi", "hi");

    std::cout<< graph;
    std::cout<< "\n\n\n=============================Replace=============================\n\n\n";
    graph.MergeReplace("bye", "hi");
    std::cout<< graph;
    graph.Replace("hi", "bye");
    std::cout<< graph;

*/




}
