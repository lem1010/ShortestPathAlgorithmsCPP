//
// Created by Luca Massei on 16/2/2024.
//
#include "ContractionHierarchies.h++"

ContractionHierarchies::ContractionHierarchies(const Graph& graph) :
    ShortestPathAlgorithm(graph),
    preprocessGraph(ContractionHierarchiesGraphFactory::makePreprocessGraph(graph) ),
    queryGraph(ContractionHierarchiesGraphFactory::makeQueryGraph(graph)), preprocessor(graph.getNodeQty()),
    distBidirecSearch(SEARCH_DIRECTIONS, std::vector<int>(graph.getNodeQty(), Constants::INF)),
    visitBidirecSearch(SEARCH_DIRECTIONS, std::vector<bool>(graph.getNodeQty(), false)) {

}

void ContractionHierarchies::enterSpeedTestMode(Timer& timer) {
    ShortestPathAlgorithm::enterTestMode();
    preprocessor.setTimerPtr(timer);
}

void ContractionHierarchies::exitSpeedTestMode() {
    ShortestPathAlgorithm::exitTestMode();
    preprocessor.resetTimerPtr();
}

void ContractionHierarchies::resetBidirecSearch() {
    while (!worksetBidirecSearch.empty()) {
        int node = worksetBidirecSearch.front();
        worksetBidirecSearch.pop();
        distBidirecSearch[0][node] = distBidirecSearch[1][node] = Constants::INF;
        visitBidirecSearch[0][node] = visitBidirecSearch[1][node] = false;
    }
}

void ContractionHierarchies::relax(int startNode, int endNode, int weight, int side, TypeDefsCH::BidirecSearchQueue& queue) {
    if (distBidirecSearch[side][endNode] > (distBidirecSearch[side][startNode] + weight) ) {

        distBidirecSearch[side][endNode] = distBidirecSearch[side][startNode] + weight;

        queue[side].push(std::make_pair(distBidirecSearch[side][endNode], endNode) );

        if ( !(visitBidirecSearch[0][endNode] || visitBidirecSearch[1][endNode]) )
            worksetBidirecSearch.push(endNode);

        if (!visitBidirecSearch[side][endNode])
            visitBidirecSearch[side][endNode] = true;
    }
}

void ContractionHierarchies::processNextEdge(TypeDefsCH::BidirecSearchQueue &queue, int node, bool willDoForwardSearch) {
    if (willDoForwardSearch) {

        relaxEdgesForSearchDirection(queue, node, queryGraph.getOutgoingEdgesReadOnly()[node],
                                                                                    queryGraph.getRankReadOnly());

        for (const Edge& edge : queryGraph.getOutgoingEdges()[node]) {

            int nextNode = edge.nodeTo;

            int weight = edge.weight;

            if (queryGraph.getRank()[nextNode] > queryGraph.getRank()[node])
                relax(node, nextNode, weight, 0, queue);
        }
    }

    else {
        for (const Edge& edge : queryGraph.getIncomingEdges()[node]) {

            int nextNode = edge.nodeTo;

            int weight = edge.weight;

            if (queryGraph.getRank()[nextNode] > queryGraph.getRank()[node])
                relax(node, nextNode, weight, 1, queue);
        }
    }
}

void ContractionHierarchies::relaxEdgesForSearchDirection(TypeDefsCH::BidirecSearchQueue &queue, int node,
                                                                            const std::list<Edge> &edgeList,
                                                                                        const std::vector<int> &rank) {
    for (const Edge& edge : edgeList) {

        int nextNode = edge.nodeTo;

        int weight = edge.weight;

        if (rank[nextNode] > rank[node])
            relax(node, nextNode, weight, 0, queue);
    }
}

int ContractionHierarchies::computeDistance(int startNode, int endNode) {
    if (!preprocessor.hasCompletedPreprocess())
        preprocessor.preprocess(preprocessGraph, queryGraph);

    // Bidirectional search queues, queue[0] - forward search, queue[1] - backward search
    TypeDefsCH::BidirecSearchQueue queue;
    queue.resize(2);

    estimate = Constants::INF;

    distBidirecSearch[0][startNode] = 0;
    distBidirecSearch[1][endNode] = 0;
    visitBidirecSearch[0][startNode] = true;
    visitBidirecSearch[1][endNode] = true;

    TypeDefsCH::QueueEdge startQueueEdge {0, startNode};
    TypeDefsCH::QueueEdge endQueueEdge {0, endNode};

    queue[0].push(startQueueEdge);
    queue[1].push(endQueueEdge);

    worksetBidirecSearch.push(startNode);
    worksetBidirecSearch.push(endNode);

    bool continueForward = true, continueBackwards = true;

    while (!queue[0].empty() || !queue[1].empty() ) {

        bool forwardSearchQueueEmpty = queue[0].empty(), backwardsSearchQueueEmpty = queue[1].empty();

        TypeDefsCH::QueueEdge topQueueEdgeForward;
        TypeDefsCH::QueueEdge topQueueEdgeBackwards;

        int topNodeForward, topNodeBackwards;

        if (!forwardSearchQueueEmpty && continueForward) {

            topQueueEdgeForward = queue[0].top();

            topNodeForward = topQueueEdgeForward.second;

            queue[0].pop();

            if (topQueueEdgeForward.first > estimate)
                continueForward = false;
        }

        if (!backwardsSearchQueueEmpty && continueBackwards) {

            topQueueEdgeBackwards = queue[1].top();

            topNodeBackwards = topQueueEdgeBackwards.second;

            queue[1].pop();

            if (topQueueEdgeBackwards.first > estimate)
                continueBackwards = false;
        }


        if (!forwardSearchQueueEmpty && continueForward) {

            if (topQueueEdgeForward.first <= estimate)
                processNextEdge(queue, topNodeForward, true);

            if (visitBidirecSearch[1][topNodeForward] && ((distBidirecSearch[0][topNodeForward] + distBidirecSearch[1][topNodeForward] ) < estimate ) )
                estimate = distBidirecSearch[0][topNodeForward] + distBidirecSearch[1][topNodeForward];
        }

        if (!backwardsSearchQueueEmpty && continueBackwards) {

            if (topQueueEdgeBackwards.first <= estimate)
                processNextEdge(queue, topNodeBackwards, false);

            if (visitBidirecSearch[0][topNodeBackwards] && ((distBidirecSearch[1][topNodeBackwards] + distBidirecSearch[0][topNodeBackwards] ) < estimate ) )
                estimate = distBidirecSearch[1][topNodeBackwards] + distBidirecSearch[0][topNodeBackwards];
        }

        if ((!continueForward || queue[0].empty() ) && (!continueBackwards || queue[1].empty() ) )
            break;
    }
    resetBidirecSearch();
    return estimate == Constants::INF ? -1 : estimate; // Return -1 if not path exists
}

void ContractionHierarchies::doPreprocess() {
    if (!preprocessor.hasCompletedPreprocess())
        preprocessor.preprocess(preprocessGraph, queryGraph);
}

int ContractionHierarchies::getTotalShortcutsAdded() const {
    return preprocessGraph.getShortcutsAdded();
}