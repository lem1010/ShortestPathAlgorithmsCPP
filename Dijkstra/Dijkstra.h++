//
// Created by Luca Massei on 10/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_DIJKSTRA_H
#define SHORTESTPATHALGORITHMSCPP_DIJKSTRA_H

#include <vector>
#include <queue>
#include "../common/graph/Graph.h++"
#include "../common/ShortestPathAlgorithm.h++"
#include "../common/utility/Constants.h++" // For infinity constant

class Dijkstra : public ShortestPathAlgorithm {
private:
    typedef std::pair<int,int> DistNodePair; // Priority queue type := < distance to source, queued node >

    std::vector<int> distances;
public:
    Dijkstra(const Graph& graph);

    void dijkstra(int startNode);
    int computeDistance(int startNode, int endNode) override;
};

#endif //SHORTESTPATHALGORITHMSCPP_DIJKSTRA_H
