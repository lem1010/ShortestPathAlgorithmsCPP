//
// Created by Luca Massei on 15/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_PREDECESSORDIJKSTRA_H
#define SHORTESTPATHALGORITHMSCPP_PREDECESSORDIJKSTRA_H

#include "../utility/TypeDefsCH.h++"
#include "../../common/graph/structs/Edge.h++"
#include "../graph/PreprocessGraph.h++"
#include "../../common/utility/Constants.h++" // For infinity constant

class PredecessorDijkstra {
private:
    // Distances for predecessor dijkstra search
    TypeDefsCH::DistList distPredecDijk;
    // Visited list for predecessor dijkstra search
    TypeDefsCH::VisitList visitPredecDijk;
    // Workset for predecessor dijkstra search
    TypeDefsCH::WorkSet worksetPredecDijk;

    void resetPredecDijkMembers();
public:
    PredecessorDijkstra(int nodeQty);

    void doPredecessorDijkstra(PreprocessGraph& preprocessGraph,
                               int predecStartNode,
                               int contractedNode,
                               int startEndEdgeWeight,
                               int distanceLimit,
                               TypeDefsCH::SucMap& contractedNodeSucs,
                               TypeDefsCH::WitnessMap& witnessPaths);
};
#endif //SHORTESTPATHALGORITHMSCPP_PREDECESSORDIJKSTRA_H
