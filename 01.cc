#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>

using namespace boost;


using graph_t = adjacency_list<vecS, vecS, directedS>;

int main() {
  auto n_vertices = 3u;
  graph_t graph(n_vertices);

  add_edge(0, 1, graph);
  add_edge(1, 2, graph);
  add_edge(2, 0, graph);

  print_graph(graph);
}
