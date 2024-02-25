//
// Created by Luca Massei on 16/2/2024.
//
#include "WitnessPathFinder.h++"

WitnessPathFinder::WitnessPathFinder(int nodeQty) : predecessorDijkstra(nodeQty) {}

void WitnessPathFinder::doWitnessSearch(PreprocessGraph& preprocessGraph, int node, int& shortcutCounter, bool simulate) {
    Shortcuts dummyShortcuts;
    doWitnessSearch(preprocessGraph, node, shortcutCounter, simulate, dummyShortcuts);
}

void WitnessPathFinder::doWitnessSearch(PreprocessGraph& preprocessGraph, int node, int& shortcutCounter, bool simulate, Shortcuts& shortcuts) {

    if (preprocessGraph.getOutgoingEdges()[node].empty() || preprocessGraph.getIncomingEdges()[node].empty())
        return;

    TypeDefsCH::WitnessMap witnessPaths;
    TypeDefsCH::SucMap nodeSuccessors = computeNodeSuccessors(preprocessGraph, node);

    preprocessGraph.updateMaxOutEdgeForNode(node);

    for (const Edge& edge : preprocessGraph.getIncomingEdges()[node]) {
        int predecNode = edge.nodeTo, predecNodeEdgeWeight = edge.weight;
        int nodeSucEdgeWeightLimit = preprocessGraph.getMaxOutEdge()[node];
        int distanceLimit = nodeSucEdgeWeightLimit + predecNodeEdgeWeight;

        predecessorDijkstra.doPredecessorDijkstra(preprocessGraph, predecNode, node,
                                                  predecNodeEdgeWeight, distanceLimit,
                                                  nodeSuccessors, witnessPaths);

    }
    for (const Edge& outerEdge : preprocessGraph.getIncomingEdges()[node]) {

        int predecNode = outerEdge.nodeTo, predecNodeEdgeWeight = outerEdge.weight;

        for (const Edge& innerEdge : preprocessGraph.getOutgoingEdges()[node]) {

            int sucNode = innerEdge.nodeTo, nodeSucEdgeWeight = innerEdge.weight;

            if (predecNode == sucNode)
                continue;

            if (witnessPaths.find(predecNode) != witnessPaths.end()) { // The key exists in the map
                if (witnessPaths[predecNode].find(sucNode) != witnessPaths[predecNode].end())
                    continue;
            }

            shortcutCounter++;

            if (!simulate) {
                Shortcut sc{predecNode, sucNode, predecNodeEdgeWeight + nodeSucEdgeWeight};
                shortcuts.push_back(sc);
            }
        }
    }
}

TypeDefsCH::SucMap WitnessPathFinder::computeNodeSuccessors(PreprocessGraph& preprocessGraph, int node) {
    TypeDefsCH::SucMap nodeSuccessors;

    for (const Edge& edge : preprocessGraph.getOutgoingEdges()[node]) // Edges to successor nodes
        nodeSuccessors[edge.nodeTo] = edge.weight;

    return nodeSuccessors;
}