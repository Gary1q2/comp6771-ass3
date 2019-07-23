#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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
  Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator,
        typename std::vector<std::tuple<N, N, E>>::const_iterator);

  // Constructor taking in initializer list
  Graph(std::initializer_list<N> list);

  // Copy constructor
  // Graph(const Graph<N, E>& graph);

  // Move constructor
  // Graph(Graph<N, E>&& graph);

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
  
  // Checks if src and dst nodes are connected
  bool IsConnected(const N& src, const N& dst);
  
  // Returns a vector all nodes in the graph (sorted by increasing order of node)
  std::vector<N> GetNodes();
  
  // Returns a vector of nodes connected to the src node (sorted by increasing order of node)
  std::vector<N> GetConnected(const N& src);
  
  // Returns a vector of the weights of edges between two nodes (sorted by increasing order of edge)
  std::vector<E> GetWeights(const N& src, const N& dst);

  
  //============================================================
  // Friends
  //============================================================

  // Operator overwrite to print out the stream
  friend std::ostream& operator<<(std::ostream& out_stream,
                                  const gdwg::Graph<N, E>& curr_graph) noexcept {

    std::unordered_map<N, shared_ptr<Node>> all_nodes = curr_graph.Get_all_nodes();

    for (std::pair<N, shared_ptr<Node>> element : all_nodes) {
      out_stream << element.first << "(";
      out_stream << element.second->in_edges_.size() << "\n";
    }
    out_stream << "Hi\n";
    return out_stream;
  }

  // Compares if two graphs are the same or not
  friend bool operator==(const gdwg::Graph<N, E>& graph1, const gdwg::Graph<N, E>& graph2) {

    // Check if maps are the same size
    if (graph1.node_graph_.size() != graph2.node_graph_.size()) {
      return false;
    }

    // Iterate through graph1's nodes and compare their name values with graph2's nodes
    for (auto g1_node_ite = graph1.node_graph_.cbegin(); g1_node_ite != graph1.node_graph_.cend();
         g1_node_ite++) {

      // Try and find a node in graph2 with the same name value
      auto g2_node_ite = graph2.node_graph_.find(g1_node_ite->first);

      // Same node didn't exist in graph2, so return false
      if (g2_node_ite == graph2.node_graph_.end()) {
        return false;
      }

      // Iterate through the edges in the node of graph1 and compare it with the node of graph2
      auto g1_node = g1_node_ite->second;
      auto g2_node = g2_node_ite->second;

      // Check if the node's inward edge array has the same size
      if (g1_node->in_edges_.size() != g2_node->in_edges_.size()) {
        return false;
      }

      // Check if the node's outward edge array has the same size
      if (g1_node->out_edges_.size() != g2_node->out_edges_.size()) {
        return false;
      }

      // Check if all the inward edge's within node1 and node2 have the same values
      for (auto g1_edge_ite = g1_node->in_edges_.cbegin(); g1_edge_ite != g1_node->in_edges_.cend();
           g1_edge_ite++) {
        bool found = false;
        auto edge1 = *g1_edge_ite;

        // Search within node2 for an edge that matches node1 (edge might not be in the same order
        // in the set)
        for (auto g2_edge_ite = g2_node->in_edges_.cbegin();
             g2_edge_ite != g2_node->in_edges_.cend(); g2_edge_ite++) {
          auto edge2 = *g2_edge_ite;
          if ((edge1->GetSrcValue() == edge2->GetSrcValue()) &&
              (edge1->GetDstValue() == edge2->GetDstValue()) &&
              (edge1->weight_ == edge2->weight_)) {
            found = true;
            break;
          }
        }

        // An edge in node1 was not found in node2 so return false
        if (!found) {
          ;
          return false;
        }
      }

      // Check if all the outward edge's within node1 and node2 have the same values
      for (auto g1_edge_ite = g1_node->out_edges_.cbegin();
           g1_edge_ite != g1_node->out_edges_.cend(); g1_edge_ite++) {
        bool found = false;
        auto edge1 = *g1_edge_ite;

        // Search within node2 for an edge that matches node1 (edge might not be in the same order
        // in the set)
        for (auto g2_edge_ite = g2_node->out_edges_.cbegin();
             g2_edge_ite != g2_node->out_edges_.cend(); g2_edge_ite++) {
          auto edge2 = *g2_edge_ite;
          if ((edge1->GetSrcValue() == edge2->GetSrcValue()) &&
              (edge1->GetDstValue() == edge2->GetDstValue()) &&
              (edge1->weight_ == edge2->weight_)) {
            found = true;
            break;
          }
        }

        // An edge in node1 was not found in node2 so return false
        if (!found) {
          return false;
        }
      }
    }
    return true;
  }

 private:
  struct Edge;  // Defining Edge struct here so it can be included in the Node class

  // Node class
  struct Node {

    // Node constructor
    Node(const N& val) : value_{val} {}

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
    N value_;                                          // Value of the node
    std::unordered_set<shared_ptr<Edge>> in_edges_;    // Edges that go into this node
    std::unordered_set<shared_ptr<Edge>> out_edges_;   // Edges that go AWAY from this node
  };

  // Edge class
  struct Edge {

    // Edge constructor
    Edge(shared_ptr<Node> src, shared_ptr<Node> dst, const E& w)
      : src_{src}, dst_{dst}, weight_{w} {}

    // Return the source node's value
    N GetSrcValue() const {
      std::shared_ptr<Node> p = src_.lock();
      return p->value_;
    }

    // Return the destination node's value
    N GetDstValue() const {
      std::shared_ptr<Node> p = dst_.lock();
      return p->value_;
    }

    // Variables
    weak_ptr<Node> src_;  // Node which the edge is coming from
    weak_ptr<Node> dst_;  // Node which the edge is going to
    E weight_;            // Weight of the edge
  };

  // Map containing all the nodes in the graph
  std::unordered_map<N, shared_ptr<Node>> node_graph_;

  //============================================================
  // Helper function
  //============================================================
  std::unordered_map<N, shared_ptr<Node>> Get_all_nodes() const noexcept {
    return this->node_graph_;
  }
};

}  // namespace gdwg

// Change this back to absolute path, only for IDE
//#include "assignments/dg/graph.tpp"
#include "graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
