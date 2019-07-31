#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

namespace gdwg {
template <typename N, typename E>
class Graph {
 private:
  
  struct Edge;
  
  // Functor to compare two edges
  struct edge_compare {
    bool operator() (const std::shared_ptr<Edge> edge1, const std::shared_ptr<Edge> edge2) const {
      
      // Compare the source nodes
      std::shared_ptr<Node> edge1_src = edge1->src_.lock();
      std::shared_ptr<Node> edge2_src = edge2->src_.lock();
      if (edge1_src->value_ != edge2_src->value_) {
        return (edge1_src->value_ < edge2_src->value_);
        
      // Compare the destination nodes
      } else {
        std::shared_ptr<Node> edge1_dst = edge1->dst_.lock();
        std::shared_ptr<Node> edge2_dst = edge2->dst_.lock();
        if (edge1_dst->value_ != edge2_dst->value_) {
          return (edge1_dst->value_ < edge2_dst->value_);
          
        // Compares the edge weights
        } else {
          return (edge1->weight_ < edge2->weight_);
        }
      }
    }
  };
  
  // Node class
  struct Node {

    // Node constructor
    Node(const N& val) : value_{val} {}

    // Checks if a given edge (destination and weight) exists from this node
    std::shared_ptr<Edge> GetEdgeDst(const N& dst, const E& w) const noexcept {
      for (const auto& edge : out_edges_) {
        std::shared_ptr<Node> dest_node = edge->dst_.lock();
        if ((dst == dest_node->value_) && (edge->weight_ == w)) {
          return edge;
        }
      }
      return nullptr;
    }
    void change_value(const N& v) noexcept { value_ = v; }

    // Variables
    N value_;                                                  // Value of the node
    std::set<std::shared_ptr<Edge>, edge_compare> in_edges_;   // Edges that go into this node
    std::set<std::shared_ptr<Edge>, edge_compare> out_edges_;  // Edges that go AWAY from this node
  };

  // Edge class
  struct Edge {

    // Edge constructor
    Edge(std::shared_ptr<Node> src, std::shared_ptr<Node> dst, const E& w)
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
    std::weak_ptr<Node> src_;  // Node which the edge is coming from
    std::weak_ptr<Node> dst_;  // Node which the edge is going to
    E weight_;                 // Weight of the edge
  };

  // Map containing all the nodes in the graph
  std::map<N, std::shared_ptr<Node>> node_graph_;
  
  
  
 public:
  
  class const_iterator {
   
   public:
    
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::tuple<N, N, E>;
    using reference = std::tuple<const N&, const N&, const E&>;
    
    // De-referencing iterator
    reference operator*() const {
        auto curr_edge = *edge_ite_;
        auto node_src = curr_edge->src_.lock();
        auto node_dst = curr_edge->dst_.lock();
        return {node_src->value_, node_dst->value_, curr_edge->weight_};
    }
    
    // Pre-increment
    const_iterator operator++() {
        ++edge_ite_;
        if (edge_ite_ == node_ite_->second->out_edges_.end()) {
          
          // Iterate to next node while skipping nodes with no edges and not reaching the end
          do {
            node_ite_++;
          } while (node_ite_ != sentinel_ && node_ite_->second->out_edges_.begin() == node_ite_->second->out_edges_.end());
          if (node_ite_ != sentinel_) {
            edge_ite_ = node_ite_->second->out_edges_.begin();
          }
        }
        return *this;
    }
    
    // Post-increment
    const_iterator operator++(int) {
        auto copy{*this};
        ++(*this);
        return copy;
    }
    /*
    // Pre-decrement
    const_iterator operator--() {
    
    }
    
    // Post-decrement
    const_iterator operator--(int) {
        auto copy{*this};
        --(*this);
        return copy;
    }
    */
    
    // == operator
    friend bool operator==(const const_iterator& edge1, const const_iterator& edge2) {
        reference tup1 = *edge1;
        reference tup2 = *edge2;
        if (tup1 == tup2) {
            return true;
        } else {
            return false;
        }
    }
    
    
    // != operator
    friend bool operator!=(const const_iterator& edge1, const const_iterator& edge2) {
        reference tup1 = *edge1;
        reference tup2 = *edge2;
        if (tup1 == tup2) {
            return false;
        } else {
            return true;
        }
    }
    
   private:
    
    typename std::map<N, std::shared_ptr<Node>>::iterator node_ite_;
    const typename std::map<N, std::shared_ptr<Node>>::iterator sentinel_;
    typename std::set<std::shared_ptr<Edge>>::iterator edge_ite_;
    
    
    // Iterator constructor
    const_iterator(const decltype(node_ite_)& node_ite,
                   const decltype(sentinel_)& sentinel,
                   const decltype(edge_ite_)& edge_ite): node_ite_{node_ite}, sentinel_{sentinel}, edge_ite_{edge_ite} {}
    
                   
    friend class Graph;
  };
  
  using iterator = const_iterator;
  
  // Return an iterator to the beginning of the graph
  iterator begin() {
      
      // Look for first node
      auto node_ite = node_graph_.begin();
      if (node_ite == node_graph_.end()) {
        return end();
      }
  
      // Look for first edge
      auto edge_ite = node_ite->second->out_edges_.begin();
      if (edge_ite == node_ite->second->out_edges_.end()) {
        return end();
      }
    
      // Return starting iterator
      return {node_ite, node_graph_.end(), edge_ite};
  }

  // Return an iterator to the end of the graph
  iterator end() {
      return { node_graph_.end(), node_graph_.end(), {}};
  }
  
  
  
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
  Graph(const Graph<N, E>& graph);

  // Move constructor
  Graph(Graph<N, E>&& graph);

  // Destructor
  ~Graph() = default;

  //============================================================
  // Operations
  //============================================================
  
  // Copy assignment
  Graph<N, E>& operator=(const Graph<N, E>& orig) noexcept;
  
  // Move assignment
  Graph<N, E>& operator=(Graph<N, E>&& orig) noexcept;
  
  //============================================================
  // Methods
  //============================================================

  // Adds a node to the graph
  bool InsertNode(const N& val) noexcept;

  // Adds an edge between two nodes
  bool InsertEdge(const N& src, const N& dst, const E& w);

  // Delete a Node from a graph
  bool DeleteNode(const N& my_node) noexcept;

  // Replace the data in the graph
  bool Replace(const N& oldData, const N& newData);

  // Replace and merge the data in the graph
  void MergeReplace(const N& oldData, const N& newData);

  // Removes all nodes and edges from the graph
  void Clear() noexcept;

  // Checks if node already exists
  bool IsNode(const N& val) const noexcept;

  // Checks if src and dst nodes are connected
  bool IsConnected(const N& src, const N& dst) const;

  // Returns a vector all nodes in the graph (sorted by increasing order of node)
  std::vector<N> GetNodes() const noexcept;

  // Returns a vector of nodes connected to the src node (sorted by increasing order of node)
  std::vector<N> GetConnected(const N& src) const;

  // Returns a vector of the weights of edges between two nodes (sorted by increasing order of edge)
  std::vector<E> GetWeights(const N& src, const N& dst) const;

  // Returns first edge in the graph (based on iterator order)
  std::shared_ptr<Edge> GetFirstEdge() const noexcept;
  
  
  //============================================================
  // Friends
  //============================================================

  // Operator overwrite to print out the stream
  friend std::ostream& operator<<(std::ostream& out_stream,
                                  const gdwg::Graph<N, E>& curr_graph) noexcept {
      
    // Iterate over nodes
    for (auto element : curr_graph.node_graph_) {
      out_stream << element.first << " (\n";

      // Iterate over outwards edges
      for (auto edge : element.second->out_edges_) {
        try {
          auto dst_node = edge->dst_.lock();
          out_stream << "  " << dst_node->value_ << " | ";
          out_stream << edge->weight_ << "\n";
        } catch (std::bad_weak_ptr& b) {
          out_stream << "BAD weak_ptr \n ";
        }
      }
      out_stream << ")\n";
    }
    return out_stream;
  }

  // Compares if two graphs are the same or not
  friend bool operator==(const gdwg::Graph<N, E>& graph1,
                         const gdwg::Graph<N, E>& graph2) noexcept {

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

  // Compares if two graphs are not the same or are
  friend bool operator!=(const gdwg::Graph<N, E>& graph1,
                         const gdwg::Graph<N, E>& graph2) noexcept {

    // Use the friend operator== and just negate the value
    return !(graph1 == graph2);
  }
};

}  // namespace gdwg

// Change this back to absolute path, only for IDE
//#include "assignments/dg/graph.tpp"
#include "graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
