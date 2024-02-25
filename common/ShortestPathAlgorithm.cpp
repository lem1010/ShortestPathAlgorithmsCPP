//
// Created by Luca Massei on 16/2/2024.
//
#include "ShortestPathAlgorithm.h++"

ShortestPathAlgorithm::ShortestPathAlgorithm(const Graph& graph) : graph(graph) {}

const Graph& ShortestPathAlgorithm::getGraph() const {
    return graph;
}

void ShortestPathAlgorithm::enterTestMode() {
    testMode = true;
}

void ShortestPathAlgorithm::exitTestMode() {
    testMode = false;
}

bool ShortestPathAlgorithm::isInTestMode() const {
    return testMode;
}