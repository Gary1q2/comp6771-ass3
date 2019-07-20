

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
    for (auto const ite = start; ite != end; ite++) {
        if (IsNode(std::get<0>(*ite)) == false) {
            InsertNode(std::get<0>(*ite));
        }
        if (IsNode(std::get<1>(*ite)) == false) {
            InsertNode(std::get<1>(*ite));
        }
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
//gdwg::Graph<N, E>::Graph(const Graph<N, E>& graph): node_graph_{graph.node_graph_} {}













/* Inserts a new node into the graph if it doesn't already exist
 */
template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertNode(const N& val) {
    if (IsNode(val)) {
      return false;
    }
    node_graph_.insert({val, std::make_shared<Node>(val)});
    return true;
}


/* Inserts an edge between two nodes in the graph
 */
//template <typename N, typename E>
//bool InsertEdge(const N& src, const N& dst, const E& w) {
    //
//}


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