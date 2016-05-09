#include <iostream>
#include <vector>

#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/graph/graph_traits.hpp>

#include <boost/property_map/property_map.hpp>

#include <boost/range.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/adaptors.hpp>

using namespace boost;
using namespace boost::adaptors;


// The following uses a static graph (compressed sparse row graph) we can no longer modify once constructed.
// Due to this restriction it is highly compact and efficient, and the only option for large sparse graphs.
// We do not use Bundled Properties but instead only temporarily use external properties through a property map.

struct vertex_data_t { int priority = 0; };

using graph_t = compressed_sparse_row_graph<directedS>;
using vertex_t = graph_traits<graph_t>::vertex_descriptor;

int main() {
  auto n_vertices = 3u;
  std::vector<vertex_t> sources{0, 1, 2};
  std::vector<vertex_t> targets{1, 2, 0};

  auto tag = construct_inplace_from_sources_and_targets;
  graph_t graph{tag, sources, targets, n_vertices};

  std::vector<vertex_data_t> vertex_data{{15}, {-5}, {10}};
  auto vertex_data_map = make_iterator_property_map(vertex_data.begin(), get(vertex_index, graph));

  auto priority = [&vertex_data_map](auto vertex) { return get(vertex_data_map, vertex).priority; };

  auto avg = accumulate(vertices(graph) | transformed(priority), 0.) / size(vertex_data);

  std::cout << avg << std::endl;
}
