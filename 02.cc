#include <iostream>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

#include <boost/range.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/adaptors.hpp>

using namespace boost;
using namespace boost::adaptors;


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
