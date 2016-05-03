## Pulling Visitors: Boost.Graph + Boost.Coroutine

[![Continuous Integration](https://travis-ci.org/daniel-j-h/cppnow2016.svg?branch=master)](https://travis-ci.org/daniel-j-h/cppnow2016)


    mkdir build && cd build
    export CC='clang' CXX='clang++' CXXFLAGS='-Wall -Wextra -pedantic'
    cmake .. -DCMAKE_BUILD_TYPE=Release

With [Nix](https://nixos.org/nix/):

    nix-shell --pure --run 'env CXXFLAGS="-Wall -Wextra -pedantic" mkdir build && cd build && cmake ..'
    nix-shell --pure --run 'cmake --build build'


## License

Copyright © 2016 Daniel J. Hofmann

Distributed under the MIT License (MIT).
