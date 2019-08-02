/* Constructor that takes in a vector of nodes
 */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator start,
                         typename std::vector<N>::const_iterator end) {
  // Iterate through vector and create new nodes
  for (auto ite = start; ite != end; ite++) {
    InsertNode(*ite);
  }
}

/* Constructor taking in a vector of tuples
 */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator start,
                         typename std::vector<std::tuple<N, N, E>>::const_iterator end) {
  // Iterate through vector and create new nodes if they don't exist, and then add the edges
  for (auto ite = start; ite != end; ite++) {
    if (IsNode(std::get<0>(*ite)) == false) {
      InsertNode(std::get<0>(*ite));
    }
    if (IsNode(std::get<1>(*ite)) == false) {
      InsertNode(std::get<1>(*ite));
    }
    // Insert the edge between the two nodes
    InsertEdge(std::get<0>(*ite), std::get<1>(*ite), std::get<2>(*ite));
  }
}

/* Constructor taking in an initializer list
 */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(std::initializer_list<N> list) {
  // Iterate through list and add the nodes
  for (auto ite = list.begin(); ite != list.end(); ite++) {
    InsertNode(*ite);
  }
}

/* Copy constructor
 */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(const Graph<N, E>& graph) {
  // Add all the nodes from the graph into the newly constructed graph
  for (auto ite = graph.node_graph_.cbegin(); ite != graph.node_graph_.cend(); ite++) {
    InsertNode(ite->first);
  }

  // Iterate through all the edges in all the nodes and add all the edges
  for (auto node_ite = graph.node_graph_.cbegin(); node_ite != graph.node_graph_.cend();
       node_ite++) {
    auto curr_node = node_ite->second;
    for (auto edge_ite = curr_node->in_edges_.cbegin(); edge_ite != curr_node->in_edges_.cend();
         edge_ite++) {
      auto curr_edge = *edge_ite;

      // Convert the edge's weak pointer reference of node into a shared pointer to access the
      // node's value
      std::shared_ptr<Node> src = curr_edge->src_.lock();
      std::shared_ptr<Node> dst = curr_edge->dst_.lock();
      InsertEdge(src->value_, dst->value_, curr_edge->weight_);
    }
  }
}

/* Move constructor
 */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(Graph<N, E>&& graph) {
  // Move the map pointer from graph to the constructed graph
  node_graph_ = std::move(graph.node_graph_);
}

//========================================================================
// Operations
//========================================================================
/**
 * Copy Assignment
 */
template <typename N, typename E>
gdwg::Graph<N, E>& gdwg::Graph<N, E>::operator=(const gdwg::Graph<N, E>& graph) noexcept {
  if (this == &graph) {
    return *this;
  } else {
    this->Clear();

    // Add all the nodes from the graph into the newly constructed graph
    for (auto ite = graph.node_graph_.cbegin(); ite != graph.node_graph_.cend(); ite++) {
      InsertNode(ite->first);
    }

    // Iterate through all the edges in all the nodes and add all the edges
    for (auto node_ite = graph.node_graph_.cbegin(); node_ite != graph.node_graph_.cend();
         node_ite++) {
      auto curr_node = node_ite->second;
      for (auto edge_ite = curr_node->in_edges_.cbegin(); edge_ite != curr_node->in_edges_.cend();
           edge_ite++) {
        auto curr_edge = *edge_ite;

        // Convert the edge's weak pointer reference of node into a shared pointer to access the
        // node's value
        std::shared_ptr<Node> src = curr_edge->src_.lock();
        std::shared_ptr<Node> dst = curr_edge->dst_.lock();
        InsertEdge(src->value_, dst->value_, curr_edge->weight_);
      }
    }

    return *this;
  }
}

/**
 * Move Assignment
 */
template <typename N, typename E>
gdwg::Graph<N, E>& gdwg::Graph<N, E>::operator=(gdwg::Graph<N, E>&& graph) noexcept {
  if (this == &graph) {
    return *this;
  } else {
    this->Clear();

    // Move the map pointer from graph to the constructed graph
    this->node_graph_ = std::move(graph.node_graph_);
  }

  return *this;
}

//========================================================================
//                                Methods
//========================================================================

/* Inserts a new node into the graph if it doesn't already exist
 */
template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertNode(const N& val) noexcept {
  // Check if node with same value already exists
  if (IsNode(val)) {
    return false;
  }

  // Create new node and insert into graph
  node_graph_.insert({val, std::make_shared<Node>(val)});
  return true;
}

/* Inserts an edge between two nodes in the graph
 */
template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertEdge(const N& src, const N& dst, const E& w) {
  // Throw exception if source or destination node don't exist
  if (!IsNode(src) || !IsNode(dst)) {
    throw std::runtime_error(
        "Cannot call Graph::InsertEdge when either src or dst node does not exist");
  }

  // Check if edge already exists
  std::shared_ptr<Edge> existing_edge = node_graph_[src]->GetEdgeDst(dst, w);
  if (existing_edge != nullptr) {
    return false;
  }

  // Create and insert edge into graph
  std::shared_ptr<Edge> edge = std::make_shared<Edge>(node_graph_[src], node_graph_[dst], w);
  node_graph_[src]->out_edges_.insert(edge);
  node_graph_[dst]->in_edges_.insert(edge);
  return true;
}
/**
 *Deletes a given node and all its associated incoming and outgoing edges. This function does
 *nothing if the node that is to be deleted does not exist in the graph. Hint: if you are using weak
 *ptrs for edges you may be able to do this quite simply. This function returns an boolean as to
 *whether the item has been removed or not (true if removed).
 */
template <typename N, typename E>
bool gdwg::Graph<N, E>::DeleteNode(const N& my_node) noexcept {
  if (!IsNode(my_node)) {
    return false;
  }

  std::map<N, std::shared_ptr<Node>> all_nodes = this->node_graph_;
  try {
    std::shared_ptr<Node> curr_Node = all_nodes.at(my_node);

    // iterate through in edge and delete the edge
    for (auto curr_edge : curr_Node->in_edges_) {
      try {
        std::shared_ptr<Node> src_Node = curr_edge->src_.lock();
        std::shared_ptr<Node> dst_Node = curr_edge->dst_.lock();
        // Check if the edge connect to correct corect node

        if (!IsNode(src_Node->value_) || !IsNode(dst_Node->value_)) {
          continue;
        } else {
          if (dst_Node == curr_Node) {
            if (src_Node->out_edges_.count(curr_edge) != 0)
              src_Node->out_edges_.erase(curr_edge);
            // if (dst_Node->in_edges_.count(curr_edge) != 0)
            // dst_Node->in_edges_.erase(curr_edge);
          }
        }
      } catch (std::bad_weak_ptr& b) {
        std::cout << "BAD weak_ptr \n ";
      }
    }
    // iterate through out edge and delete the edge

    for (auto curr_edge : curr_Node->out_edges_) {
      try {
        std::shared_ptr<Node> src_Node = curr_edge->src_.lock();
        std::shared_ptr<Node> dst_Node = curr_edge->dst_.lock();
        // Check if the edge connect to correct corect node
        if (!IsNode(src_Node->value_) || !IsNode(dst_Node->value_)) {
          continue;
        } else {
          if (src_Node == curr_Node) {
            if (dst_Node->in_edges_.count(curr_edge) != 0)
              dst_Node->in_edges_.erase(curr_edge);
            // if (src_Node->out_edges_.count(curr_edge) != 0)
            // src_Node->out_edges_.erase(curr_edge);
          }
        }
      } catch (std::bad_weak_ptr& b) {
        std::cout << "BAD weak_ptr \n ";
      }
    }
  } catch (const std::out_of_range& e) {
    std::cout << "Exception at " << e.what() << std::endl;
  }
  this->node_graph_.erase(my_node);
  return true;
}

/**
 * Replaces the original data, oldData, stored at this particular node by the replacement data,
 * newData. This function returns false if a node that contains value newData already exists in the
 * graph (with the graph unchanged) and true otherwise.
 */
template <typename N, typename E>
bool gdwg::Graph<N, E>::Replace(const N& oldData, const N& newData) {
  if (!IsNode(oldData)) {
    throw std::runtime_error("Cannot call Graph::Replace on a node that doesn't exist");
  }
  if (IsNode(newData)) {
    return false;
  }

  auto nodeHandler = this->node_graph_.extract(oldData);
  nodeHandler.key() = newData;
  this->node_graph_.insert(std::move(nodeHandler));
  this->node_graph_[newData]->value_ = newData;

  return true;
}

/**
 * All instances of node oldData in the graph are replaced with instances of newData. After
 * completing, every incoming and outgoing edge of oldData becomes an incoming/ougoing edge of
 * newData, except that duplicate edges must be removed. Examples at the bottom of the table.
 */
template <typename N, typename E>
void gdwg::Graph<N, E>::MergeReplace(const N& oldData, const N& newData) {
  if (!IsNode(oldData) || !IsNode(newData)) {
    throw std::runtime_error(
        "Cannot call Graph::MergeReplace on old or new data if they don't exist in the graph");
  }
  // if old and new are same, do nothing
  if (oldData == newData)
    return;

  // Get the node
  std::shared_ptr<Node> curr_node = this->node_graph_.at(oldData);
  // store edges info of oldData Node
  std::unordered_multimap<N, E> in_edge_list;
  for (std::shared_ptr<Edge> item : curr_node->in_edges_) {
    std::shared_ptr<Node> tmp_node = item->src_.lock();
    in_edge_list.insert(std::pair<N, E>{tmp_node->value_, item->weight_});
  }
  std::unordered_multimap<N, E> out_edge_list;
  for (std::shared_ptr<Edge> item2 : curr_node->out_edges_) {
    std::shared_ptr<Node> tmp_node = item2->dst_.lock();
    out_edge_list.insert(std::pair<N, E>{tmp_node->value_, item2->weight_});
  }

  // delete the node
  this->DeleteNode(oldData);
  // restore the data
  this->InsertNode(newData);
  for (std::pair<N, E> dst : out_edge_list) {
    if (dst.first == oldData) {
      this->InsertEdge(newData, newData, dst.second);
    } else {
      this->InsertEdge(newData, dst.first, dst.second);
    }
  }
  for (std::pair<N, E> src : in_edge_list) {
    if (src.first == oldData) {
      this->InsertEdge(newData, newData, src.second);
    } else {
      this->InsertEdge(src.first, newData, src.second);
    }
  }
}

/* Removes all nodes and edges from the graph
 */
template <typename N, typename E>
void gdwg::Graph<N, E>::Clear() noexcept {
  this->node_graph_.clear();
}

/* Checks if a node with the same value already exists in the graph or not
 */
template <typename N, typename E>
bool gdwg::Graph<N, E>::IsNode(const N& val) const noexcept {
  // Search if a node with val already exists
  auto ite = node_graph_.find(val);
  if (ite == node_graph_.end()) {
    return false;
  }
  return true;
}

/* Checks if src and dst nodes are connected
 */
template <typename N, typename E>
bool gdwg::Graph<N, E>::IsConnected(const N& src, const N& dst) const {
  // Throw exception if source or destination node don't exist
  if (!IsNode(src) || !IsNode(dst)) {
    throw std::runtime_error(
        "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
  }
  // Iterate through the src node's in_edge_ array to look for an edge to dst node
  auto in_edge_array = node_graph_.at(src)->in_edges_;
  for (auto ite = in_edge_array.cbegin(); ite != in_edge_array.cend(); ite++) {
    auto edge = *ite;

    // An edge is found so return true
    if (edge->GetSrcValue() == dst) {
      return true;
    }
  }
  // Iterate through the src node's out_edge_ array to look for an edge to dst node
  auto out_edge_array = node_graph_.at(src)->out_edges_;
  for (auto ite = out_edge_array.cbegin(); ite != out_edge_array.cend(); ite++) {
    auto edge = *ite;

    // An edge is found so return true
    if (edge->GetDstValue() == dst) {
      return true;
    }
  }

  return false;
}

/* Returns a vector of all nodes in the graph (sorted by increasing order of node)
 */
template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetNodes() const noexcept {
  // Iterate through map containing all the node values and append to a vector
  std::vector<N> result;
  for (auto ite = node_graph_.cbegin(); ite != node_graph_.cend(); ite++) {
    result.insert(result.begin(), ite->first);
  }

  // Sort and return the vector
  sort(result.begin(), result.end());
  return result;
}

/* Returns a vector of nodes connected to the src node (sorted by increasing order of node)
 */
template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetConnected(const N& src) const {
  // Throw exception if source node doesn't exist
  if (!IsNode(src)) {
    throw std::out_of_range("Cannot call Graph::GetConnected if src doesn't exist in the graph");
  }

  std::set<N> result_set;

  // Iterate through each outward edge on source node and append the destination node
  for (auto ite = node_graph_.at(src)->out_edges_.cbegin();
       ite != node_graph_.at(src)->out_edges_.cend(); ite++) {
    auto edge = *ite;
    result_set.insert(edge->GetDstValue());
  }

  // Convert the set into a vector and then sort it
  std::vector<N> result_vec{result_set.begin(), result_set.end()};
  sort(result_vec.begin(), result_vec.end());

  return result_vec;
}

/* Returns a vector of the weights of edges between two nodes (sorted by increasing order of edge)
 */
template <typename N, typename E>
std::vector<E> gdwg::Graph<N, E>::GetWeights(const N& src, const N& dst) const {
  // Throw exception if source or destination node don't exist
  if (!IsNode(src) || !IsNode(dst)) {
    throw std::out_of_range(
        "Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
  }

  std::vector<E> result_vec;

  // Iterate through source node's out_edge_ array and look for edges that connect to dst node
  for (auto ite = node_graph_.at(src)->out_edges_.cbegin();
       ite != node_graph_.at(src)->out_edges_.cend(); ite++) {
    auto edge = *ite;

    // Edge connects to dst node so append it to the set
    if (edge->GetDstValue() == dst) {
      result_vec.insert(result_vec.begin(), edge->weight_);
    }
  }

  // Sort vector and then return
  sort(result_vec.begin(), result_vec.end());
  return result_vec;
}
