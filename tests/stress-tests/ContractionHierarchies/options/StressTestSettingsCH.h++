//
// Created by Luca Massei on 22/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_STRESSTESTSETTINGSCH_H
#define SHORTESTPATHALGORITHMSCPP_STRESSTESTSETTINGSCH_H

#include "../../../options/TestSettings.h++"

class StressTestSettingsCH : public TestSettings {
private:
    bool willOnlyTestPreprocess;
    bool willPrintQueryAns;
    bool willPrintSpeedTestAns;
    bool willCheckSpeedTestAns;
    bool willDoSpecificTest;

    /* For testing a specific query
     * between two particular node */
    int specificStartNode;
    int specificEndNode;
    
    int queryFailToleranceThreshold; // To stop testing if query fails exceed threshold
public:
    StressTestSettingsCH(const TestSettings &baseSettings, bool willOnlyTestPreprocess = false,
                         bool willCheckSpeedTestAns = false, int queryFailToleranceThreshold = 0,
                         bool willPrintSpeedTestAns = false, bool willPrintQueryAns = false);

    static const int PRINT_AT_QUEUE_SIZE_MULTIPLES_OF = 500;

    bool getWillOnlyTestPreprocess();
    bool getWillPrintQueryAns();
    bool getWillPrintSpeedTestAns();
    bool getWillCheckSpeedTestAns();
    bool getWillDoSpecificTest();
    int getSpecificStartNode();
    int getSpecificEndNode();
    int getQueryFailToleranceThreshold();
    
    void setWillOnlyTestPreprocess(bool willOnlyTestPreprocess);
    void setWillPrintQueryAns(bool willPrintQueryAns);
    void setWillPrintSpeedTestAns(bool willPrintSpeedTestAns);
    void setWillCheckSpeedTestAns(bool willCheckSpeedTestAns);
    void setSpecificTestSettings(int specificStartNode, int specificEndNode);
    void setQueryFailToleranceThreshold(int queryFailToleranceThreshold);
};

#endif //SHORTESTPATHALGORITHMSCPP_STRESSTESTSETTINGSCH_H
