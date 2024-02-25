//
// Created by Luca Massei on 22/2/2024.
//

#include "SPAFactory.h++"

std::unique_ptr<ShortestPathAlgorithm> SPAFactory::makeAlgorithm(SPAType algorithmType, const Graph& graph) {
    switch (algorithmType) {
        case SPAType::DijkstraSPA:
            return std::make_unique<Dijkstra>(graph);
        case SPAType::ContractionHierarchiesSPA:
            return std::make_unique<ContractionHierarchies>(graph);
        default:
            return nullptr;  // Or throw an exception if an unknown type is requested
    }
}