#include <iostream>
#include <vector>

#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/breadth_first_search.hpp>

#include <boost/range/algorithm.hpp>

#include <boost/coroutine/all.hpp>

using namespace boost;


// In the following we introduce coroutines and the overall pattern presented here.
// We provide a breadth-first search visitor that pushes vertices into a push_type coroutine.
// Using the coroutine's pull_type lets us transform the visitor into a lazy generator we can step through.
// The generator provides the usual begin(), end() interface and is suitable for range-based for loops.
// Looping through the generator does the following:
//  - run the visitor for one vertex
//  - stop the visitor handing over the vertex to the call site
//  - resume the visitor for one vertex, repeat this stepwise process
// This provides us with a lazy range of vertices in breadth-first order we can loop over, inverting the control flow.
// Note how we can use stdlib algorithms on this range, e.g. std::find_if to search for vertices in breadth-first order.

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

  // The following shows how we're able to plug in the full stdlib algorithms.
  // It also shows what happens if you step through an exhausted generator.
  // Give it a try and then comment out the range-based for loop above.

  // auto splits = [&graph](auto vertex) { return out_degree(vertex, graph) > 1; };
  // auto it = find_if(lazy_bfs_vertices, splits);
  //
  // if (it != end(lazy_bfs_vertices))
  //   std::cout << *it << std::endl;
}
