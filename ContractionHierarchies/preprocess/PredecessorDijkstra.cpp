//
// Created by Luca Massei on 16/2/2024.
//
#include "PredecessorDijkstra.h++"

PredecessorDijkstra::PredecessorDijkstra(int nodeQty) {
    distPredecDijk.resize(nodeQty, Constants::INF);
    visitPredecDijk.resize(nodeQty, false);
}

void PredecessorDijkstra::resetPredecDijkMembers() {
    int count = 0;
    while(!worksetPredecDijk.empty()) {
        count++;
        int node = worksetPredecDijk.front();
        worksetPredecDijk.pop();
        distPredecDijk[node] = Constants::INF;
        visitPredecDijk[node] = false;
    }
}

void
PredecessorDijkstra::doPredecessorDijkstra(PreprocessGraph& preprocessGraph, int predecStartNode, int contractedNode,
                                           int startEndEdgeWeight, int distanceLimit, TypeDefsCH::SucMap &contractedNodeSucs,
                                                                                TypeDefsCH::WitnessMap &witnessPaths) {
    TypeDefsCH::EdgePrQueue queue;
    queue.push( std::make_pair(0, predecStartNode ) );
    distPredecDijk[predecStartNode] = 0;
    visitPredecDijk[predecStartNode] = true;
    worksetPredecDijk.push(predecStartNode);

    while ( !queue.empty() ) {
        TypeDefsCH::QueueEdge topEdgeNode = queue.top();
        if (topEdgeNode.first > distanceLimit)
            break;

        int topNode = topEdgeNode.second;
        queue.pop();

        for (const Edge& edge : preprocessGraph.getOutgoingEdges()[topNode]) {
            int nextNode = edge.nodeTo, weight = edge.weight;

            if ((predecStartNode == nextNode) || (contractedNode == nextNode))
                continue;

            if (distPredecDijk[nextNode] > distPredecDijk[topNode] + weight) {

                distPredecDijk[nextNode] = distPredecDijk[topNode] + weight;

                if (!visitPredecDijk[nextNode]) {
                    visitPredecDijk[nextNode] = true;
                    worksetPredecDijk.push(nextNode);
                }

                queue.push( std::make_pair(distPredecDijk[nextNode], nextNode ) );
            }

            if (contractedNodeSucs.find(nextNode) != contractedNodeSucs.end()) {
                // nextNode is a successor node of contractedNode (i.e. they share an edge of some weight)
                int contractedNextEdgeWeight = contractedNodeSucs[nextNode];

                if ((startEndEdgeWeight + contractedNextEdgeWeight) >= distPredecDijk[nextNode]) {
                    witnessPaths[predecStartNode][nextNode] = distPredecDijk[nextNode];
                }
            }
        }
    }
    resetPredecDijkMembers();
}