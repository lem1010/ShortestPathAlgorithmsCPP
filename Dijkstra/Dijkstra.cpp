//
// Created by Luca Massei on 16/2/2024.
//
#include "Dijkstra.h++"

Dijkstra::Dijkstra(const Graph& graph) : ShortestPathAlgorithm(graph) {
    distances.resize(graph.getNodeQty(), Constants::INF);
}

void Dijkstra::dijkstra(int startNode) {
    std::priority_queue<DistNodePair, std::vector<DistNodePair>, std::greater<DistNodePair> > queue;
    distances[startNode] = 0;
    queue.push(std::make_pair(0, startNode));
    while (!queue.empty()) {
        DistNodePair queueFront = queue.top();
        int node = queueFront.second;
        queue.pop();
        for (auto& edge : getGraph().getOutgoingEdgesReadOnly()[node]) {
            if (distances[edge.nodeTo] > distances[node] + edge.weight) {
                distances[edge.nodeTo] = distances[node] + edge.weight;
                queue.push(std::make_pair(distances[edge.nodeTo], edge.nodeTo));
            }
        }
    }
}

int Dijkstra::computeDistance(int startNode, int endNode) {
    distances.assign(distances.size(), Constants::INF);  // reset distances before each query
    dijkstra(startNode);
    return (distances[endNode] == Constants::INF) ? -1 : distances[endNode];
}