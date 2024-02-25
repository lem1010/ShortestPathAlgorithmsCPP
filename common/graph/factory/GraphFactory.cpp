//
// Created by Luca Massei on 16/2/2024.
//
#include "GraphFactory.h++"

void GraphFactory::createGraphEdges(GraphDataReader& dataReader, Graph& graph) {
    for (int i = 0; i < graph.getExpectedEdgeQty(); i++) {
        Trio dataTrio = dataReader.readEdgeDataLine();
        int startNode = dataTrio.first - 1;
        int endNode = dataTrio.second - 1;
        int weight = dataTrio.third;
        if ( !dataReader.skipEdgeInput(startNode, endNode, weight) ) {
            graph.addEdge(startNode, endNode, weight);
            dataReader.storePrevLineInput(startNode, endNode, weight);
        }
    }
}

Graph GraphFactory::makeGraphFromReadData() {
    return makeGraphFromReadData("");
}

Graph GraphFactory::makeGraphFromReadData(std::string fileName) {
    GraphDataReader* dataReader;
    if (fileName == "")
        dataReader = new GraphInputReader();
    else
        dataReader = new GraphFileReader(fileName);

    std::pair<int, int> nodeEdgeQtyPair = dataReader->readNodeAndEdgeQtyLine();
    Graph graph = Graph(nodeEdgeQtyPair.first, nodeEdgeQtyPair.second);
    createGraphEdges(*dataReader, graph);

    delete dataReader;

    return graph;
}