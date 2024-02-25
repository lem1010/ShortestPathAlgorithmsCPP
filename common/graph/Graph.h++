//
// Created by Luca Massei on 9/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_GRAPH_H
#define SHORTESTPATHALGORITHMSCPP_GRAPH_H

#include <vector>
#include <list>
#include <iostream>

#include "../../ContractionHierarchies/graph/structs/Shortcut.h++"
#include "structs/Edge.h++"

class Graph {
public:
    typedef std::list<Edge> NodeList;
    typedef std::vector<NodeList> AdjacencyList;

    Graph(int nodeQty);
    Graph(int nodeQty, int expectedEdgeQty);

    virtual ~Graph();

    virtual void addEdge(int startNode, int endNode, int weight);
    void deleteNode(int node);
    AdjacencyList& getOutgoingEdges();
    AdjacencyList& getIncomingEdges();
    const AdjacencyList& getOutgoingEdgesReadOnly() const;
    const AdjacencyList& getIncomingEdgesReadOnly() const;
    int getNodeQty() const;
    int getEdgeQty() const;
    int getExpectedEdgeQty() const;
private:
    int nodeQty = 0; // Number of nodes
    int edgeQty = 0; // True number of edges
    int expectedEdgeQty = 0; // Expected number of edges

    bool willPrintNodeDeletionMsg = false;

    AdjacencyList outgoingEdges; // adjList[startNode] = [{endNode, cost}, ...]
    AdjacencyList incomingEdges; // adjList[endNode] = [{startNode, cost}, ...]

    void deletePair(NodeList& list, int value);
    void resizeAllMembers();
    void addEdgeToList(NodeList& list, int neighbourNode, int weight);
};

#endif //SHORTESTPATHALGORITHMSCPP_GRAPH_H
