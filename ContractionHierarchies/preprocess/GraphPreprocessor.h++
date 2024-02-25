//
// Created by Luca Massei on 16/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_GRAPHPREPROCESSOR_H
#define SHORTESTPATHALGORITHMSCPP_GRAPHPREPROCESSOR_H

#include <utility>
#include <queue>

#include "WitnessPathFinder.h++"
#include "../graph/PreprocessGraph.h++"
#include "../graph/QueryGraph.h++"
#include "../../common/utility/Timer.h++"
#include "../../tests/stress-tests/ContractionHierarchies/options/StressTestSettingsCH.h++"

class GraphPreprocessor {
private:
    int nodesContracted = 0;
    bool preprocessComplete = false;
    WitnessPathFinder witnessPathFinder;
    Timer* timerPtr = nullptr; // For measuring speed of preprocessing phase in test mode

    void finalise(QueryGraph& queryGraph);
    void eraseRedundantEdges(std::list<Edge>& edges, const std::vector<int>& rank, int node);
    void loadPreprocessQueue(PreprocessGraph &preprocessGraph, TypeDefsCH::ImpoPrQueue &queue);
    void addShortcuts(Shortcuts& shortcuts, const std::vector<Graph*>& graphs);
    void contractNode(PreprocessGraph &preprocessGraph, QueryGraph &queryGraph, int topNode);
    void computeContractedNeighbours(PreprocessGraph& preprocessGraph, int node);
    void computeNodeLevel(PreprocessGraph& preprocessGraph, int node);
    void computeShortcutCover(PreprocessGraph& preprocessGraph, int node);
    void doLazyUpdate(PreprocessGraph &preprocessGraph, TypeDefsCH::ImpoPrQueue &queue);
    void updateNodeImportance(PreprocessGraph& preprocessGraph, int& node);
    int getUpdatedNodeImportance(PreprocessGraph& preprocessGraph, int& node);
    bool isRunningPreprocessSpeedTest();
    void printQueueTimes(const PreprocessGraph& preprocessGraph, const TypeDefsCH::ImpoPrQueue& queue);
public:
    GraphPreprocessor(int nodeQty);

    void preprocess(PreprocessGraph& preprocessGraph, QueryGraph& queryGraph);
    void setTimerPtr(Timer& timer);
    void resetTimerPtr();
    bool hasCompletedPreprocess() const;
};
#endif //SHORTESTPATHALGORITHMSCPP_GRAPHPREPROCESSOR_H
