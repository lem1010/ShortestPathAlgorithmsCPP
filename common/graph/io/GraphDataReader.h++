//
// Created by Luca Massei on 11/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_GRAPHDATAREADER_H
#define SHORTESTPATHALGORITHMSCPP_GRAPHDATAREADER_H

#include <utility>
#include "../Graph.h++"
#include "../structs/Trio.h++"

class GraphDataReader {
private:
    const int PREV_INIT_VAL = -1;
    int prevInputStartNode = PREV_INIT_VAL;
    int prevInputEndNode = PREV_INIT_VAL;
    int prevInputWeight = PREV_INIT_VAL;

public:
    virtual std::istream & getStream() = 0;

    virtual ~GraphDataReader() {}

    Trio readEdgeDataLine();
    std::pair<int, int> readNodeAndEdgeQtyLine();
    void storePrevLineInput(int startNode, int endNode, int weight);
    bool skipEdgeInput(int startNode, int endNode, int weight);
};
#endif //SHORTESTPATHALGORITHMSCPP_GRAPHDATAREADER_H
