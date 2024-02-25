//
// Created by Luca Massei on 22/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_SPAFACTORY_H
#define SHORTESTPATHALGORITHMSCPP_SPAFACTORY_H


#include "../SPAType.h++"
#include "../ShortestPathAlgorithm.h++"
#include "../../Dijkstra/Dijkstra.h++"
#include "../../ContractionHierarchies/ContractionHierarchies.h++"

class SPAFactory {
public:
    static std::unique_ptr<ShortestPathAlgorithm> makeAlgorithm(SPAType algorithmType, const Graph& graph);
};


#endif //SHORTESTPATHALGORITHMSCPP_SPAFACTORY_H
