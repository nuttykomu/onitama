I am building an Onitama AI agent based on the Monte Carlo Tree Search (MCTS) algorithm. Right now, the agent is slow as hell (like 400-500 iterations per second), so I am focusing on optimization at the moment. I have some ideas for speeding up the execution:

- [ ] Replace all instances of `std::vector` with C arrays. After profiling the code with `gprof`, I discovered that most of the running time is spent in the `std::vector` methods (primarily allocation and `push_back` operations). I tried using `reserve` to limit the amount of times the internal array needs to be resized — didn't really do much. Time to bring out the raw pointers!

*Update #1:* I began refactoring out some instances of `std::vector` containers, replacing them with C arrays, in commit `9ed60bef`. The speedup is already almost 5-fold.

- [x] The program is single-threaded, so it only uses a fraction of the CPU power available on my machine. Parallelize the computation to make use of all of the CPU cores. One idea is to use *root parallelization* — build multiple MCTS trees in parallel. At the end of the computation, merge the scores in the root children. This method requires only a minimal amount of communication between the threads, so it should be relatively easy to implement.

*Update #2:* After multithreading the agent, the CPU usage went up from ~15-16% to 95+%. The agent is even 5x faster than it was *Update #1*.

- [ ] ~~Every node in the tree is dynamically allocated during the expansion phase. Do away with dynamic allocation. Instead, implement and manage a static buffer of free nodes. Move nodes from the buffer to the tree when the tree needs to be expanded. When the game state changes, resulting in unreachable branches, move the unreachable nodes from the tree back to the buffer.~~ Nevermind. This probably will not work as it will cause the stack to run out of memory. The tree nodes will remain dynamically allocated. However, it may be worth investigating whether preallocating a chunk of memory will result in a significant increase in speed over allocating nodes on the fly.

## Building

Compile with `clang++` because `g++` does not support unicode variable identifiers.

```
git clone https://github.com/nuttykomu/onitama.git && cd source/onitama
clang benchmark.cc Agent.cc Board.cc Card.cc Move.cc Random.cc State.cc
clang main.cc Agent.cc Board.cc Card.cc Move.cc Random.cc State.cc
```

## Play

To play against the AI agent, execute the driver program:

```
./main
```

## Benchmark

`benchmark` runs MCTS on a random initial board state for 30 seconds and measures how many iterations were completed.

```
./benchmark
```

## Profiling

To generate a code profile report, run:

```
sh benchmark.sh
```

This outputs a visual graph (`report.pdf`) that provides a [visualization](https://github.com/jrfonseca/gprof2dot#output) of the "hot-spot" function calls. Make sure that `g++`, `gprof`, `gprof2dot`, and `dot` can be located in your `$PATH`. If your system is Microsoft Windows, MinGW must be installed with the `POSIX` threads option.

## High Scores

Benchmarks were executed on an Intel Core i7-6700 CPU @ 3.40GHz. Scores are averaged over 10 runs.

`02b5ad0c` - **12,417** (414 iterations/sec)

`9ed60bef` - **57,208** (1,907 iterations/sec)

`b0deb3c9` - **319,359** (10,645 iterations/sec)