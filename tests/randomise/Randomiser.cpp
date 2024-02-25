//
// Created by Luca Massei on 20/2/2024.
//

#include "Randomiser.h++"

std::random_device Randomiser::rd; // Definition for rd
std::mt19937 Randomiser::generator(rd());

int Randomiser::generateRandomInt(int min, int max) {
    std::uniform_int_distribution<> dist(min, max); // Define a uniform integer distribution
    return dist(generator); // Use the mt19937 generator to produce a random number within the distribution
}

std::uniform_int_distribution<> Randomiser::makeUniformIntDist(int min, int max) {
    return std::uniform_int_distribution<>(min, max);
}