//
// Created by Luca Massei on 17/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_QUERYGRAPH_H
#define SHORTESTPATHALGORITHMSCPP_QUERYGRAPH_H

#include <vector>

#include "../../common/graph/Graph.h++"

class QueryGraph : public Graph {
private:
    std::vector<int> rank; // Ranks of nodes := positions in the node ordering
public:
    QueryGraph(const Graph& graph);

    std::vector<int>& getRank();
    const std::vector<int>& getRankReadOnly() const;
};


#endif //SHORTESTPATHALGORITHMSCPP_QUERYGRAPH_H
