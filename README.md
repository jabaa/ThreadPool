[![Build Status](https://travis-ci.org/jabaa/ThreadPool.svg?branch=master)](https://travis-ci.org/jabaa/ThreadPool)

# ThreadPool
A C++11 library implementing a thread pool.

## Installation with conan
Add remote: `conan remote add jabaa https://api.bintray.com/conan/jabaa/Conan`
Install: `conan install -r jabaa ThreadPool@0.1@jabaa/stable`

## Build from source
Generate with examples: `cmake -DBUILD_EXAMPLES=true ..`
or
Generate without examples: `cmake ..`
Build:`cmake --build .`
