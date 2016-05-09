#include <iostream>

#include <boost/graph/adjacency_list.hpp>

#include <boost/range.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/adaptors.hpp>

using namespace boost;
using namespace boost::adaptors;


// Here we show Bundled Properties by attaching edge_data_t to each edge in the adjacency list.
// We use boost::no_property for vertex properties since we do not want properties on them.
// Algorithms such as vertices(graph) and edges(graph) return ranges (pairs with first, last).
// We prefer using Boost.Range's algorithms such as boost::accumulate to iterate on the pair's range.
// In addition, we find Boost.Range's adaptors and their pipe syntax a perfect fit for these use-cases.

struct edge_data_t { int duration = 0; };

using graph_t = adjacency_list<vecS, vecS, directedS, no_property, edge_data_t>;

int main() {
  auto n_vertices = 3u;
  graph_t graph(n_vertices);

  add_edge(0, 1, edge_data_t{100}, graph);
  add_edge(1, 2, edge_data_t{200}, graph);
  add_edge(2, 0, edge_data_t{-10}, graph);

  auto duration = [&graph](auto edge) { return graph[edge].duration; };
  auto positive = [](auto duration) { return duration > 0; };

  auto total = accumulate(edges(graph) | transformed(duration) | filtered(positive), 0);

  std::cout << total << std::endl;
}
