//
// Created by Luca Massei on 18/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_TYPEDEFSCH_H
#define SHORTESTPATHALGORITHMSCPP_TYPEDEFSCH_H

#include <unordered_map>
#include <queue>

namespace TypeDefsCH {
    using SucMap = std::unordered_map<int, int>;
    using WitnessMap = std::unordered_map<int, std::unordered_map<int, int>>;
    using VisitList = std::vector<bool>;
    using DistList = std::vector<int>;
    using WorkSet = std::queue<int>;
    using QueueEdge = std::pair<int,int>; // (cost, node)
    using EdgePrQueue = std::priority_queue< QueueEdge, std::vector<QueueEdge>, std::greater<QueueEdge> >;
    using BidirecSearchQueue = std::vector<EdgePrQueue>;
    using ImpoNodePair = std::pair<int,int> ; // (importance, node)
    using ImpoPrQueue = std::priority_queue< ImpoNodePair, std::vector<ImpoNodePair>, std::greater<ImpoNodePair> >;
    // Other type definitions...
}

#endif //SHORTESTPATHALGORITHMSCPP_TYPEDEFSCH_H
