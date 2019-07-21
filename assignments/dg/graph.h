#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <algorithm>
#include <iostream>
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
  Graph();
  
  // Constructor taking in iterators of a vector
  Graph(typename std::vector<N>::const_iterator start, typename std::vector<N>::const_iterator end);
  
  // Constructor taking in a vector of tuples
  Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator, typename std::vector<std::tuple<N, N, E>>::const_iterator);
  
  // Constructor taking in initializer list
  Graph(std::initializer_list<N> list);
  
  // Copy constructor
  //Graph(const Graph<N, E>& graph);
  
  // Move constructor
  //Graph(Graph<N, E>&& graph);
  
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
  
  // Removes all nodes and edges from the graph
  void Clear();
  
  // Checks if node already exists
  bool IsNode(const N& val);
  
  //============================================================
  // Friends
  //============================================================
  
  // Compares if two graphs are the same or not
  friend bool operator==(const gdwg::Graph<N, E>& graph1, const gdwg::Graph<N, E>& graph2) {
      
      // Check if maps are the same size
      if (graph1.node_graph_ != graph2.node_graph_) {
          return false;
      }
    
      // Check if each node is the same
      for (const auto& node : graph1.node_graph_) {
          if (node.second != graph2[node.first]) {
              return false;
          }
    
          // Check if each node's inward edges are the same
          if (node->in_edges_ != graph2[node.first]) {
              return false;
          }
          
          // Check if each node's inward edges are the same
          if (node->out_edges_ != graph2[node.first]) {
              return false;
          }
          
      }
      return true;
  }
  
 private:
  
  struct Edge;  // Defining Edge struct here so it can be included in the Node class
  
  // Node class
  struct Node {
    
    // Node constructor
    Node(const N& val): value_{val} {}
    
    // Checks if a given edge (destination and weight) exists from this node
    std::shared_ptr<Edge> GetEdgeDst(const N& dst, const E& w) {
        for (const auto& edge : out_edges_) {
            std::shared_ptr<Node> dest_node = edge->dst_.lock();
            if ((dst == dest_node->value_) && (edge->weight_ == w)) {
                return edge;
            }
        }
        return nullptr;
    }
    
    // Variables
    N value_;                                // Value of the node
    std::set<shared_ptr<Edge>> in_edges_;    // Edges that go into this node
    std::set<shared_ptr<Edge>> out_edges_;   // Edges that go AWAY from this node
    
    
  };

  
  // Edge class
  struct Edge {
    
    // Edge constructor
    Edge(shared_ptr<Node> src, shared_ptr<Node> dst, const E& w): src_{src}, dst_{dst}, weight_{w} {}
    
    // Variables
    weak_ptr<Node> src_;  // Node which the edge is coming from
    weak_ptr<Node> dst_;  // Node which the edge is going to
    E weight_;            // Weight of the edge
  };
  
  
  // Map containing all the nodes in the graph
  std::unordered_map<N, shared_ptr<Node>> node_graph_;
};

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
