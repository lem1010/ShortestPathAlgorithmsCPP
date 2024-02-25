//
// Created by Luca Massei on 22/2/2024.
//

#include "StressTestSettingsCH.h++"

StressTestSettingsCH::StressTestSettingsCH(const TestSettings &baseSettings,
                                           bool willOnlyTestPreprocess,
                                           bool willCheckSpeedTestAns,
                                           int queryFailToleranceThreshold,
                                           bool willPrintSpeedTestAns,
                                           bool willPrintQueryAns)
                                           :
                                           TestSettings(baseSettings),
                                           willOnlyTestPreprocess(willOnlyTestPreprocess),
                                           willCheckSpeedTestAns(willCheckSpeedTestAns),
                                           queryFailToleranceThreshold(queryFailToleranceThreshold),
                                           willPrintSpeedTestAns(willPrintSpeedTestAns),
                                           willPrintQueryAns(willPrintQueryAns) {
    willDoSpecificTest = false;
    specificStartNode = 0;
    specificEndNode = 0;
}

bool StressTestSettingsCH::getWillOnlyTestPreprocess() {
    return willOnlyTestPreprocess;
}

bool StressTestSettingsCH::getWillPrintQueryAns() {
    return willPrintQueryAns;
}

bool StressTestSettingsCH::getWillPrintSpeedTestAns() {
    return willPrintSpeedTestAns;
}

bool StressTestSettingsCH::getWillCheckSpeedTestAns() {
    return willCheckSpeedTestAns;
}

bool StressTestSettingsCH::getWillDoSpecificTest() {
    return false;
}

int StressTestSettingsCH::getSpecificStartNode() {
    return specificStartNode;
}

int StressTestSettingsCH::getSpecificEndNode() {
    return specificEndNode;
}

int StressTestSettingsCH::getQueryFailToleranceThreshold() {
    return queryFailToleranceThreshold;
}

void StressTestSettingsCH::setWillOnlyTestPreprocess(bool willOnlyTestPreprocess) {
    this->willOnlyTestPreprocess = willOnlyTestPreprocess;
}

void StressTestSettingsCH::setWillPrintQueryAns(bool willPrintQueryAns) {
    this->willPrintQueryAns = willPrintQueryAns;
}

void StressTestSettingsCH::setWillPrintSpeedTestAns(bool willPrintSpeedTestAns) {
    this->willPrintSpeedTestAns = willPrintSpeedTestAns;
}

void StressTestSettingsCH::setWillCheckSpeedTestAns(bool willCheckSpeedTestAns) {
    this->willCheckSpeedTestAns = willCheckSpeedTestAns;
}

void StressTestSettingsCH::setSpecificTestSettings(int specificStartNode, int specificEndNode) {
    willDoSpecificTest = true;
    this->specificStartNode = specificStartNode;
    this->specificEndNode = specificEndNode;
}

void StressTestSettingsCH::setQueryFailToleranceThreshold(int queryFailToleranceThreshold) {
    this->queryFailToleranceThreshold = queryFailToleranceThreshold;
}