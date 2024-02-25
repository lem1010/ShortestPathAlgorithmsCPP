//
// Created by Luca Massei on 16/2/2024.
//
#include "ContractionHierarchiesGraphFactory.h++"

PreprocessGraph ContractionHierarchiesGraphFactory::makePreprocessGraph(const Graph& graph) {
    return PreprocessGraph(graph);
}

QueryGraph ContractionHierarchiesGraphFactory::makeQueryGraph(const Graph& graph) {
    return QueryGraph(graph);
}