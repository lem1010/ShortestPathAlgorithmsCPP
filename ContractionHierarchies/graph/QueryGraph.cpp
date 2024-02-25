//
// Created by Luca Massei on 17/2/2024.
//

#include "QueryGraph.h++"

QueryGraph::QueryGraph(const Graph& graph) : Graph(graph) {
    rank.resize(graph.getNodeQty(), -1);
}

std::vector<int>& QueryGraph::getRank() {
    return rank;
}

const std::vector<int>& QueryGraph::getRankReadOnly() const {
    return rank;
}