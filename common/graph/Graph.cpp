//
// Created by Luca Massei on 16/2/2024.
//
#include "Graph.h++"

Graph::Graph(int nodeQty) : Graph(nodeQty, 0) {}

Graph::Graph(int nodeQty, int expectedEdgeQty) : nodeQty(nodeQty), expectedEdgeQty(expectedEdgeQty) {
    resizeAllMembers();
}

Graph::~Graph() {}

void Graph::deletePair(NodeList& list, int value) {
    list.remove_if([value](const Edge& edge) { return edge.nodeTo == value; });
}

void Graph::deleteNode(int node) {
    for (auto iter = outgoingEdges[node].begin(); iter != outgoingEdges[node].end(); ++iter) {
        Edge edge = *iter;
        int nodeTo = edge.nodeTo;
        deletePair(incomingEdges[nodeTo], node);
        if (willPrintNodeDeletionMsg) { printf("                                               deleting %d from •incoming•[%d]  {%d}\n", node + 1, nodeTo + 1, edge.weight); }
    }

    for (auto iter = incomingEdges[node].begin(); iter != incomingEdges[node].end(); ++iter) {
        Edge edge = *iter;
        int nodeFrom = edge.nodeTo;
        deletePair(outgoingEdges[nodeFrom], node);
        if (willPrintNodeDeletionMsg) { printf("                                               deleting %d from ºoutgoingº[%d]  {%d}\n", node + 1, nodeFrom + 1, edge.weight); }
    }
}

void Graph::resizeAllMembers() {
    outgoingEdges.resize(nodeQty);
    incomingEdges.resize(nodeQty);
}

void Graph::addEdgeToList(NodeList& list, int neighbourNode, int weight) {
    for (auto& edge : list) {
        if (edge.nodeTo == neighbourNode) {
            if (edge.weight > weight)
                edge.weight = weight;
            return;
        }
    }
    Edge edge {neighbourNode, weight};
    list.push_back(edge);
}

void Graph::addEdge(int startNode, int endNode, int weight) {
    addEdgeToList(outgoingEdges[startNode], endNode, weight);
    addEdgeToList(incomingEdges[endNode], startNode, weight);
    edgeQty += 1;
}

Graph::AdjacencyList& Graph::getOutgoingEdges() {
    return outgoingEdges;
}

Graph::AdjacencyList& Graph::getIncomingEdges() {
    return incomingEdges;
}

// Const reference for read-only access
const Graph::AdjacencyList& Graph::getOutgoingEdgesReadOnly() const {
    return outgoingEdges;
}

const Graph::AdjacencyList& Graph::getIncomingEdgesReadOnly() const {
    return incomingEdges;
}

int Graph::getNodeQty() const {
    return nodeQty;
}

int Graph::getEdgeQty() const {
    return expectedEdgeQty;
}

int Graph::getExpectedEdgeQty() const {
    return expectedEdgeQty;
}