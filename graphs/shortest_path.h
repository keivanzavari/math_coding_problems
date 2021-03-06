#pragma once
#include <limits>
#include <queue>

#include "weighted_graph_definitions.h"

template <typename N, typename W>
struct ShortestPath {
  N from;
  N to;
  std::vector<N> vertices;
  W distance;
};

/**
 *  INITIALIZE-SINGLE-SOURCE(G, start)
 *    for each vertex v in G
 *      v.distance = inf
 *      v.parent = NIL
 *    start.distance = 0
 *
 */
template <typename N, typename W>
void initialize(const AdjList<N, W>& graph, N start, std::unordered_map<N, W>& distances,
                std::unordered_map<N, N>& parents) {
  distances.clear();
  parents.clear();
  for (const auto& el : graph) {
    distances[el.first] = std::numeric_limits<W>::max();
    parents[el.first] = N(0);
  }
  distances[start] = W(0);
}

/**
 * @brief
 *
 * @tparam N template parameter for vertex type
 * @tparam W template parameter for weight type
 * @param graph adjacency list representing a directed weighted graph
 * @param start start vertex for dijkstra algorithm
 * @param distances a dictionary of all the shortest distances from the start vertex
 * @param parents a dictionary of all the parents for the shortest path starting from start vertex
 *
 *
 * The cost of this algorithm is everything since it determines which node will come out of the priority queue.
 *
 *
 * In greedy best search, instead of distance we use a heuristic function which is the distance to the target.
 * In A*, this idea is improved and we use this heuristic function + the distance so far.
 */
template <typename N, typename W>
void dijkstra(const AdjList<N, W>& graph, const N start, std::unordered_map<N, W>& distances,
              std::unordered_map<N, N>& parents) {
  // std::vector<N> determined{};
  initialize(graph, start, distances, parents);

  std::pair<W, N> node_distance;
  auto compare = [](const std::pair<W, N>& left, const std::pair<W, N>& right) { return left.first > right.first; };
  std::priority_queue<std::pair<W, N>, std::vector<std::pair<W, N>>, decltype(compare)> min_heap(compare);
  min_heap.push({W(0), start});
  while (!min_heap.empty()) {
    // std::cout << "determined: " << determined << "\n";
    auto pair = min_heap.top();
    auto u = pair.second;
    min_heap.pop();
    // determined.push_back(u);
    for (const auto& edge : graph.at(u)) {
      auto v = edge.to;
      auto w = edge.weight.value();
      /**
       * Relax(u,v,w)
       * if v.distance > u.distance + w(u,v)
       *   v.distance = u.distance + w(u,v)
       *   v.parent = u
       */
      if (distances.at(v) > distances.at(u) + w) {
        distances[v] = distances.at(u) + w;
        parents[v] = u;
        min_heap.push({distances[v], v});
      }
    }
  }

  std::cout << "distances: " << distances << "\n";
}

template <typename N, typename W>
ShortestPath<N, W> getShortestPath(const AdjList<N, W>& graph, N from, N to) {
  std::unordered_map<N, W> distances;
  std::unordered_map<N, N> parents;
  dijkstra(graph, from, distances, parents);
  if (parents.empty() || distances.empty()) {
    throw std::runtime_error("Failed to find a path!");
  }
  ShortestPath<N, W> shortest_path;
  shortest_path.from = from;
  shortest_path.to = to;
  shortest_path.distance = distances.at(to);
  auto vertex = to;
  while (vertex != from) {
    shortest_path.vertices.push_back(vertex);
    vertex = parents.at(vertex);
  }
  shortest_path.vertices.push_back(vertex);
  return shortest_path;
}
// Belman-Ford
