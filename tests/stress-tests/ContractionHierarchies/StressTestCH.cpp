//
// Created by Luca Massei on 21/2/2024.
//

#include "StressTestCH.h++"

StressTestCH::StressTestCH(SPAType benchmarkAlgorithmType, std::unique_ptr<StressTestSettingsCH> settings) :
    StressTest(SPAType::ContractionHierarchiesSPA, benchmarkAlgorithmType, *settings),
    settingsCH(std::move(settings)) {}

bool StressTestCH::runStressTest(std::string fileName, int queryQty) {
    Graph graph = GraphFactory::makeGraphFromReadData(fileName);
    int nodeQty = graph.getNodeQty(), edgeQty = graph.getEdgeQty();

    benchmarkAlgorithm = SPAFactory::makeAlgorithm(getBenchmarkAlgorithmType(), graph);

    if (settingsCH->getWillPrintExtraLinesForTesting())
        printf("\nRunning test on graph with nodeQty = %d,   edgeQty = %d...\n\n", nodeQty, edgeQty);

    if (settingsCH->getWillRunSpeedTest())
        return runStressSpeedTest(graph, queryQty);
    else
        return runQueryTestOnly(graph, queryQty);
}

bool StressTestCH::runStressSpeedTest(const Graph& graph, int queryQty) {
    Timer timer;

    if (getSettings().getWillPrintExtraLinesForTesting())
        printPreprocSpeedTestStartingLine();

    ContractionHierarchies ch = ContractionHierarchies(graph);

    ch.enterSpeedTestMode(timer);
    ch.doPreprocess();
    ch.exitSpeedTestMode();

    if (getSettings().getWillPrintExtraLinesForTesting())
        printPreprocSpeedTestFinishingLine(timer.getTotalTime(), ch.getTotalShortcutsAdded());

    timer.resetTimer();

    if (settingsCH->getWillOnlyTestPreprocess())
        return true;

    return runQuerySpeedTest(ch, graph, queryQty, timer);
}

bool StressTestCH::runQuerySpeedTest(ContractionHierarchies& ch, const Graph& graph, int queryQty, Timer &timer) {
    std::vector<int> startNodeValues;
    std::vector<int> endNodeValues;
    std::vector<int> totalAnswersCH;

    if (getSettings().getWillPrintExtraLinesForTesting())
        printf("\nINITIATING SPEED TEST WITH QUERIES = %d...\n", queryQty);

    if (getSettings().getWillPrintExtraLinesForTesting())
        printf("\nstarting speed test for CH...\n");

    timer.startTimer();
    for (int i = 0; i < queryQty; i++) {
        int startNode = Randomiser::generateRandomInt(1, graph.getNodeQty());
        int endNode = Randomiser::generateRandomInt(1, graph.getNodeQty());

        startNodeValues.push_back(startNode);
        endNodeValues.push_back(endNode);

        int answerCH = ch.computeDistance(startNode - 1, endNode - 1);

        if (settingsCH->getWillPrintSpeedTestAns())
            printf("T#%d: answerCH = %d\n", i + 1, answerCH);

        if (settingsCH->getWillCheckSpeedTestAns())
            totalAnswersCH.push_back(answerCH);
    }
    timer.stopTimer();

    double queryTimeCH = timer.getTotalTime();
    timer.resetTimer();

    getTestingAlgorithmAnsTimes().push_back(queryTimeCH);

    if (getSettings().getWillPrintExtraLinesForTesting())
        printf("¢©¢©¢©¢©¢©   CH Elapsed time: %f seconds.\n", queryTimeCH);

    if (getSettings().getWillPrintExtraLinesForTesting())
        printf("\nBENCHMARK: starting speed test for %s...\n", getBenchmarkAlgorithmName().c_str());

    timer.startTimer();
    for (int i = 0; i < queryQty; i++) {
        int startNode = startNodeValues[i], endNode = endNodeValues[i]; // Same two nodes as CH
        int answerBenchmark = benchmarkAlgorithm->computeDistance(startNode - 1, endNode - 1);

        if (settingsCH->getWillPrintSpeedTestAns())
            printf("T#%d: answerBenchmark = %d\n", i + 1, answerBenchmark);

        if (settingsCH->getWillCheckSpeedTestAns()) {
            if (totalAnswersCH[i] != answerBenchmark) {
                printSpeedTestAnsError(startNode, endNode, totalAnswersCH[i], answerBenchmark, graph);
                return false;
            }
        }
    }
    timer.stopTimer();

    double queryTimeBenchmark = timer.getTotalTime();
    timer.resetTimer();

    getBenchmarkAlgorithmAnsTimes().push_back(queryTimeBenchmark);

    if (getSettings().getWillPrintExtraLinesForTesting())
        printf("£™£™£™£™£™   %s Elapsed time: %f seconds.\n\n", getBenchmarkAlgorithmName().c_str(), queryTimeBenchmark);

    if (settingsCH->getWillCheckSpeedTestAns())
        printf("✓_✓_✓_✓_✓_✓_✓_✓_✓        SUCCESS: All cross-checked answers match.\n\n");
    return true;
}

bool StressTestCH::runQueryTestOnly(const Graph& graph, int queryQty) {
    initQueryParameters(queryQty);
    int failedQueriesCounter = 0;
    bool success = true;

    ContractionHierarchies ch = ContractionHierarchies(graph);

    for (int i = 0; i < queryQty; i++) {
        int startNode = Randomiser::generateRandomInt(1, graph.getNodeQty());
        int endNode = Randomiser::generateRandomInt(1, graph.getNodeQty());

        if (settingsCH->getWillDoSpecificTest()) {
            startNode = settingsCH->getSpecificStartNode();
            endNode = settingsCH->getSpecificEndNode();
        }

        int CHAns = ch.computeDistance(startNode - 1, endNode - 1);
        int benchmarkAns = benchmarkAlgorithm->computeDistance(startNode - 1, endNode - 1);

        if (settingsCH->getWillPrintQueryAns())
            printf("T#%d: CH ans = %d,             benchmark ans = %d\n", i + 1, CHAns, benchmarkAns);

        if (!checkForMatchingAns(CHAns, benchmarkAns, startNode, endNode, i + 1)) {
            success = false;
            failedQueriesCounter++;
            if (failedQueriesCounter >= settingsCH->getQueryFailToleranceThreshold())
                break;
        }
        else
            incrementQueriesPassed();

        if (settingsCH->getWillDoSpecificTest())
            break;
    }

    if (!success && settingsCH->getWillPrintExtraLinesForTesting())
        printf("Successfully passed all tests.\n");

    return success;
}

void StressTestCH::printPreprocSpeedTestStartingLine() {
    printf("📣📣📣    INITIATING PRE-PROCESSING SPEED TEST...\n");
}

void StressTestCH::printPreprocSpeedTestFinishingLine(const double& totalTime, const int& shortcutsAdded) {
    printf("\n\n☑️☑️☑️   ~~   PRE-PROCESSING COMPLETE: It took %.3f seconds.     Total shortcuts added = %d\n\n",
           totalTime, shortcutsAdded);
}

void StressTestCH::printSpeedTestAnsError(int startNode, int endNode, int answerCH, int answerBenchmark, const Graph& graph) {
    printf("\n\n¡™™¡™™¡™™¡™™¡™™¡™™¡™™¡™™¡™™      SPEED TEST ERROR:      ");
    printf("startNode = %d,  endNode = %d.    ch_ans[] = %d,    but answerBenchmark = %d\n", startNode + 1,
           endNode + 1, answerCH, answerBenchmark);
    printf("\nnodeQty = %d,   edgeQty = %d\n", graph.getNodeQty(), graph.getEdgeQty());
}