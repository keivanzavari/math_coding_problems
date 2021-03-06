
#include <utility>
#include <vector>

// clang-format off
#include "graph_definitions.h"
#include "dfs.h"
// clang-format on

void testClrsDfsExample() {
  constexpr bool directed = true;
  Graph<char> g(directed);
  char vertices[] = {'u', 'v', 'w', 'x', 'y', 'z'};
  std::vector<std::pair<char, char>> edges{{'u', 'v'}, {'u', 'x'}, {'v', 'y'}, {'x', 'v'},
                                           {'y', 'x'}, {'w', 'y'}, {'w', 'z'}, {'z', 'z'}};
  for (const auto v : vertices) {
    g.addVertex(v);
  }

  for (const auto e : edges) {
    g.addEdge(e.first, e.second);
  }
  g.print();

  dfs(g.get(), 'u');
}

void testDag() {
  constexpr bool directed = true;
  Graph<char> g(directed);
  char vertices[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
  std::vector<std::pair<char, char>> edges{{'g', 'h'}, {'a', 'h'}, {'a', 'b'}, {'b', 'c'},
                                           {'d', 'c'}, {'d', 'e'}, {'c', 'f'}, {'e', 'f'}};
  for (const auto v : vertices) {
    g.addVertex(v);
  }

  for (const auto e : edges) {
    g.addEdge(e.first, e.second);
  }
  g.print();

  auto out = dfsWithStack(g.get());
  // dfs(g.get(), 'h');
}

void testBst() {
  constexpr bool directed = true;
  Graph<char> g(directed);
  char vertices[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
  std::vector<std::pair<char, char>> edges{{'d', 'b'}, {'b', 'a'}, {'b', 'c'}, {'d', 'f'},
                                           {'f', 'e'}, {'f', 'h'}, {'h', 'g'}, {'h', 'i'}};

  for (const auto e : edges) {
    g.addEdge(e.first, e.second);
  }

  auto out = dfsWithStack(g.get());
}

void testLine() {
  constexpr bool directed = true;
  Graph<char> g(directed);
  char vertices[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
  std::vector<std::pair<char, char>> edges{{'a', 'b'}, {'b', 'c'}, {'c', 'd'}, {'d', 'e'},
                                           {'e', 'f'}, {'f', 'g'}, {'g', 'h'}, {'h', 'i'}};

  for (const auto e : edges) {
    g.addEdge(e.first, e.second);
  }

  auto out = dfsWithStack(g.get());
  std::cout << "out: " << out << "\n";
}

void testCyclicGraph() {
  constexpr bool directed = true;
  Graph<char> g(directed);
  char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F'};
  std::vector<std::pair<char, char>> edges{{'A', 'B'}, {'B', 'C'}, {'C', 'E'}, {'E', 'D'}, {'D', 'B'}, {'E', 'F'}};
  /**
   * A -> B -> C -> E -> F
   *      ^         |
   *      |
   *      -- D <-  |
   */
  for (const auto e : edges) {
    g.addEdge(e.first, e.second);
  }

  // In a cyclic graph, the order of finishing vertices is no longer as a DAG.
  // Vertex C is finished vertex B even though there is an edge from B to C.
  auto out = dfsWithStack(g.get());
  std::cout << "out: " << out << "\n";
}

int main() {
  testCyclicGraph();
  return 0;
}
