//
// Created by Luca Massei on 10/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_CONTRACTIONHIERARCHIES_H
#define SHORTESTPATHALGORITHMSCPP_CONTRACTIONHIERARCHIES_H

#include "../common/ShortestPathAlgorithm.h++"
#include "graph/PreprocessGraph.h++"
#include "graph/QueryGraph.h++"
#include "graph/factory/ContractionHierarchiesGraphFactory.h++" // For graph construction
#include "preprocess/GraphPreprocessor.h++"
#include "../common/utility/Constants.h++" // For infinity constant

class ContractionHierarchies : public ShortestPathAlgorithm {
private:
    static const int SEARCH_DIRECTIONS = 2;
    /* Visited list for bidirectional search. True if visited.
     * visitBidirecSearch[0] - forward search,
     * visitBidirecSearch[1] - backward search. */
    std::vector<TypeDefsCH::VisitList> visitBidirecSearch;

    /* Distance list stores distances to some node v in bidirectional searches, as shown below.
     * distBidirecSearch[0][v] - from source in the forward search,
     * distBidirecSearch[1][v] - from target in the backward search. */
    std::vector<TypeDefsCH::DistList> distBidirecSearch;

    /* Work set stores nodes encountered in bidirectional search so visited and distances lists can be reset. */
    TypeDefsCH::WorkSet worksetBidirecSearch;

    GraphPreprocessor preprocessor;
    PreprocessGraph preprocessGraph;
    QueryGraph queryGraph;

    int estimate = Constants::INF;

    void resetBidirecSearch();
    void relax(int startNode, int endNode, int weight, int side, TypeDefsCH::BidirecSearchQueue& queue);
    void processNextEdge(TypeDefsCH::BidirecSearchQueue &queue, int node, bool willDoForwardSearch);
    void relaxEdgesForSearchDirection(TypeDefsCH::BidirecSearchQueue &queue, int node,
                                      const std::list<Edge> &edgeList, const std::vector<int> &rank);
public:
    ContractionHierarchies(const Graph& graph);

    int computeDistance(int startNode, int endNode) override;

    void enterSpeedTestMode(Timer &timer);
    void exitSpeedTestMode();

    void doPreprocess();
    int getTotalShortcutsAdded() const;
};
#endif //SHORTESTPATHALGORITHMSCPP_CONTRACTIONHIERARCHIES_H
