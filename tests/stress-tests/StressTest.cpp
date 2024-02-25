//
// Created by Luca Massei on 21/2/2024.
//

#include "StressTest.h++"

StressTest::StressTest(SPAType testingAlgorithmType, SPAType benchmarkAlgorithmType, TestSettings& settings) :
                       testingAlgorithmType(testingAlgorithmType),
                       benchmarkAlgorithmType(benchmarkAlgorithmType),
                       settings(settings) {}


void StressTest::runStressTestOnRandomGraphs(RandomGraphInitRanges &initRanges, int totalTestsSet, int queryQty) {
    initQueryParameters(queryQty);
    int totalTestsPassed = 0;
    std::ostringstream oss;

    if (settings.getWillPrintExtraLinesForTesting())
        printRandomGraphStressTestLineBarForStartEnd(true);

    for (int i = 0; i < totalTestsSet; i++) {
        if (settings.getWillPrintExtraLinesForTesting()) {
            oss << "    " << "RUNNING STRESS TEST #" << (i + 1) << "/" << totalTestsSet << "    ";
            printRandomGraphStressTestLineBar(oss.str(), false);
            resetOStringStream(oss);
        }

        int nodeQty = Randomiser::generateRandomInt(initRanges.getNodeQtyMinMaxRange().minimum,
                                                    initRanges.getNodeQtyMinMaxRange().maximum);

        int edgeQty = Randomiser::generateRandomInt(initRanges.getEdgeQtyMinMaxRange().minimum,
                                                    initRanges.getEdgeQtyMinMaxRange().maximum);

        if (settings.getWillPrintExtraLinesForTesting())
            printf("⧆  GENERATING RANDOM GRAPH...");

        RandomGraphFileFactory::generateRandomGraphFile(nodeQty, edgeQty,initRanges.getWeightMinMaxRange());

        if (settings.getWillPrintExtraLinesForTesting())
            printf("     RANDOM GRAPH GENERATED. INITIATING SPEED TEST...\n");

        bool success = runStressTest(RandomGraphFileFactory::LAST_RAND_GRAPH_FILE_NAME, queryQty);

        if (!success) {
            if (settings.getWillPrintExtraLinesForTesting()) {
                oss << "!!!    FAIL:    STRESS TEST #" << (i + 1) << "/" << totalTestsSet;
                printRandomGraphStressTestLineBar(oss.str(), true);
                resetOStringStream(oss);
            }

            if (settings.getWillExitAfterFirstTestFailure())
                break;
        }

        else {
            if (settings.getWillPrintExtraLinesForTesting()) {
                oss << "✓✓✓  SUCCESS:   STRESS TEST #" << (i + 1) << "/" << totalTestsSet;
                printRandomGraphStressTestLineBar(oss.str(), true);
                resetOStringStream(oss);
            }
            totalTestsPassed++;
        }
    }

    if (settings.getWillRunSpeedTest()) {
        if (settings.getWillPrintExtraLinesForTesting())
            printAvgQueryTimes();

    }

    printStressTestOnRandomGraphsSummary(totalTestsPassed, totalTestsSet);
    if (settings.getWillPrintExtraLinesForTesting())
        printRandomGraphStressTestLineBarForStartEnd(false);
}

void StressTest::printAvgQueryTimes() {
    printf("\n          ---------    AVG. QUERY TIMES    ---------\n\n");
    printf("     ");
    printf("%s:  %.3f  seconds", getTestingAlgorithmName().c_str(), KahanSum::calculate(testingAlgorithmAnsTimes));
    printf(",          ");
    printf("%s:  %.3f  seconds", getBenchmarkAlgorithmName().c_str(), KahanSum::calculate(benchmarkAlgorithmAnsTimes));
    printf("\n\n");
}

bool StressTest::checkForMatchingAns(int testingAlgoAns, int benchmarkAlgoAns, int startNode, int endNode, int testNumber) {
    if (testingAlgoAns != benchmarkAlgoAns) {
        printf("\nError at test #%d for startNode = %d,  endNode = %d: ", testNumber, startNode, endNode);
        printf("%s answer = %d,   but %s answer = %d.\n", getTestingAlgorithmName().c_str(), testingAlgoAns,
               getBenchmarkAlgorithmName().c_str(), benchmarkAlgoAns);
        return false;
    }
    return true;
}

void StressTest::printStressTestOnRandomGraphsSummary(int totalTestsPassed, int totalTestsSet) {
    printf("\n‹·›‹·›‹·›‹·›      STRESS TEST COMPLETE:");
    printf(",       ");
    printf("tests passed  =  %d/%d   ( %.2f %% )", totalTestsPassed, totalTestsSet, 100*(double)totalTestsPassed/totalTestsSet);
    printf(",       ");
    printf("queries passed  =  %d/%d   ( %.2f %% )", totalQueriesPassed, totalQueriesSet, 100*(double)totalTestsPassed/totalTestsSet);
    printf(".\n");
}

void StressTest::printRandomGraphStressTestLineBarForStartEnd(bool isStartingTest) {
    std::string testStatus;
    if (isStartingTest)
        testStatus = "□  initiating random graph stress testing...";
    else
        testStatus = "■  exiting random graph stress testing...";

    printf("\n");
    printf("=============================================   %s   =================================================", testStatus.c_str());
    printf("\n\n");
}

void StressTest::printRandomGraphStressTestLineBar(std::string testStatus, bool hasFinishedTest) {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   %s   ~~~~~~~~~~~~~~~~~~~", testStatus.c_str());
    hasFinishedTest ? printf("\n\n\n\n") : printf("\n\n");
}

void StressTest::resetOStringStream(std::ostringstream& oss) {
    // Clear the stream for reuse
    oss.str("");  // Clear the content
    oss.clear();  // Clear any error flags
}

void StressTest::incrementQueriesPassed() {
    totalQueriesPassed++;
}

void StressTest::initQueryParameters(int queryQty) {
    totalQueriesPassed = 0;
    totalQueriesSet = queryQty;
}

TestSettings& StressTest::getSettings() {
    return settings;
}

const int& StressTest::getTotalQueriesPassed() const {
    return totalQueriesPassed;
}

const int& StressTest::getTotalQueriesSet() const {
    return totalQueriesSet;
}

SPAType StressTest::getTestingAlgorithmType() const {
    return testingAlgorithmType;
}
SPAType StressTest::getBenchmarkAlgorithmType() const {
    return benchmarkAlgorithmType;
}

std::string StressTest::getTestingAlgorithmName() const {
    return SPANames[testingAlgorithmType];
}

std::string StressTest::getBenchmarkAlgorithmName() const {
    return SPANames[benchmarkAlgorithmType];
}

std::vector<double> & StressTest::getTestingAlgorithmAnsTimes() {
    return testingAlgorithmAnsTimes;
}

std::vector<double> & StressTest::getBenchmarkAlgorithmAnsTimes() {
    return benchmarkAlgorithmAnsTimes;
}