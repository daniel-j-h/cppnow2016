#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>

using namespace boost;


// The following constructs a simple graph we can dynamically add edges and vertices to.
// Using vecS for the adjacency list containers selects std::vector for inner and outer container.
// Using directedS makes all edges directed by default. We can still manually add reverse edges.

using graph_t = adjacency_list<vecS, vecS, directedS>;

int main() {
  auto n_vertices = 3u;
  graph_t graph(n_vertices);

  add_edge(0, 1, graph);
  add_edge(1, 2, graph);
  add_edge(2, 0, graph);

  print_graph(graph);
}
