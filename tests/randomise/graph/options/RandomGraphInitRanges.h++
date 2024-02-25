//
// Created by Luca Massei on 22/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_RANDOMGRAPHINITRANGES_H
#define SHORTESTPATHALGORITHMSCPP_RANDOMGRAPHINITRANGES_H

#include "../../../utility/MinMaxRange.h++"

class RandomGraphInitRanges {
private:
    static const int NODE_QTY_DEFAULT_MIN = 1;
    static const int NODE_QTY_DEFAULT_MAX = 110000;

    static const int EDGE_QTY_DEFAULT_MIN = 1;
    static const int EDGE_QTY_DEFAULT_MAX = 250000;

    static const int WEIGHT_DEFAULT_MIN = 1;
    static const int WEIGHT_DEFAULT_MAX = 200000;

    MinMaxRange nodeQtyMinMaxRange;
    MinMaxRange edgeQtyMinMaxRange;
    MinMaxRange weightMinMaxRange;
public:
    RandomGraphInitRanges(MinMaxRange nodeQtyMinMaxRange, MinMaxRange edgeQtyMinMaxRange, MinMaxRange weightMinMaxRange);
    RandomGraphInitRanges();

    const MinMaxRange& getNodeQtyMinMaxRange() const;
    const MinMaxRange& getEdgeQtyMinMaxRange() const;
    const MinMaxRange& getWeightMinMaxRange() const;

    void setNodeQtyMinMaxRange(MinMaxRange nodeQtyMinMaxRange);
    void setEdgeQtyMinMaxRange(MinMaxRange edgeQtyMinMaxRange);
    void setWeightMinMaxRange(MinMaxRange weightMinMaxRange);
};


#endif //SHORTESTPATHALGORITHMSCPP_RANDOMGRAPHINITRANGES_H
