//
// Created by Luca Massei on 16/2/2024.
//
#include "GraphPreprocessor.h++"

GraphPreprocessor::GraphPreprocessor(int nodeQty) : witnessPathFinder(nodeQty) {}

void GraphPreprocessor::loadPreprocessQueue(PreprocessGraph& preprocessGraph, TypeDefsCH::ImpoPrQueue& queue) {
    for (int node = 0; node < preprocessGraph.getNodeQty(); node++) {
        int shortcutCounter = 0;
        witnessPathFinder.doWitnessSearch(preprocessGraph, node, shortcutCounter, true);

        int out = preprocessGraph.getOutgoingEdges()[node].size();
        int in = preprocessGraph.getIncomingEdges()[node].size();
        int nodeImportance = shortcutCounter - in - out;

        preprocessGraph.getImportance()[node] = nodeImportance;
        TypeDefsCH::ImpoNodePair impoNodePair{nodeImportance, node};
        queue.push(impoNodePair);
    }
}

void GraphPreprocessor::preprocess(PreprocessGraph& preprocessGraph, QueryGraph& queryGraph) {
    TypeDefsCH::ImpoPrQueue queue;
    loadPreprocessQueue(preprocessGraph, queue);

    while (!queue.empty()) {
        // For observing time taken to contract nodes at queue size multiples of 500 (if already in test mode)
        if ( isRunningPreprocessSpeedTest() && ((queue.size() % StressTestSettingsCH::PRINT_AT_QUEUE_SIZE_MULTIPLES_OF) == 0) )
            printQueueTimes(preprocessGraph, queue);

        if (isRunningPreprocessSpeedTest())
            timerPtr->startTimer();

        // Obtaining node at the front of queue to potentially contract next
        int topNode = queue.top().second;

        queue.pop();

        // Recompute topNode's shortcut cover since the contraction of other nodes may have changed its true value
        updateNodeImportance(preprocessGraph, topNode);

        int topNodeImpo = getUpdatedNodeImportance(preprocessGraph, topNode);

        doLazyUpdate(preprocessGraph, queue);

        // Checking if topNode is still the least important node after the lazy update(s)
        if (topNodeImpo > queue.top().first) // Push topNode back to queue since it's no longer the least important node
            queue.push(TypeDefsCH::ImpoNodePair{topNodeImpo, topNode});

        else // Otherwise, we can contract topNode if it is still the least important node
            contractNode(preprocessGraph, queryGraph, topNode);

        if (isRunningPreprocessSpeedTest())
            timerPtr->stopTimer();
    }

    finalise(queryGraph);
    preprocessComplete = true;
}

/*
 * Contracting nodes potentially influences the 'true' node importance values.
 * Lazy updating is a way to update some of the nodes' importance values to achieve
 * a more accurate/useful node ordering for contracting nodes.
 *
 * Lazy updating simply updates the importance of the next node(s) in the queue and adds
 * them back to the queue. After doing the lazy updates, the current node that we are trying
 * to contract will have its importance compared to that of the node at the front of the queue,
 * and if the current node still has the lowest importance, it will be contracted.
 */
void GraphPreprocessor::doLazyUpdate(PreprocessGraph &preprocessGraph, TypeDefsCH::ImpoPrQueue &queue) {
    int nextTopNode = queue.top().second;

    queue.pop();

    updateNodeImportance(preprocessGraph, nextTopNode);

    queue.push({getUpdatedNodeImportance(preprocessGraph, nextTopNode), nextTopNode});
}

// Runs updates to any heuristic metrics where applicable
void GraphPreprocessor::updateNodeImportance(PreprocessGraph& preprocessGraph, int& node) {
    computeShortcutCover(preprocessGraph, node);
}

int GraphPreprocessor::getUpdatedNodeImportance(PreprocessGraph& preprocessGraph, int& node) {
    return preprocessGraph.getShortcutCover()[node]
            + preprocessGraph.getNodeLevel()[node]
            + preprocessGraph.getContractedNeighboursQty()[node]
            + preprocessGraph.getImportance()[node];
}

void GraphPreprocessor::contractNode(PreprocessGraph &preprocessGraph, QueryGraph &queryGraph, int topNode) {
    Shortcuts shortcuts;
    int dummyShortcutCounter = 0;

    witnessPathFinder.doWitnessSearch(preprocessGraph, topNode, dummyShortcutCounter, false, shortcuts);

    // Mark topNode as contracted
    preprocessGraph.getContractedStatus()[topNode] = 1;
    nodesContracted++;

    // Setting topNode as the 'nodesContracted'-th contracted node for the ordering.
    queryGraph.getRank()[topNode] = nodesContracted;

    computeNodeLevel(preprocessGraph, topNode);
    computeContractedNeighbours(preprocessGraph, topNode);

    preprocessGraph.deleteNode(topNode);

    addShortcuts(shortcuts, {&preprocessGraph, &queryGraph});
}

void GraphPreprocessor::computeShortcutCover(PreprocessGraph& preprocessGraph, int node) {
    preprocessGraph.getShortcutCover()[node] = 0;

    for (const Edge& edge : preprocessGraph.getIncomingEdges()[node]) {

        int predecNode = edge.nodeTo;

        int predecNodeOutEdgeQty = preprocessGraph.getOutgoingEdges()[predecNode].size();

        if (predecNodeOutEdgeQty == 1)
            preprocessGraph.getShortcutCover()[node] += 1;

    }
}

void GraphPreprocessor::computeNodeLevel(PreprocessGraph& preprocessGraph, int node) {
    for (const Edge& edge : preprocessGraph.getOutgoingEdges()[node]) {

        int sucNode = edge.nodeTo;

        preprocessGraph.getNodeLevel()[sucNode] = std::max(preprocessGraph.getNodeLevel()[sucNode],
                                                               preprocessGraph.getNodeLevel()[node] + 1);
    }

    for (const Edge& edge : preprocessGraph.getIncomingEdges()[node]) {

        int predecNode = edge.nodeTo;

        preprocessGraph.getNodeLevel()[predecNode] = std::max(preprocessGraph.getNodeLevel()[predecNode],
                                                             preprocessGraph.getNodeLevel()[node] + 1);
    }
}

void GraphPreprocessor::computeContractedNeighbours(PreprocessGraph& preprocessGraph, int node) {
    for (const Edge& edge : preprocessGraph.getOutgoingEdges()[node]) {

        int sucNode = edge.nodeTo;

        preprocessGraph.getContractedNeighboursQty()[sucNode] += 1;
    }

    for (const Edge& edge : preprocessGraph.getIncomingEdges()[node]) {

        int predecNode = edge.nodeTo;

        preprocessGraph.getContractedNeighboursQty()[predecNode] += 1;
    }
}

// Adds all the shortcuts following a node contraction
void GraphPreprocessor::addShortcuts(Shortcuts& shortcuts, const std::vector<Graph*>& graphs) {
    // Add neighbors and shortcut cover heuristics
    for (Shortcut shortcut : shortcuts) {
        for (Graph* graph : graphs)
            graph->addEdge(shortcut.from, shortcut.to, shortcut.cost);
    }
}

// Remove any redundant edges for each node's outgoing/incoming edge lists
void GraphPreprocessor::finalise(QueryGraph& queryGraph) {
    for (int node = 0; node < queryGraph.getNodeQty(); node++) {
        eraseRedundantEdges(queryGraph.getOutgoingEdges()[node], queryGraph.getRank(), node);
        eraseRedundantEdges(queryGraph.getIncomingEdges()[node], queryGraph.getRank(), node);
    }
}

void GraphPreprocessor::eraseRedundantEdges(std::list<Edge>& edges, const std::vector<int>& rank, int node) {
    for (auto iter = edges.begin(); iter != edges.end(); ) {

        int sucNode = iter->nodeTo;

        if (rank[node] > rank[sucNode])
            iter = edges.erase(iter);
        else
            ++iter;
    }
}

bool GraphPreprocessor::isRunningPreprocessSpeedTest() {
    return timerPtr != nullptr;
}

void GraphPreprocessor::setTimerPtr(Timer& timer) {
    timerPtr = &timer;
}

void GraphPreprocessor::resetTimerPtr() {
    timerPtr = nullptr;
}

void GraphPreprocessor::printQueueTimes(const PreprocessGraph& preprocessGraph, const TypeDefsCH::ImpoPrQueue& queue) {
    /*
     * ' { %d } ' := The importance of the node at the front of the queue.
     * ' out ' := The number of outgoing edges of the node at the front of the queue.
     * ' in ' := The number of incoming edges of the node at the front of the queue.
     */
    printf("queue.size = %lu,   shortcut's_added = %d,   { %d },   out = %lu,   in = %lu,   "
           "time_accum = %.3f\n", queue.size(), preprocessGraph.getShortcutsAdded(), queue.top().first,
           preprocessGraph.getOutgoingEdgesReadOnly()[queue.top().second].size(),
           preprocessGraph.getIncomingEdgesReadOnly()[queue.top().second].size(),
           timerPtr->getTotalTime());
}

bool GraphPreprocessor::hasCompletedPreprocess() const {
    return preprocessComplete;
}