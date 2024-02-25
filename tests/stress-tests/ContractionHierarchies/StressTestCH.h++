//
// Created by Luca Massei on 21/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_STRESSTESTCH_H
#define SHORTESTPATHALGORITHMSCPP_STRESSTESTCH_H


#include "../StressTest.h++"
#include "options/StressTestSettingsCH.h++"
#include "../../../common/graph/Graph.h++"
#include "../../../ContractionHierarchies/ContractionHierarchies.h++"
#include "../../../common/utility/Timer.h++"

class StressTestCH : public StressTest {
private:
    std::unique_ptr<StressTestSettingsCH> settingsCH = nullptr;
    std::unique_ptr<ShortestPathAlgorithm> benchmarkAlgorithm = nullptr;

    bool runStressSpeedTest(const Graph& graph, int queryQty);
    /*
    * 'runQuerySpeedTest' testing function is for benchmarking query computational speed, but
    * can also check if the answers between CH and the benchmark algorithm mismatch.
    * For a more resource efficient query testing, call the 'runQueryTestOnly' (see below).
    */
    bool runQuerySpeedTest(ContractionHierarchies& ch, const Graph& graph, int queryQty, Timer& timer);
    bool runQueryTestOnly(const Graph& graph, int queryQty);

    void printPreprocSpeedTestStartingLine();
    void printPreprocSpeedTestFinishingLine(const double& totalTime, const int& shortcutsAdded);
    void printSpeedTestAnsError(int startNode, int endNode, int answerCH, int answerBenchmark, const Graph &graph);
public:
    StressTestCH(SPAType benchmarkAlgorithmType, std::unique_ptr<StressTestSettingsCH> settings);

    bool runStressTest(std::string fileName, int queryQty) override;
};


#endif //SHORTESTPATHALGORITHMSCPP_STRESSTESTCH_H
