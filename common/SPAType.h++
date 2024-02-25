//
// Created by Luca Massei on 22/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_SPATYPE_H
#define SHORTESTPATHALGORITHMSCPP_SPATYPE_H


enum SPAType {
    ContractionHierarchiesSPA,
    DijkstraSPA,
    NUM_ALGORITHMS
};

extern const char* SPANames[NUM_ALGORITHMS];

#endif //SHORTESTPATHALGORITHMSCPP_SPATYPE_H
