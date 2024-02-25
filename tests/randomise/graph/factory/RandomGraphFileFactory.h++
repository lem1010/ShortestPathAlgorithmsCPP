//
// Created by Luca Massei on 20/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_RANDOMGRAPHFILEFACTORY_H
#define SHORTESTPATHALGORITHMSCPP_RANDOMGRAPHFILEFACTORY_H

#include <iostream>
#include <fstream>
#include <string>

#include "../../../utility/MinMaxRange.h++"
#include "../../Randomiser.h++"

class RandomGraphFileFactory {
private:
public:
    static const std::string LAST_RAND_GRAPH_FILE_NAME;

    static void generateRandomGraphFile(int nodeQty, int edgeQty, MinMaxRange weightMinMaxPair);
};

#endif //SHORTESTPATHALGORITHMSCPP_RANDOMGRAPHFILEFACTORY_H
