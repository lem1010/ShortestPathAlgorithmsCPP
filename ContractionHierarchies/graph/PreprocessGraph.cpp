//
// Created by Luca Massei on 16/2/2024.
//
#include "PreprocessGraph.h++"

PreprocessGraph::PreprocessGraph(const Graph& graph) : Graph(graph) {
    maxOutEdge.resize(graph.getNodeQty());
    contractedStatus.resize(graph.getNodeQty(), 0);
    nodeLevel.resize(graph.getNodeQty(), 0);
    shortcutCover.resize(graph.getNodeQty(), 0);
    contractedNeighboursQty.resize(graph.getNodeQty(), 0);
    importance.resize(graph.getNodeQty(), 0);
}

void PreprocessGraph::addEdge(int startNode, int endNode, int weight) {
    Graph::addEdge(startNode, endNode, weight);
    shortcutsAdded++;
}

void PreprocessGraph::updateMaxOutEdgeForNode(int node) {
    int initMaxOutEdge = 0;
    for (const Edge& edge : getOutgoingEdges()[node])
        initMaxOutEdge = std::max(initMaxOutEdge, edge.weight);
    maxOutEdge[node] = initMaxOutEdge;
}

std::vector<int>& PreprocessGraph::getMaxOutEdge() {
    return maxOutEdge;
};

std::vector<int>& PreprocessGraph::getContractedStatus() {
    return contractedStatus;
}

std::vector<int>& PreprocessGraph::getNodeLevel() {
    return nodeLevel;
}

std::vector<int>& PreprocessGraph::getShortcutCover() {
    return shortcutCover;
}

std::vector<int>& PreprocessGraph::getContractedNeighboursQty() {
    return contractedNeighboursQty;
}

std::vector<int>& PreprocessGraph::getImportance() {
    return importance;
}

int PreprocessGraph::getShortcutsAdded() const {
    return shortcutsAdded;
}