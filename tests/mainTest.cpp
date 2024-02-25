//
// Created by Luca Massei on 20/2/2024.
//
#include "../common/SPAType.h++"
#include "../common/graph/factory/GraphFactory.h++"
#include "randomise/graph/options/RandomGraphInitRanges.h++"
#include "stress-tests/ContractionHierarchies/StressTestCH.h++"
#include "stress-tests/ContractionHierarchies/options/StressTestSettingsCH.h++"

int main() {
    SPAType benchmarkAlgorithm = SPAType::DijkstraSPA;

    auto settings = std::make_unique<StressTestSettingsCH>(
            TestSettings(true),
            true,
            true
            );

    StressTestCH stressTestCH = StressTestCH(benchmarkAlgorithm, std::move(settings));

    int queryQty = 2500;

    bool willRunStressTestOnRandomGraphs = false;

    if (willRunStressTestOnRandomGraphs) {
        RandomGraphInitRanges initRanges;
        /*
         * Set node quantity, edge quantity, and edge weight values to your liking.
         * These range values will be used to generate the random graphs through random
         * selection of node quantity/edge quantity/edge weights between those ranges.
         * You can also set minimum == maximum to generate random graphs of a particular
         * node quantity/edge quantity/edge weight.
         */
        initRanges.setNodeQtyMinMaxRange(MinMaxRange(50, 500));
        initRanges.setEdgeQtyMinMaxRange(MinMaxRange(50, 500));
        initRanges.setWeightMinMaxRange(MinMaxRange(1, 50000));

        int totalTestsSet = 3; // Number of random graphs to be generated and tested on

        stressTestCH.runStressTestOnRandomGraphs(initRanges, totalTestsSet, queryQty);
    }
    else {
        std::string fileName = "Testing/big_data_test.txt";
        stressTestCH.runStressTest(fileName, queryQty);
    }

    return 0;
}