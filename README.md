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

Note: apply `use-boost-coroutine2.patch` if you want to use the newer Boost.Coroutine2 instead of the Boost.Coroutine library.
This requires your Boost >=1.59 distribution to be build with `CXXFLAGS=-std=c++14`, which is probably not the case by default or using Boost >=1.61 where Boost.Coroutine2 was relaxed to C++11.

## Resources

- [Boost.Graph](http://www.boost.org/doc/libs/1_60_0/libs/graph/doc/table_of_contents.html)
- [Boost.Graph Concepts](http://www.boost.org/doc/libs/1_60_0/libs/graph/doc/graph_concepts.html)
- [Boost.Coroutine](http://www.boost.org/doc/libs/1_60_0/libs/coroutine/doc/html/index.html)
- [tippecanoe](https://github.com/mapbox/tippecanoe) for zoom-based GeoJSON simplification
- [Mapbox Studio](https://www.mapbox.com/studio) or [geojson.io](http://geojson.io) for visualizing GeoJSON
- [Richel Bilderbeek's recent take on writing a C++11 Boost.Graph tutorial](https://github.com/richelbilderbeek/BoostGraphTutorial)
- [libosmium](https://github.com/osmcode/libosmium) and [Boost.Geometry](http://www.boost.org/doc/libs/1_60_0/libs/geometry/doc/html/index.html) for your OpenStreetMap based project
- [How it all started](http://lists.boost.org/boost-users/2015/11/85302.php)


## License

Copyright © 2016 Daniel J. Hofmann

Distributed under the MIT License (MIT).
