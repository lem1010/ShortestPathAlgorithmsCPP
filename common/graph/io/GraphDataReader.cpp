//
// Created by Luca Massei on 16/2/2024.
//
#include "GraphDataReader.h++"

std::pair<int, int> GraphDataReader::readNodeAndEdgeQtyLine() {
    int nodeQtyInput, edgeQtyInput;
    getStream() >> nodeQtyInput >> edgeQtyInput;
    return std::make_pair(nodeQtyInput, edgeQtyInput);
}

Trio GraphDataReader::readEdgeDataLine() {
    int startNodeInput, endNodeInput, weightInput;
    getStream() >> startNodeInput >> endNodeInput >> weightInput;
    return Trio(startNodeInput, endNodeInput, weightInput);
}

void GraphDataReader::storePrevLineInput(int startNode, int endNode, int weight) {
    prevInputStartNode = startNode;
    prevInputEndNode = endNode;
    prevInputWeight = weight;
}

bool GraphDataReader::skipEdgeInput(int startNode, int endNode, int weight) {
    // If input edge is the same as the previous one but directionally in reverse, skip it
    if (startNode == prevInputEndNode && endNode == prevInputStartNode && weight == prevInputWeight)
        return true;
        // If input edge is an exact duplicate of the last edge read, skip it
    else if (startNode == prevInputStartNode && endNode == prevInputEndNode && weight == prevInputWeight)
        return true;
    return false;
}