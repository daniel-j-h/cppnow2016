#include <iostream>
#include <vector>

#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/breadth_first_search.hpp>

using namespace boost;


// Here we provide a custom breadth-first search visitor, printing vertices in the order we discover them.
// Note how the breadth_first_search call at the end runs through before the final "*" is printed.

using graph_t = compressed_sparse_row_graph<directedS>;
using vertex_t = graph_traits<graph_t>::vertex_descriptor;

struct discover_visitor : default_bfs_visitor {
  void discover_vertex(const vertex_t vertex, const graph_t&) {
    std::cout << vertex << std::endl;
  }
};

int main() {
  /*
   * 0 -> 1 -> 2
   * ^    |    |
   * |    v    v
   * 5 <- 4 <- 3
   */
  auto n_vertices = 6u;
  std::vector<vertex_t> sources{0, 1, 1, 2, 3, 4, 5};
  std::vector<vertex_t> targets{1, 2, 4, 3, 4, 5, 0};

  auto tag = construct_inplace_from_sources_and_targets;
  graph_t graph{tag, sources, targets, n_vertices};

  vertex_t source{0};
  breadth_first_search(graph, source, visitor(discover_visitor{}));
  std::cout << "*" << std::endl;
}
