//
// Created by Luca Massei on 11/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_GRAPHFACTORY_H
#define SHORTESTPATHALGORITHMSCPP_GRAPHFACTORY_H

#include "../Graph.h++"
#include "../io/GraphDataReader.h++"
#include "../io/GraphInputReader.h++"
#include "../io/GraphFileReader.h++"

class GraphFactory {
private:
    static void createGraphEdges(GraphDataReader& dataReader, Graph& graph);
public:
    // Overloaded eraseRedundantEdges for when data is read from user input
    static Graph makeGraphFromReadData();

    // Function reads data from the file path parameter
    static Graph makeGraphFromReadData(std::string fileName);
};
#endif //SHORTESTPATHALGORITHMSCPP_GRAPHFACTORY_H
