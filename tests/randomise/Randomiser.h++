//
// Created by Luca Massei on 20/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_RANDOMISER_H
#define SHORTESTPATHALGORITHMSCPP_RANDOMISER_H

#include <random>

class Randomiser {
private:
    static std::random_device rd;
public:
    static std::mt19937 generator;
    static int generateRandomInt(int min, int max);
    static std::uniform_int_distribution<> makeUniformIntDist(int min, int max);
};


#endif //SHORTESTPATHALGORITHMSCPP_RANDOMISER_H
