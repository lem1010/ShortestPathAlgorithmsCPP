//
// Created by Luca Massei on 16/2/2024.
//
#include "GraphFileReader.h++"

GraphFileReader::GraphFileReader(std::string fileName) {
    graphFile.open(fileName);
    if (!graphFile)
        std::cerr << "Error opening file" << std::endl;
}

std::istream& GraphFileReader::getStream() {
    return graphFile;
}