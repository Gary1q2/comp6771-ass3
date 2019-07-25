/*

  == Explanation and rational of testing ==

   For each constructor, operation and method we thought of all
   the possible edge cases and wrote edge case tests to ensure our methods would
   pass them. Along with our edge case tests we added 1-2 normal cases
   to make sure our methods would function normally.

   We are certain we have covered most if not all the possibilities because
   we have spent time ensuring no edge case is left uncovered.


*/

// Change this back to absolute path, only for IDE
//#include "assignments/dg/graph.h"
#include "catch.h"
#include "graph.h"
#include <sstream>

//============================================================
// Constructors
//============================================================
SCENARIO("Testing default constructor") {
  GIVEN("A constructed graph") {
    gdwg::Graph<std::string, int> graph;
    WHEN("Checked with another graph that was default constructed") {
      gdwg::Graph<std::string, int> res;
      THEN("Graphs are equal") { REQUIRE((graph == res) == true); }
    }
  }
}

SCENARIO("Testing constructor taking in a vector of nodes") {
  GIVEN("A null vector") {
    std::vector<std::string> vec = {};
    WHEN("Constructed") {
      gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
      THEN("Graph has no nodes") {
        gdwg::Graph<std::string, int> res;
        REQUIRE(graph == res);
      }
    }
  }
  GIVEN("A vector of size 1") {
    std::vector<std::string> vec = {"hello"};
    WHEN("Constructed") {
      gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
      THEN("There will be 1 node in graph") {
        gdwg::Graph<std::string, int> res;
        res.InsertNode("hello");
        REQUIRE(graph == res);
      }
    }
  }
  GIVEN("A vector of size 3") {
    std::vector<std::string> vec = {"hello", "bye", "yo"};
    WHEN("Constructed") {
      gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
      THEN("There will be 3 node in graph") {
        gdwg::Graph<std::string, int> res;
        res.InsertNode("hello");
        res.InsertNode("bye");
        res.InsertNode("yo");
        REQUIRE(graph == res);
      }
    }
  }
  GIVEN("A vector of size 2 with 2 duplicate nodes") {
    std::vector<std::string> vec = {"hi", "hi"};
    WHEN("Constructed") {
      gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
      THEN("There will be 1 node in the graph") {
        gdwg::Graph<std::string, int> res;
        res.InsertNode("hi");
        REQUIRE(graph == res);
      }
    }
  }
}

SCENARIO("Testing constructor taking in a vector of tuples") {
  GIVEN("A vector with no tuples") {
    std::vector<std::tuple<std::string, std::string, int>> vec;
    gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
    THEN("There will be empty graph") {
      gdwg::Graph<std::string, int> res;
      REQUIRE(graph == res);
    }
  }
  GIVEN("A vector with 1 tuple") {
    std::vector<std::tuple<std::string, std::string, int>> vec{std::make_tuple("hi", "bye", 4)};
    gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
    THEN("There will be 1 node in graph") {
      gdwg::Graph<std::string, int> res;
      res.InsertNode("hi");
      res.InsertNode("bye");
      res.InsertEdge("hi", "bye", 4);
      REQUIRE(graph == res);
    }
  }
  GIVEN("A vector with 2 tuples and 4 unique nodes") {
    auto e1 = std::make_tuple("hi", "bye", 3);
    auto e2 = std::make_tuple("lol", "shy", 6);
    std::vector<std::tuple<std::string, std::string, int>> vec{e1, e2};
    gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
    THEN("There will be 4 node in graph + 2 edges") {
      gdwg::Graph<std::string, int> res;
      res.InsertNode("hi");
      res.InsertNode("bye");
      res.InsertNode("lol");
      res.InsertNode("shy");
      res.InsertEdge("hi", "bye", 3);
      res.InsertEdge("lol", "shy", 6);
      REQUIRE(graph == res);
    }
  }
  GIVEN("A vector with 2 tuples where a src node already exists") {
    auto e1 = std::make_tuple("hi", "bye", 3);
    auto e2 = std::make_tuple("bye", "shy", 6);
    std::vector<std::tuple<std::string, std::string, int>> vec{e1, e2};
    gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
    THEN("The existing src node won't be created again") {
      gdwg::Graph<std::string, int> res;
      res.InsertNode("hi");
      res.InsertNode("bye");
      res.InsertNode("shy");
      res.InsertEdge("hi", "bye", 3);
      res.InsertEdge("bye", "shy", 6);
      REQUIRE(graph == res);
    }
  }
  GIVEN("A vector with 2 tuples where a dst node already exists") {
    auto e1 = std::make_tuple("hi", "bye", 3);
    auto e2 = std::make_tuple("shy", "hi", 6);
    std::vector<std::tuple<std::string, std::string, int>> vec{e1, e2};
    gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
    THEN("The existing dst node won't be created again") {
      gdwg::Graph<std::string, int> res;
      res.InsertNode("hi");
      res.InsertNode("bye");
      res.InsertNode("shy");
      res.InsertEdge("hi", "bye", 3);
      res.InsertEdge("shy", "hi", 6);
      REQUIRE(graph == res);
    }
  }
  GIVEN("A vector with 2 tuples where an edge already exists") {
    auto e1 = std::make_tuple("hi", "bye", 3);
    auto e2 = std::make_tuple("hi", "bye", 3);
    std::vector<std::tuple<std::string, std::string, int>> vec{e1, e2};
    gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
    THEN("The existing edge won't be created again") {
      gdwg::Graph<std::string, int> res;
      res.InsertNode("hi");
      res.InsertNode("bye");
      res.InsertEdge("hi", "bye", 3);
      REQUIRE(graph == res);
    }
  }
}

SCENARIO("Testing constructor taking in an initializer list") {
  GIVEN("An empty list") {
    gdwg::Graph<std::string, int> graph{};
    THEN("The graph is empty") {
      gdwg::Graph<std::string, int> res;
      REQUIRE(graph == res);
    }
  }
  GIVEN("A list with 1 node") {
    gdwg::Graph<std::string, int> graph{"hi"};
    THEN("The graph has 1 node") {
      gdwg::Graph<std::string, int> res;
      res.InsertNode("hi");
      REQUIRE(graph == res);
    }
  }
  GIVEN("A list with 3 nodes") {
    gdwg::Graph<std::string, int> graph{"hi", "bye", "lol"};
    THEN("The graph has 3 nodes") {
      gdwg::Graph<std::string, int> res;
      res.InsertNode("hi");
      res.InsertNode("bye");
      res.InsertNode("lol");
      REQUIRE(graph == res);
    }
  }
  GIVEN("A list with 2 duplicate nodes") {
    gdwg::Graph<std::string, int> graph{"hi", "hi"};
    THEN("The graph will only have 1 node") {
      gdwg::Graph<std::string, int> res;
      res.InsertNode("hi");
      REQUIRE(graph == res);
    }
  }
}

SCENARIO("Testing copy constructor") {
  GIVEN("An empty graph") {
    gdwg::Graph<std::string, int> graph;
    WHEN("Copied") {
      gdwg::Graph<std::string, int> copy{graph};
      THEN("We get another empty graph") {
        gdwg::Graph<std::string, int> res;
        REQUIRE(copy == res);
      }
    }
  }
  GIVEN("A graph with 1 node") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    WHEN("Copied") {
      gdwg::Graph<std::string, int> copy{graph};
      THEN("We get a graph with 1 node") {
        gdwg::Graph<std::string, int> res;
        res.InsertNode("hi");
        REQUIRE(copy == res);
      }
    }
  }
  GIVEN("A graph with 3 nodes") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertNode("lol");
    WHEN("Copied") {
      gdwg::Graph<std::string, int> copy{graph};
      THEN("We get a graph with 3 nodes") {
        gdwg::Graph<std::string, int> res;
        res.InsertNode("hi");
        res.InsertNode("bye");
        res.InsertNode("lol");
        REQUIRE(copy == res);
      }
    }
  }
  GIVEN("A graph with 2 nodes and 1 edge") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertEdge("hi", "bye", 3);
    WHEN("Copied") {
      gdwg::Graph<std::string, int> copy{graph};
      THEN("We get a graph with 2 nodes and 1 edge") {
        gdwg::Graph<std::string, int> res;
        res.InsertNode("hi");
        res.InsertNode("bye");
        res.InsertEdge("hi", "bye", 3);
        REQUIRE(copy == res);
      }
    }
  }
  GIVEN("A graph with 2 nodes and 2 edges") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertEdge("hi", "bye", 3);
    graph.InsertEdge("bye", "hi", 3);
    WHEN("Copied") {
      gdwg::Graph<std::string, int> copy{graph};
      THEN("We get a graph with 2 nodes and 2 edges") {
        gdwg::Graph<std::string, int> res;
        res.InsertNode("hi");
        res.InsertNode("bye");
        res.InsertEdge("hi", "bye", 3);
        res.InsertEdge("bye", "hi", 3);
        REQUIRE(copy == res);
      }
    }
  }
  GIVEN("A graph with 2 nodes and 4 edges") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertEdge("hi", "bye", 3);
    graph.InsertEdge("hi", "bye", 2);
    graph.InsertEdge("bye", "hi", 3);
    graph.InsertEdge("bye", "hi", 2);
    WHEN("Copied") {
      gdwg::Graph<std::string, int> copy{graph};
      THEN("We get a graph with 2 nodes and 4 edges") {
        gdwg::Graph<std::string, int> res;
        res.InsertNode("hi");
        res.InsertNode("bye");
        res.InsertEdge("hi", "bye", 3);
        res.InsertEdge("hi", "bye", 2);
        res.InsertEdge("bye", "hi", 3);
        res.InsertEdge("bye", "hi", 2);
        REQUIRE(copy == res);
      }
    }
  }
}

SCENARIO("Testing move constructor") {
  GIVEN("An empty graph") {
    gdwg::Graph<std::string, int> graph;
    WHEN("Moved") {
      gdwg::Graph<std::string, int> move = std::move(graph);
      THEN("Moved graph is empty") {
        gdwg::Graph<std::string, int> res;
        REQUIRE(move == res);
      }
    }
  }
  GIVEN("A graph with 1 node and 1 edge") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertEdge("hi", "hi", 4);
    WHEN("Moved") {
      gdwg::Graph<std::string, int> move = std::move(graph);
      THEN("Moved graph is empty") {
        gdwg::Graph<std::string, int> res;
        res.InsertNode("hi");
        res.InsertEdge("hi", "hi", 4);
        REQUIRE(move == res);
      }
    }
  }
  GIVEN("A graph with 3 node and 5 edges") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertNode("lol");
    graph.InsertEdge("hi", "hi", 4);
    graph.InsertEdge("hi", "hi", 1);
    graph.InsertEdge("hi", "bye", 3);
    graph.InsertEdge("bye", "lol", 2);
    graph.InsertEdge("lol", "hi", 2);
    WHEN("Moved") {
      gdwg::Graph<std::string, int> move = std::move(graph);
      THEN("Moved graph is empty") {
        gdwg::Graph<std::string, int> res;
        res.InsertNode("hi");
        res.InsertNode("bye");
        res.InsertNode("lol");
        res.InsertEdge("hi", "hi", 4);
        res.InsertEdge("hi", "hi", 1);
        res.InsertEdge("hi", "bye", 3);
        res.InsertEdge("bye", "lol", 2);
        res.InsertEdge("lol", "hi", 2);
        REQUIRE(move == res);
      }
    }
  }
}

//============================================================
// Operations
//============================================================

//============================================================
// Methods
//============================================================
SCENARIO("Testing InsertNode()") {
  GIVEN("An empty graph") {
    gdwg::Graph<std::string, int> graph;
    WHEN("Node inserted") {
      THEN("Graph has 1 node and return true") {
        REQUIRE(graph.InsertNode("hello") == true);

        std::vector<std::string> vec{"hello"};
        gdwg::Graph<std::string, int> res{vec.begin(), vec.end()};
        REQUIRE(graph == res);
      }
    }
  }
  GIVEN("A graph with 2 nodes") {
    gdwg::Graph<std::string, int> graph{"hi", "bye"};
    WHEN("Node inserted") {
      THEN("Graph has 3 nodes and function return true") {
        REQUIRE(graph.InsertNode("hello") == true);
        gdwg::Graph<std::string, int> res{"hi", "bye", "hello"};
        REQUIRE(graph == res);
      }
    }
  }
  GIVEN("A graph with 1 node") {
    gdwg::Graph<std::string, int> graph{"hi"};
    WHEN("Node with same value is inserted") {
      THEN("It return false and graph still has 1 node") {
        REQUIRE(graph.InsertNode("hi") == false);
        gdwg::Graph<std::string, int> res{"hi"};
        REQUIRE(graph == res);
      }
    }
  }
}

SCENARIO("Testing InsertEdge()") {
  GIVEN("A graph with a node") {
    gdwg::Graph<std::string, int> graph{"hi"};
    WHEN("An edge is inserted on that node") {
      THEN("Edge is added and function returns true") {
        REQUIRE(graph.InsertEdge("hi", "hi", 3) == true);

        auto e = std::make_tuple("hi", "hi", 3);
        std::vector<std::tuple<std::string, std::string, int>> vec{e};
        gdwg::Graph<std::string, int> res{vec.begin(), vec.end()};
        REQUIRE(graph == res);
      }
    }
  }
  GIVEN("A graph with 2 nodes") {
    gdwg::Graph<std::string, int> graph{"hi", "bye"};
    WHEN("An edge is inserted on those 2 nodes") {
      THEN("Edge is added and function returns true") {
        REQUIRE(graph.InsertEdge("hi", "bye", 3) == true);

        auto e = std::make_tuple("hi", "bye", 3);
        std::vector<std::tuple<std::string, std::string, int>> vec{e};
        gdwg::Graph<std::string, int> res{vec.begin(), vec.end()};
        REQUIRE(graph == res);
      }
    }
  }
  GIVEN("A graph with 2 nodes and an existing edge") {
    gdwg::Graph<std::string, int> graph{"hi", "bye"};
    graph.InsertEdge("hi", "bye", 3);
    WHEN("The same edge is inserted on those 2 nodes") {
      THEN("Graph remains the same and function returns false") {
        REQUIRE(graph.InsertEdge("hi", "bye", 3) == false);

        auto e = std::make_tuple("hi", "bye", 3);
        std::vector<std::tuple<std::string, std::string, int>> vec{e};
        gdwg::Graph<std::string, int> res{vec.begin(), vec.end()};
        REQUIRE(graph == res);
      }
    }
  }
  GIVEN("A graph with 1 node") {
    gdwg::Graph<std::string, int> graph{"hi"};
    WHEN("We insert an edge onto a non existent source node") {
      THEN("Exception is thrown") {
        REQUIRE_THROWS_WITH(
            graph.InsertEdge("lol", "hi", 3),
            "Cannot call Graph::InsertEdge when either src or dst node does not exist");
      }
    }
  }
  GIVEN("A graph with 1 node") {
    gdwg::Graph<std::string, int> graph{"hi"};
    WHEN("We insert an edge onto a non existent destination node") {
      THEN("Exception is thrown") {
        REQUIRE_THROWS_WITH(
            graph.InsertEdge("hi", "lol", 3),
            "Cannot call Graph::InsertEdge when either src or dst node does not exist");
      }
    }
  }
}

SCENARIO("Testing Clear()") {
  GIVEN("An empty graph") {
    gdwg::Graph<std::string, int> graph;
    WHEN("cleared") {
      graph.Clear();
      THEN("It should be empty") {
        gdwg::Graph<std::string, int> res;
        REQUIRE(graph == res);
      }
    }
  }
  GIVEN("A graph with 1 node") {
    gdwg::Graph<std::string, int> graph{"lel"};
    WHEN("cleared") {
      graph.Clear();
      THEN("It should be empty") {
        gdwg::Graph<std::string, int> res;
        REQUIRE(graph == res);
      }
    }
  }
  GIVEN("A graph with 3 nodes") {
    gdwg::Graph<std::string, int> graph{"hi", "bye", "shy"};
    WHEN("cleared") {
      graph.Clear();
      THEN("It should be empty") {
        gdwg::Graph<std::string, int> res;
        REQUIRE(graph == res);
      }
    }
  }
  GIVEN("A graph with 3 nodes") {
    gdwg::Graph<std::string, int> graph{"hi", "bye", "shy"};
    WHEN("cleared") {
      graph.Clear();
      THEN("It should be empty and then new nodes and edges can be added") {
        gdwg::Graph<std::string, int> res;
        REQUIRE(graph == res);

        graph.InsertNode("omg");
        res.InsertNode("omg");
        REQUIRE(graph == res);

        graph.InsertEdge("omg", "omg", 2);
        res.InsertEdge("omg", "omg", 2);
        REQUIRE(graph == res);
      }
    }
  }
}

SCENARIO("Testing IsNode()") {
  GIVEN("A graph with 1 node") {
    gdwg::Graph<std::string, int> graph{"hi"};
    WHEN("Checked if that node exists") {
      THEN("Return true") { REQUIRE(graph.IsNode("hi") == true); }
    }
  }
  GIVEN("A graph with 3 nodes") {
    gdwg::Graph<std::string, int> graph{"hi", "bye", "shy"};
    WHEN("Checked if an existing node exists") {
      THEN("Return true") {
        REQUIRE(graph.IsNode("hi") == true);
        REQUIRE(graph.IsNode("bye") == true);
        REQUIRE(graph.IsNode("shy") == true);
      }
    }
  }
  GIVEN("An empty graph") {
    gdwg::Graph<std::string, int> graph;
    WHEN("Checked a non existing node is checked") {
      THEN("Return false") {
        REQUIRE(graph.IsNode("hi") == false);
        REQUIRE(graph.IsNode("bye") == false);
        REQUIRE(graph.IsNode("shy") == false);
      }
    }
  }
}

SCENARIO("Testing IsConnected()") {
  GIVEN("Graph with 2 nodes with 1 edge") {
    gdwg::Graph<std::string, int> graph{"hi", "bye"};
    graph.InsertEdge("hi", "bye", 3);
    WHEN("Checking if the edge connected (in edge case)") {
      THEN("Return true") { REQUIRE(graph.IsConnected("bye", "hi")); }
    }
  }
  GIVEN("Graph with 2 nodes with 1 edge") {
    gdwg::Graph<std::string, int> graph{"hi", "bye"};
    graph.InsertEdge("hi", "bye", 3);
    WHEN("Checking if the edge connected (out edge case)") {
      THEN("Return true") { REQUIRE(graph.IsConnected("hi", "bye")); }
    }
  }
  GIVEN("Graph with 2 nodes") {
    gdwg::Graph<std::string, int> graph{"hi", "bye"};
    WHEN("Checking if non-existent edge exists") {
      THEN("Return false") { REQUIRE(graph.IsConnected("hi", "bye") == false); }
    }
  }
  GIVEN("1 node and 1 edge") {
    gdwg::Graph<std::string, int> graph{"hi"};
    graph.InsertEdge("hi", "hi", 3);
    WHEN("Checked for an edge on a source node that doesn't exist") {
      THEN("Exception thrown") {
        REQUIRE_THROWS_WITH(
            graph.IsConnected("bye", "hi"),
            "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
      }
    }
  }
  GIVEN("1 node and 1 edge") {
    gdwg::Graph<std::string, int> graph{"hi"};
    graph.InsertEdge("hi", "hi", 3);
    WHEN("Checked for an edge on a destination node that doesn't exist") {
      THEN("Exception thrown") {
        REQUIRE_THROWS_WITH(
            graph.IsConnected("hi", "bye"),
            "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
      }
    }
  }
}

SCENARIO("Testing GetNodes()") {
  GIVEN("A graph with 0 nodes") {
    gdwg::Graph<std::string, int> graph;
    WHEN("GetNodes() is called") {
      THEN("Return vector with nothing") {
        std::vector<std::string> res;
        REQUIRE(graph.GetNodes() == res);
      }
    }
  }
  GIVEN("A graph with 1 node") {
    gdwg::Graph<std::string, int> graph{"hi"};
    WHEN("GetNodes() is called") {
      THEN("Return vector with 1 node") {
        std::vector<std::string> res{"hi"};
        REQUIRE(graph.GetNodes() == res);
      }
    }
  }
  GIVEN("A graph with 3 nodes") {
    gdwg::Graph<std::string, int> graph{"bye", "hi", "lol"};
    WHEN("GetNodes() is called") {
      THEN("Return vector with 3 nodes") {
        std::vector<std::string> res{"bye", "hi", "lol"};
        REQUIRE(graph.GetNodes() == res);
      }
    }
  }
  GIVEN("A graph with 3 nodes in a random order") {
    gdwg::Graph<std::string, int> graph{"hi", "bye", "lol"};
    WHEN("GetNodes() is called") {
      THEN("Return vector with 3 nodes that is ordered") {
        std::vector<std::string> res{"bye", "hi", "lol"};
        REQUIRE(graph.GetNodes() == res);
      }
    }
  }
}

SCENARIO("Testing GetConnected()") {
  GIVEN("A graph with 2 nodes and 1 edge") {
    gdwg::Graph<std::string, int> graph{"hi", "bye"};
    graph.InsertEdge("bye", "hi", 2);
    WHEN("GetConnected() called on hi node (checking in_edge)") {
      THEN("Return vector of size 1") {
        std::vector<std::string> res{"bye"};
        REQUIRE(graph.GetConnected("hi") == res);
      }
    }
  }
  GIVEN("A graph with 2 nodes and 1 edge") {
    gdwg::Graph<std::string, int> graph{"hi", "bye"};
    graph.InsertEdge("hi", "bye", 2);
    WHEN("GetConnected() called on hi node (checking out_edge)") {
      THEN("Return vector of size 1") {
        std::vector<std::string> res{"bye"};
        REQUIRE(graph.GetConnected("hi") == res);
      }
    }
  }
  GIVEN("A graph with 1 node") {
    gdwg::Graph<std::string, int> graph{"hi"};
    WHEN("GetConnected() called on hi node") {
      THEN("Return vector with no nodes") {
        std::vector<std::string> res;
        REQUIRE(graph.GetConnected("hi") == res);
      }
    }
  }
  GIVEN("A graph with 2 nodes and 2 edge") {
    gdwg::Graph<std::string, int> graph{"hi", "bye"};
    graph.InsertEdge("hi", "bye", 2);
    graph.InsertEdge("hi", "bye", 3);
    WHEN("GetConnected() called on hi node") {
      THEN("Return vector of only size 1 (checking no duplicates)") {
        std::vector<std::string> res{"bye"};
        REQUIRE(graph.GetConnected("hi") == res);
      }
    }
  }
  GIVEN("A graph with 4 nodes and 3 edges") {
    gdwg::Graph<std::string, int> graph{"lol", "hi", "pop", "bye"};
    graph.InsertEdge("hi", "bye", 3);
    graph.InsertEdge("hi", "lol", 3);
    graph.InsertEdge("hi", "pop", 3);
    WHEN("GetConnected() called on hi node") {
      THEN("Return vector of size 3 (checking vector gets ordered)") {
        std::vector<std::string> res{"bye", "lol", "pop"};
        REQUIRE(graph.GetConnected("hi") == res);
      }
    }
  }
  GIVEN("A graph with 0 nodes") {
    gdwg::Graph<std::string, int> graph;
    WHEN("GetConnected() called on non-existent node") {
      THEN("Exception thrown") {
        REQUIRE_THROWS_WITH(graph.GetConnected("hi"),
                            "Cannot call Graph::GetConnected if src doesn't exist in the graph");
      }
    }
  }
}

SCENARIO("Testing GetWeights()") {
  GIVEN("Graph with 2 nodes only") {
    gdwg::Graph<std::string, int> graph{"hi", "bye"};
    WHEN("GetWeights() is called") {
      THEN("Vector of size 0 is returned") {
        std::vector<int> res;
        REQUIRE(graph.GetWeights("hi", "bye") == res);
      }
    }
  }
  GIVEN("Graph with 2 nodes and 1 edge") {
    gdwg::Graph<std::string, int> graph{"hi", "bye"};
    graph.InsertEdge("bye", "hi", 3);
    WHEN("GetWeights() is called") {
      THEN("Vector of size 1 is returned (checking in_edge)") {
        std::vector<int> res{3};
        REQUIRE(graph.GetWeights("hi", "bye") == res);
      }
    }
  }
  GIVEN("Graph with 2 nodes and 1 edge") {
    gdwg::Graph<std::string, int> graph{"hi", "bye"};
    graph.InsertEdge("hi", "bye", 3);
    WHEN("GetWeights() is called") {
      THEN("Vector of size 1 is returned (checking out_edge)") {
        std::vector<int> res{3};
        REQUIRE(graph.GetWeights("hi", "bye") == res);
      }
    }
  }
  GIVEN("Graph with 2 nodes and 2 edges") {
    gdwg::Graph<std::string, int> graph{"hi", "bye"};
    graph.InsertEdge("hi", "bye", 3);
    graph.InsertEdge("bye", "hi", 3);
    WHEN("GetWeights() is called") {
      THEN("Vector of size 2 is returned (checking duplicate edges is allowed)") {
        std::vector<int> res{3, 3};
        REQUIRE(graph.GetWeights("hi", "bye") == res);
      }
    }
  }
  GIVEN("Graph with 2 nodes and 4 edges") {
    gdwg::Graph<std::string, int> graph{"hi", "bye"};
    graph.InsertEdge("hi", "bye", 5);
    graph.InsertEdge("hi", "bye", 3);
    graph.InsertEdge("bye", "hi", 6);
    graph.InsertEdge("bye", "hi", 3);
    WHEN("GetWeights() is called") {
      THEN("Vector of size 4 is returned (checking the vector is ordered)") {
        std::vector<int> res{3, 3, 5, 6};
        REQUIRE(graph.GetWeights("hi", "bye") == res);
      }
    }
  }
  GIVEN("Graph with 1 source node") {
    gdwg::Graph<std::string, int> graph{"hi"};
    WHEN("GetWeights() is called") {
      THEN("Exception thrown because no src node") {
        REQUIRE_THROWS_WITH(
            graph.GetWeights("lol", "hi"),
            "Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
      }
    }
  }
  GIVEN("Graph with 1 destination node") {
    gdwg::Graph<std::string, int> graph{"hi"};
    WHEN("GetWeights() is called") {
      THEN("Exception thrown because no destination node") {
        REQUIRE_THROWS_WITH(
            graph.GetWeights("hi", "lol"),
            "Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
      }
    }
  }
}

//============================================================
// Friends
//============================================================

SCENARIO("Outstream operator overloading") {
  GIVEN("Test from assignment page") {
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
    g.InsertEdge(2, 4, -3);
    g.InsertEdge(3, 6, -8);
    g.InsertEdge(3, 2, 2);
    g.InsertEdge(4, 1, -4);
    g.InsertEdge(4, 5, 3);
    g.InsertEdge(5, 2, 7);
    g.InsertEdge(6, 2, 5);
    g.InsertEdge(6, 3, 10);

    THEN("Print out a correct graph (from assignment page)") {
      std::stringstream stream;
      stream << g;
      std::string ans = "";
      ans.append("1 (\n");
      ans.append("  5 | -1\n");
      ans.append(")\n");
      ans.append("2 (\n");
      ans.append("  1 | 1\n");
      ans.append("  4 | -3\n");
      ans.append("  4 | -2\n");
      ans.append("  4 | 2\n");
      ans.append(")\n");
      ans.append("3 (\n");
      ans.append("  2 | 2\n");
      ans.append("  6 | -8\n");
      ans.append(")\n");
      ans.append("4 (\n");
      ans.append("  1 | -4\n");
      ans.append("  5 | 3\n");
      ans.append(")\n");
      ans.append("5 (\n");
      ans.append("  2 | 7\n");
      ans.append(")\n");
      ans.append("6 (\n");
      ans.append("  2 | 5\n");
      ans.append("  3 | 10\n");
      ans.append(")\n");
      ans.append("7 (\n");
      ans.append(")\n");
      REQUIRE(stream.str() == ans);
    }
  }

}

SCENARIO("Testing friend operator== and operator!=") {
  GIVEN("Two empty graphs") {
    gdwg::Graph<std::string, int> graph;
    gdwg::Graph<std::string, int> res;
    THEN("They are the same") {
      REQUIRE((graph == res) == true);
      REQUIRE((graph != res) == false);
    }
  }
  GIVEN("Two graphs with different amount of nodes") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    gdwg::Graph<std::string, int> res;
    res.InsertNode("hi");
    res.InsertNode("bye");
    THEN("They are different") {
      REQUIRE((graph == res) == false);
      REQUIRE((graph != res) == true);
    }
  }
  GIVEN("Two graphs with same amount of nodes") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    gdwg::Graph<std::string, int> res;
    res.InsertNode("hi");
    res.InsertNode("bye");
    THEN("They are the same") {
      REQUIRE((graph == res) == true);
      REQUIRE((graph != res) == false);
    }
  }
  GIVEN("Two graphs with same amount of nodes but different nodes") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    gdwg::Graph<std::string, int> res;
    res.InsertNode("hi");
    res.InsertNode("lol");
    THEN("They are different") {
      REQUIRE((graph == res) == false);
      REQUIRE((graph != res) == true);
    }
  }
  GIVEN("Two graphs with same nodes but different in_edge_ array size") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertEdge("hi", "bye", 3);
    gdwg::Graph<std::string, int> res;
    res.InsertNode("hi");
    res.InsertNode("bye");
    THEN("They are different") {
      REQUIRE((graph == res) == false);
      REQUIRE((graph != res) == true);
    }
  }
  GIVEN("Two graphs with same nodes, same in_edge_ array size but different out_edge_ array size") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertEdge("hi", "bye", 3);
    gdwg::Graph<std::string, int> res;
    res.InsertNode("hi");
    res.InsertNode("bye");
    res.InsertEdge("hi", "bye", 3);
    res.InsertEdge("bye", "hi", 3);
    THEN("They are different") {
      REQUIRE((graph == res) == false);
      REQUIRE((graph != res) == true);
    }
  }
  GIVEN("Two graphs with same nodes, same edge array sizes and same edge values") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertEdge("hi", "bye", 3);
    graph.InsertEdge("bye", "hi", 3);
    gdwg::Graph<std::string, int> res;
    res.InsertNode("hi");
    res.InsertNode("bye");
    res.InsertEdge("hi", "bye", 3);
    res.InsertEdge("bye", "hi", 3);
    THEN("They are the same") {
      REQUIRE((graph == res) == true);
      REQUIRE((graph != res) == false);
    }
  }
  GIVEN("Two graphs with same nodes, same edge array sizes, but different edge values") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertEdge("hi", "bye", 3);
    graph.InsertEdge("bye", "hi", 3);
    gdwg::Graph<std::string, int> res;
    res.InsertNode("hi");
    res.InsertNode("bye");
    res.InsertEdge("hi", "hi", 3);
    res.InsertEdge("bye", "hi", 3);
    THEN("They are different") {
      REQUIRE((graph == res) == false);
      REQUIRE((graph != res) == true);
    }
  }
  GIVEN("Two graphs with same nodes, same edge array sizes and same edge values but created in "
        "different order") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertEdge("hi", "bye", 3);
    graph.InsertEdge("bye", "hi", 3);
    gdwg::Graph<std::string, int> res;
    res.InsertNode("hi");
    res.InsertNode("bye");
    res.InsertEdge("bye", "hi", 3);
    res.InsertEdge("hi", "bye", 3);
    THEN("They are the same") {
      REQUIRE((graph == res) == true);
      REQUIRE((graph != res) == false);
    }
  }
  GIVEN("Two complicated graphs with 5 nodes and 7 edges that are all equal, but created in "
        "different orders") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertNode("fly");
    graph.InsertNode("die");
    graph.InsertNode("shy");
    graph.InsertEdge("hi", "bye", 4);
    graph.InsertEdge("hi", "fly", 2);
    graph.InsertEdge("hi", "hi", 4);
    graph.InsertEdge("hi", "hi", 2);
    graph.InsertEdge("fly", "die", 5);
    graph.InsertEdge("shy", "die", 4);
    graph.InsertEdge("die", "fly", 3);

    gdwg::Graph<std::string, int> res;
    res.InsertNode("die");
    res.InsertNode("bye");
    res.InsertNode("fly");
    res.InsertEdge("die", "fly", 3);
    res.InsertNode("hi");
    res.InsertEdge("hi", "hi", 4);
    res.InsertEdge("hi", "hi", 2);
    res.InsertEdge("hi", "bye", 4);
    res.InsertEdge("hi", "fly", 2);
    res.InsertNode("shy");
    res.InsertEdge("fly", "die", 5);
    res.InsertEdge("shy", "die", 4);

    THEN("They are the same") {
      REQUIRE((graph == res) == true);
      REQUIRE((graph != res) == false);
    }
  }
  GIVEN("Two complicated graphs with 5 nodes and 7 edges that are slightly different") {
    gdwg::Graph<std::string, int> graph;
    graph.InsertNode("hi");
    graph.InsertNode("bye");
    graph.InsertNode("fly");
    graph.InsertNode("die");
    graph.InsertNode("shy");
    graph.InsertEdge("hi", "bye", 4);
    graph.InsertEdge("hi", "fly", 2);
    graph.InsertEdge("hi", "hi", 4);
    graph.InsertEdge("hi", "hi", 2);
    graph.InsertEdge("fly", "die", 5);
    graph.InsertEdge("shy", "die", 4);
    graph.InsertEdge("die", "fly", 3);

    gdwg::Graph<std::string, int> res;
    res.InsertNode("die");
    res.InsertNode("bye");
    res.InsertNode("fly");
    res.InsertEdge("die", "fly", 3);
    res.InsertNode("hi");
    res.InsertEdge("hi", "hi", 4);
    res.InsertEdge("hi", "hi", 2);
    res.InsertEdge("hi", "bye", 4);
    res.InsertEdge("hi", "fly", 2);
    res.InsertNode("shy");
    res.InsertEdge("fly", "die", 4);
    res.InsertEdge("shy", "die", 4);

    THEN("They are different") {
      REQUIRE((graph == res) == false);
      REQUIRE((graph != res) == true);
    }
  }
}

//============================================================
// Helper methods
//============================================================
SCENARIO("Testing GetEdgeDst() custom method in Node datatype") {}

SCENARIO("Testing GetSrcValue() custom method in Edge datatype") {}

SCENARIO("Testing GetDstValue() custom method in Edge datatype") {}
