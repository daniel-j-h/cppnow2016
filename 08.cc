#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>

#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/graph/graph_traits.hpp>

#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>

#include <boost/algorithm/string/join.hpp>

#include <boost/format.hpp>

using namespace boost;
using namespace boost::adaptors;


// The following shows how to produce GeoJSON from your graph with location-tagged vertices.
// Use Mapbox Studio geojson.io or Github / Gist to visualize the GeoJSON result on top of a map.
// You can format the output for quick manual inspection with: ./08 | python3 -m json.tool
// For larger graphs you want to use tippecanoe for zoom-level based simplification.
// The following could be made more generic requiring only a location property map.

struct location_t { float longitude = 0., latitude = 0.; };

using graph_t = compressed_sparse_row_graph<directedS, location_t>;
using vertex_t = graph_traits<graph_t>::vertex_descriptor;


std::ostream& operator<<(std::ostream& out, const location_t location) {
  boost::format fmt{"{\"type\":\"Feature\","
                     "\"properties\":{},"
                     "\"geometry\":{"
                       "\"type\":\"Point\","
                       "\"coordinates\":[%1$.5f,%2$.5f]}}"};

  return out << (fmt % location.longitude % location.latitude);
}

std::ostream& operator<<(std::ostream& out, const graph_t graph) {
  boost::format fmt{"{\"type\":\"FeatureCollection\","
                     "\"features\":[%1%]}"};

  auto location = [&graph](auto vertex) {
    std::ostringstream fmt;
    fmt << graph[vertex];
    return fmt.str();
  };

  auto coordinates = vertices(graph) | transformed(location);
  return out << (fmt % algorithm::join(coordinates, ","));
}


int main() {
  auto n_vertices = 3u;
  std::vector<vertex_t> sources{0, 1, 2};
  std::vector<vertex_t> targets{1, 2, 0};

  auto tag = construct_inplace_from_sources_and_targets;
  graph_t graph{tag, sources, targets, n_vertices};

  graph[0] = {13.42252, 52.49603};
  graph[1] = {13.40229, 52.52363};
  graph[2] = {13.41816, 52.49933};

  std::cout << graph << std::endl;
}
