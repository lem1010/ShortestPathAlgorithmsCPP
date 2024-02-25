//
// Created by Luca Massei on 15/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_CONTRACTIONHIERARCHIESGRAPHFACTORY_H
#define SHORTESTPATHALGORITHMSCPP_CONTRACTIONHIERARCHIESGRAPHFACTORY_H

#include "../../../common/graph/factory/GraphFactory.h++"
#include "../PreprocessGraph.h++"
#include "../QueryGraph.h++"

class ContractionHierarchiesGraphFactory : public GraphFactory {
public:
    static PreprocessGraph makePreprocessGraph(const Graph& graph);
    static QueryGraph makeQueryGraph(const Graph& graph);
};
#endif //SHORTESTPATHALGORITHMSCPP_CONTRACTIONHIERARCHIESGRAPHFACTORY_H
