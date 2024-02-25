//
// Created by Luca Massei on 15/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_EDGE_H
#define SHORTESTPATHALGORITHMSCPP_EDGE_H

struct Edge {
    int nodeTo;
    int weight;
    Edge(int nodeTo, int weight) : nodeTo(nodeTo), weight(weight) {}
};

#endif //SHORTESTPATHALGORITHMSCPP_EDGE_H
