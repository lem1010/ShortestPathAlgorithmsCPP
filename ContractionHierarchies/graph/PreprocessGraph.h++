//
// Created by Luca Massei on 10/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_PREPROCESSGRAPH_H
#define SHORTESTPATHALGORITHMSCPP_PREPROCESSGRAPH_H

#include <vector>
#include <algorithm> // For std::max, std::min

#include "../../common/graph/Graph.h++"

class PreprocessGraph : public Graph {
private:
    // Heuristics
    std::vector<int> nodeLevel;
    std::vector<int> shortcutCover;
    std::vector<int> contractedNeighboursQty;
    std::vector<int> importance; // Contains nodes' importance as the sum of heuristic metrics
    std::vector<int> contractedStatus; // Contraction status of node := 1 if contractedStatus and 0 otherwise
    std::vector<int> maxOutEdge; // Stores max out-going edge of each node as (cost, startNode)

    int shortcutsAdded = 0;

public:
    PreprocessGraph(const Graph& graph);

    void addEdge(int startNode, int endNode, int weight) override;
    void updateMaxOutEdgeForNode(int node);
    std::vector<int>& getMaxOutEdge();
    std::vector<int>& getContractedStatus();
    std::vector<int>& getNodeLevel();
    std::vector<int>& getShortcutCover();
    std::vector<int>& getContractedNeighboursQty();
    std::vector<int>& getImportance();
    int getShortcutsAdded() const;
};
#endif //SHORTESTPATHALGORITHMSCPP_PREPROCESSGRAPH_H
