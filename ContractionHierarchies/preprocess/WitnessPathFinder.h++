//
// Created by Luca Massei on 15/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_WITNESSPATHFINDER_H
#define SHORTESTPATHALGORITHMSCPP_WITNESSPATHFINDER_H

#include "PredecessorDijkstra.h++"
#include "../graph/structs/Shortcut.h++" // For Shortcuts
#include "../graph/PreprocessGraph.h++"
#include "../utility/TypeDefsCH.h++"

class WitnessPathFinder {
private:
    PredecessorDijkstra predecessorDijkstra;
    TypeDefsCH::SucMap computeNodeSuccessors(PreprocessGraph& preprocessGraph, int node);
public:
    WitnessPathFinder(int nodeQty);

    void doWitnessSearch(PreprocessGraph& preprocessGraph, int node, int& shortcutCounter, bool simulate);
    void doWitnessSearch(PreprocessGraph& preprocessGraph, int node, int& shortcutCounter, bool simulate, Shortcuts& shortcuts);

};
#endif //SHORTESTPATHALGORITHMSCPP_WITNESSPATHFINDER_H
