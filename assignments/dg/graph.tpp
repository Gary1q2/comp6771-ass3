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
    for (auto node_ite = graph.node_graph_.cbegin(); node_ite != graph.node_graph_.cend(); node_ite++) {
        auto curr_node = node_ite->second;
        for (auto edge_ite = curr_node->in_edges_.cbegin(); edge_ite != curr_node->in_edges_.cend(); edge_ite++) {
            auto curr_edge = *edge_ite;
            
            // Convert the edge's weak pointer reference of node into a shared pointer to access the node's value
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

//========================================================================
// Methods
//========================================================================

/* Inserts a new node into the graph if it doesn't already exist
 */
template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertNode(const N& val) {
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

/* Removes all nodes and edges from the graph
 */
template <typename N, typename E>
void gdwg::Graph<N, E>::Clear() {
  node_graph_.clear();
}

/* Checks if a node with the same value already exists in the graph or not
 */
template <typename N, typename E>
bool gdwg::Graph<N, E>::IsNode(const N& val) {

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
bool gdwg::Graph<N, E>::IsConnected(const N& src, const N& dst) {

  // Throw exception if source or destination node don't exist
  if (!IsNode(src) || !IsNode(dst)) {
    throw std::runtime_error(
        "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
  }

  // Iterate through the src node's in_edge_ array to look for an edge to dst node
  auto in_edge_array = node_graph_[src]->in_edges_;
  for (auto ite = in_edge_array.cbegin(); ite != in_edge_array.cend(); ite++) {
    auto edge = *ite;

    // An edge is found so return true
    if (edge->GetSrcValue() == dst) {
      return true;
    }
  }

  // Iterate through the src node's out_edge_ array to look for an edge to dst node
  auto out_edge_array = node_graph_[src]->out_edges_;
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
std::vector<N> gdwg::Graph<N, E>::GetNodes() {

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
std::vector<N> gdwg::Graph<N, E>::GetConnected(const N& src) {

  // Throw exception if source node doesn't exist
  if (!IsNode(src)) {
    throw std::out_of_range("Cannot call Graph::GetConnected if src doesn't exist in the graph");
  }

  // Iterate through each inward edge on source node and append the other connected node
  std::unordered_set<N> result_set;
  for (auto ite = node_graph_[src]->in_edges_.cbegin(); ite != node_graph_[src]->in_edges_.cend();
       ite++) {
    auto edge = *ite;
    result_set.insert(edge->GetSrcValue());
  }

  // Iterate through each outward edge on source node and append the destination node
  for (auto ite = node_graph_[src]->out_edges_.cbegin(); ite != node_graph_[src]->out_edges_.cend();
       ite++) {
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
std::vector<E> gdwg::Graph<N, E>::GetWeights(const N& src, const N& dst) {
    
    // Throw exception if source or destination node don't exist
    if (!IsNode(src) || !IsNode(dst)) {
        throw std::out_of_range(
            "Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
    }
    
    // Iterate through source node's in_edge_ array and look for edges that connect to dst node
    std::vector <E> result_vec;
    for (auto ite = node_graph_[src]->in_edges_.cbegin(); ite != node_graph_[src]->in_edges_.cend();
         ite++) {
        auto edge = *ite;
        
        // Edge connects to dst node so append it to the set
        if (edge->GetSrcValue() == dst) {
            result_vec.insert(result_vec.begin(), edge->weight_);
        }
    }
    
    // Iterate through source node's out_edge_ array and look for edges that connect to dst node
    for (auto ite = node_graph_[src]->out_edges_.cbegin(); ite != node_graph_[src]->out_edges_.cend(); ite++) {
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