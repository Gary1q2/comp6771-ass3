/*

  == Explanation and rational of testing ==

   For each constructor, operation and method we thought of all
   the possible edge cases and wrote edge case tests to ensure our methods would
   pass them. Along with our edge case tests we added 1-2 normal cases
   to make sure our methods would function normally.

   We are certain we have covered most if not all the possibilities because
   we have spent time ensuring no edge case is left uncovered.


*/

//Change this back to absolute path, only for IDE
//#include "assignments/dg/graph.h"
#include "graph.h"
#include "catch.h"

//============================================================
// Constructors
//============================================================
SCENARIO("Testing default constructor") {
    GIVEN("A constructed graph") {
        gdwg::Graph<std::string, int> graph;
        WHEN("Checked with another graph that was default constructed") {
            gdwg::Graph<std::string, int> res;
            THEN("Graphs are equal") {
                REQUIRE((graph == res) == true);
            }
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
    GIVEN("A vector with 3 tuple but only 3 unique nodes") {
        auto e1 = std::make_tuple("hi", "bye", 3);
        auto e2 = std::make_tuple("lol", "bye", 6);
        auto e3 = std::make_tuple("lol", "hi", 2);
        std::vector<std::tuple<std::string, std::string, int>> vec{e1, e2, e3};
        gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
        THEN("There will be 3 node in graph + 3 edges") {
            gdwg::Graph<std::string, int> res;
            res.InsertNode("hi");
            res.InsertNode("bye");
            res.InsertNode("lol");
            res.InsertEdge("hi", "bye", 3);
            res.InsertEdge("lol", "bye", 6);
            res.InsertEdge("lol", "hi", 2);
            REQUIRE(graph == res);
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
    GIVEN("A graph with 3 nodes") {
        std::vector<std::string> vec{"hi", "bye", "shy"};
        gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
        WHEN("Node inserted") {
            THEN("Graph has 4 nodes") {
                REQUIRE(graph.InsertNode("hello") == true);


                std::vector<std::string> vec{"hi", "bye", "shy", "hello"};
                gdwg::Graph<std::string, int> res{vec.begin(), vec.end()};
                REQUIRE(graph == res);
            }
        }
    }
    GIVEN("A graph with 1 node") {
        std::vector<std::string> vec{"hi"};
        gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
        WHEN("Node with same value is inserted") {
            THEN("It return false and graph still has 1 node") {
                REQUIRE(graph.InsertNode("hi") == false);

                gdwg::Graph<std::string, int> res{vec.begin(), vec.end()};
                REQUIRE(graph == res);
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
        gdwg::Graph<std::string, int> graph;
        graph.InsertNode("lel");
        WHEN("cleared") {
            graph.Clear();
            THEN("It should be empty") {
                gdwg::Graph<std::string, int> res;
                REQUIRE(graph == res);

            }
        }
    }
    GIVEN("A graph with 3 nodes") {
        std::vector<std::string> vec {"hi", "bye", "shy"};
        gdwg::Graph<std::string, int> graph{vec.begin(), vec.end()};
        WHEN("cleared") {
            graph.Clear();
            THEN("It should be empty but after you can add another node to it") {
                gdwg::Graph<std::string, int> res;
                REQUIRE(graph == res);

                graph.InsertNode("lol");
                res.InsertNode("lol");
                REQUIRE(graph == res);
            }
        }
    }
}


//============================================================
// Friends
//============================================================


SCENARIO("Outstream operator overloading")
{
  gdwg::Graph<std::string, int> g;
  g.InsertNode("hello");
  g.InsertNode("how");
  g.InsertNode("are");
  g.InsertNode("you?");

  g.InsertEdge("hello", "how", 5);
  g.InsertEdge("hello", "are", 8);
  g.InsertEdge("hello", "are", 2);

  g.InsertEdge("how", "you?", 1);
  g.InsertEdge("how", "hello", 4);

  g.InsertEdge("are", "you?", 3);

  std::cout << g << '\n';

  gdwg::Graph<std::string, int> g2{g};

  std::cout << g2 << "\n";
  WHEN("Print out a normal graph (from assignment page)")
  {
  }
}
















SCENARIO("Testing friend operator==") {
    GIVEN("Two empty graphs") {
        gdwg::Graph<std::string, int> graph;
        gdwg::Graph<std::string, int> res;
        THEN("Return true") {
            REQUIRE((graph == res));
        }
    }
    GIVEN("Two graphs with different amount of nodes") {
        gdwg::Graph<std::string, int> graph;
        graph.InsertNode("hi");
        gdwg::Graph<std::string, int> res;
        res.InsertNode("hi");
        res.InsertNode("bye");
        THEN("Return false") {
            REQUIRE((graph == res) == false);
        }
    }
    GIVEN("Two graphs with same amount of nodes and same nodes") {
        gdwg::Graph<std::string, int> graph;
        graph.InsertNode("hi");
        graph.InsertNode("bye");
        gdwg::Graph<std::string, int> res;
        res.InsertNode("hi");
        res.InsertNode("bye");
        THEN("Return true") {
            REQUIRE(graph == res);
        }
    }
    GIVEN("Two graphs with same amount of nodes but different nodes") {
        gdwg::Graph<std::string, int> graph;
        graph.InsertNode("hi");
        graph.InsertNode("bye");
        gdwg::Graph<std::string, int> res;
        res.InsertNode("hi");
        res.InsertNode("lol");
        THEN("Return false") {
            REQUIRE((graph == res) == false);
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
        THEN("Return false") {
            REQUIRE((graph == res) == false);
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
        THEN("Return false") {
            REQUIRE((graph == res) == false);
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
        THEN("Return true") {
            REQUIRE(graph == res);
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
        THEN("Return false") {
            REQUIRE((graph == res) == false);
        }
    }
    GIVEN("Two graphs with same nodes, same edge array sizes and same edge values but created in different order") {
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
        THEN("Return true") {
            REQUIRE(graph == res);
        }
    }
    GIVEN("Two complicated graphs with 5 nodes and 7 edges that are all equal, but created in different orders") {
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

        THEN("Return true") {
            REQUIRE(graph == res);
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

        THEN("Return false") {
            REQUIRE((graph == res) == false);
        }
    }
}


















//============================================================
// Helper methods
//============================================================
