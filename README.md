## Pulling Visitors: Boost.Graph + Boost.Coroutine

[![Continuous Integration](https://travis-ci.org/daniel-j-h/cppnow2016.svg?branch=master)](https://travis-ci.org/daniel-j-h/cppnow2016)


## Overview

I recommend going through the examples in order.

| Example        | Introduces                                                                                           |
| -------------- | ---------------------------------------------------------------------------------------------------- |
| [01.cc](01.cc) | Dynamic graph, `adjacency_list`                                                                      |
| [02.cc](02.cc) | Bundled Properties, working with vertex / edge ranges                                                |
| [03.cc](03.cc) | Static graph, `compressed_sparse_row_graph`, temporary graph-external properties                     |
| [04.cc](04.cc) | Breadth-first search, customization through visitor                                                  |
| [05.cc](05.cc) | Breadth-first search, inverting control flow with coroutines, stepwise iteration, stdlib integration |
| [06.cc](06.cc) | Bidirectional dijkstra, customization through visitor, problem with stepping visitors                |
| [07.cc](07.cc) | Bidirectional dijkstra, inverted control flow with coroutines, stepwise iteration                    |
| [08.cc](08.cc) | GeoJSON from graph for visualization                                                                 |


## Building the Examples


    mkdir build && cd build
    export CC='clang' CXX='clang++' CXXFLAGS='-Wall -Wextra -pedantic'
    cmake .. -DCMAKE_BUILD_TYPE=Release

With [Nix](https://nixos.org/nix/):

    nix-shell --pure --run 'env CXXFLAGS="-Wall -Wextra -pedantic" mkdir build && cd build && cmake ..'
    nix-shell --pure --run 'cmake --build build'


## Resources

- [Boost.Graph](http://www.boost.org/doc/libs/1_60_0/libs/graph/doc/table_of_contents.html)
- [Boost.Graph Concepts](http://www.boost.org/doc/libs/1_60_0/libs/graph/doc/graph_concepts.html)
- [Boost.Coroutine](http://www.boost.org/doc/libs/1_60_0/libs/coroutine/doc/html/index.html)
- [tippecanoe](https://github.com/mapbox/tippecanoe) for zoom-based GeoJSON simplification
- [Mapbox Studio](https://www.mapbox.com/studio) or [geojson.io](http://geojson.io) for visualizing GeoJSON


## License

Copyright © 2016 Daniel J. Hofmann

Distributed under the MIT License (MIT).
