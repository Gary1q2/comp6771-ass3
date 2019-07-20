#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <memory>
#include <set>
#include <vector>
#include <unordered_map>

namespace gdwg {
using std::shared_ptr;
using std::weak_ptr;

template <typename N, typename E>
class Graph {
 public:
  class const_iterator {};
  
  //============================================================
  // Constructors
  //============================================================
  
  // Default constructor
  Graph() = default;
  
  // Constructor taking in iterators of a vector
  Graph(typename std::vector<N>::const_iterator start, typename std::vector<N>::const_iterator end);
  
  // Constructor taking in a vector of tuples
  Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator, typename std::vector<std::tuple<N, N, E>>::const_iterator);
  
  // Constructor taking in initializer list
  Graph(std::initializer_list<N> list);
  
  // Copy constructor
  Graph(const Graph<N, E>& graph);
  
  // Move constructor
  Graph(Graph<N, E>&& graph);
  
  // Destructor
  ~Graph() = default;
  
  
  
  
  
  //============================================================
  // Operations
  //============================================================
  
  
  
  
  //============================================================
  // Methods
  //============================================================
  
  // Adds a node to the graph
  bool InsertNode(const N& val);
  
  // Adds an edge between two nodes
  bool InsertEdge(const N& src, const N& dst, const E& w);
  
  // Checks if node already exists
  bool IsNode(const N& val);
  
  
  
  
  
  
 private:
  
  struct Edge;  // Defining Edge struct here so it can be included in the Node class
  
  // Node class
  struct Node {
    
    // Node constructor
    Node(const N& val): value_{val} {}
    
    // Variables
    N value_;                                // Value of the node
    std::set<shared_ptr<Edge>> in_edges_;    // Edges that go into this node
    std::set<shared_ptr<Edge>> out_edges_;   // Edges that go AWAY from this node
    int in_degree_;                          // Number of edges going in
    int out_degree_;                         // Number of edges going out
  };
  
  
  // Edge class
  struct Edge {
    
    // Edge constructor
    Edge(const N& src, const N& dst, const E& w): src_{src}, dst_{dst}, weight_{w} {}
    
    // Variables
    E weight_;            // Weight of the edge
    weak_ptr<Node> src_;  // Node which the edge is coming from
    weak_ptr<Node> dst_;  // Node which the edge is going to
  };
  
  
  // Map containing all the nodes in the graph
  std::unordered_map<N, shared_ptr<Node>> node_graph_;
};

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
