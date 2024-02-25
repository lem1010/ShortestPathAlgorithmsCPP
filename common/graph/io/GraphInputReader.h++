//
// Created by Luca Massei on 12/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_GRAPHINPUTREADER_H
#define SHORTESTPATHALGORITHMSCPP_GRAPHINPUTREADER_H

#include "GraphDataReader.h++"
#include <iostream>  // For std::cin

class GraphInputReader : public GraphDataReader {
public:
    std::istream& getStream() override;
};
#endif //SHORTESTPATHALGORITHMSCPP_GRAPHINPUTREADER_H
