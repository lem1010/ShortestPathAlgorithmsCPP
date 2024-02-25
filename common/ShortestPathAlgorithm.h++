//
// Created by Luca Massei on 7/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_SHORTESTPATHALGORITHM_H
#define SHORTESTPATHALGORITHMSCPP_SHORTESTPATHALGORITHM_H

#include "graph/Graph.h++"

class ShortestPathAlgorithm {
private:
    const Graph& graph;
    bool testMode = false;
public:
    ShortestPathAlgorithm(const Graph& graph);

    virtual ~ShortestPathAlgorithm() = default;
    virtual int computeDistance(int startNode, int endNode) = 0;

    /*
     * The enterTestMode() method prepares the algorithm for test operations,
     * setting the necessary state for testing. Derived classes should call this
     * method at the start of any test-specific functions to ensure the algorithm
     * is in the correct mode for testing.
     */
    void enterTestMode();

    /*
     * Similarly, exitTestMode() reverts the algorithm back to its standard operating
     * mode, cleaning up or resetting any test-specific state. It should be called
     * at the end of test-specific functions in derived classes to ensure the algorithm
     * exits the test mode cleanly and is ready for normal operations.
     */
    void exitTestMode();

    bool isInTestMode() const;

    const Graph& getGraph() const;
};

#endif //SHORTESTPATHALGORITHMSCPP_SHORTESTPATHALGORITHM_H

