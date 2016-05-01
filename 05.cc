#include <iostream>
#include <vector>

#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/breadth_first_search.hpp>

#include <boost/coroutine/all.hpp>

using namespace boost;


using graph_t = compressed_sparse_row_graph<directedS>;
using vertex_t = graph_traits<graph_t>::vertex_descriptor;
using coro_t = coroutines::asymmetric_coroutine<vertex_t>;

struct discover_visitor : default_bfs_visitor {
  discover_visitor(coro_t::push_type& sink_) : sink(sink_) { }

  void discover_vertex(const vertex_t vertex, const graph_t&) {
    sink(vertex);
  }

  coro_t::push_type& sink;
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

  coro_t::pull_type lazy_bfs_vertices{[&](auto& sink) {
    breadth_first_search(graph, source, visitor(discover_visitor{sink}));
  }};

  for (auto vertex : lazy_bfs_vertices) {
    std::cout << vertex << std::endl;
    std::cout << "*" << std::endl;
  }
}
