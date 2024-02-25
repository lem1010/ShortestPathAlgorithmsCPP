//
// Created by Luca Massei on 21/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_STRESSTEST_H
#define SHORTESTPATHALGORITHMSCPP_STRESSTEST_H

#include <sstream> // For std::ostringstream to build formatted strings

#include "../../common/graph/Graph.h++"
#include "../randomise/Randomiser.h++"
#include "../randomise/graph/factory/RandomGraphFileFactory.h++"
#include "../options/TestSettings.h++"
#include "../utility/KahanSum.h++"
#include "../randomise/graph/options/RandomGraphInitRanges.h++"
#include "../../common/SPAType.h++"
#include "../../common/factory/SPAFactory.h++"


class StressTest {
private:
    TestSettings& settings;

    SPAType testingAlgorithmType; // i.e. the shortest path algorithm being stress tested
    SPAType benchmarkAlgorithmType; // i.e. the shortest path algorithm acting as the benchmark

    std::vector<double> testingAlgorithmAnsTimes;
    std::vector<double> benchmarkAlgorithmAnsTimes;

    int totalQueriesPassed = 0;
    int totalQueriesSet = 0;

    void resetOStringStream(std::ostringstream& oss);

    void printStressTestOnRandomGraphsSummary(int totalTestsPassed, int totalTestsSet);
    void printRandomGraphStressTestLineBarForStartEnd(bool isStartingTest);
    void printRandomGraphStressTestLineBar(std::string testStatus, bool hasFinishedTest);
    void printAvgQueryTimes();
public:
    StressTest(SPAType testingAlgorithmType, SPAType benchmarkAlgorithmType, TestSettings& settings);

    void runStressTestOnRandomGraphs(RandomGraphInitRanges &initRanges, int totalTestsSet, int queryQty);

    virtual bool runStressTest(std::string fileName, int queryQty) = 0;

    bool checkForMatchingAns(int testingAlgoAns, int benchmarkAlgoAns, int startNode, int endNode, int testNumber);

    void incrementQueriesPassed();
    void initQueryParameters(int queryQty);

    TestSettings& getSettings();

    const int& getTotalQueriesPassed() const;
    const int& getTotalQueriesSet() const;

    SPAType getTestingAlgorithmType() const;
    SPAType getBenchmarkAlgorithmType() const;

    std::string getTestingAlgorithmName() const;
    std::string getBenchmarkAlgorithmName() const;

    std::vector<double>& getTestingAlgorithmAnsTimes();
    std::vector<double>& getBenchmarkAlgorithmAnsTimes();
};

#endif //SHORTESTPATHALGORITHMSCPP_STRESSTEST_H
