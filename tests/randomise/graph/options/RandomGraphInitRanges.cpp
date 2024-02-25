//
// Created by Luca Massei on 22/2/2024.
//

#include "RandomGraphInitRanges.h++"

RandomGraphInitRanges::RandomGraphInitRanges(MinMaxRange nodeQtyMinMaxRange, MinMaxRange edgeQtyMinMaxRange,
                                             MinMaxRange weightMinMaxRange) :
                                        nodeQtyMinMaxRange(nodeQtyMinMaxRange),
                                        edgeQtyMinMaxRange(edgeQtyMinMaxRange),
                                        weightMinMaxRange(weightMinMaxRange)    {}

RandomGraphInitRanges::RandomGraphInitRanges() : RandomGraphInitRanges(
        MinMaxRange(NODE_QTY_DEFAULT_MIN, NODE_QTY_DEFAULT_MAX),
        MinMaxRange(EDGE_QTY_DEFAULT_MIN, EDGE_QTY_DEFAULT_MAX),
        MinMaxRange(WEIGHT_DEFAULT_MIN, WEIGHT_DEFAULT_MAX)) {}

const MinMaxRange& RandomGraphInitRanges::getNodeQtyMinMaxRange() const {
    return nodeQtyMinMaxRange;
}

const MinMaxRange& RandomGraphInitRanges::getEdgeQtyMinMaxRange() const {
    return edgeQtyMinMaxRange;
}

const MinMaxRange& RandomGraphInitRanges::getWeightMinMaxRange() const {
    return weightMinMaxRange;
}

void RandomGraphInitRanges::setNodeQtyMinMaxRange(MinMaxRange nodeQtyMinMaxRange) {
    this->nodeQtyMinMaxRange = nodeQtyMinMaxRange;
}

void RandomGraphInitRanges::setEdgeQtyMinMaxRange(MinMaxRange edgeQtyMinMaxRange) {
    this->edgeQtyMinMaxRange = edgeQtyMinMaxRange;
}

void RandomGraphInitRanges::setWeightMinMaxRange(MinMaxRange weightMinMaxRange) {
    this->weightMinMaxRange = weightMinMaxRange;
}