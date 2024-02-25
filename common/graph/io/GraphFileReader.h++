//
// Created by Luca Massei on 12/2/2024.
//
#ifndef SHORTESTPATHALGORITHMSCPP_GRAPHFILEREADER_H
#define SHORTESTPATHALGORITHMSCPP_GRAPHFILEREADER_H

#include "GraphDataReader.h++"
#include <fstream>  // Include for std::ifstream
#include <iostream> // Include for std::cerr

class GraphFileReader : public GraphDataReader {
private:
    std::ifstream graphFile;

public:
    explicit GraphFileReader(std::string fileName);  // Constructor declaration

    std::istream& getStream() override;  // Function declaration
};
#endif //SHORTESTPATHALGORITHMSCPP_GRAPHFILEREADER_H
