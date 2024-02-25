//
// Created by Luca Massei on 21/2/2024.
//

#include "TestSettings.h++"

TestSettings::TestSettings(bool willRunSpeedTest, bool willPrintExtraLinesForTesting, bool willExitAfterFirstTestFailure) :
        willRunSpeedTest(willRunSpeedTest),
        willPrintExtraLinesForTesting(willPrintExtraLinesForTesting),
        willExitAfterFirstTestFailure(willExitAfterFirstTestFailure){}

const bool& TestSettings::getWillPrintExtraLinesForTesting() const {
   return willPrintExtraLinesForTesting;
}

const bool& TestSettings::getWillRunSpeedTest() const {
    return willRunSpeedTest;
}

const bool& TestSettings::getWillExitAfterFirstTestFailure() const {
    return willExitAfterFirstTestFailure;
}

void TestSettings::setWillPrintExtraLinesForTesting(bool willPrintExtraLinesForTesting) {
    this->willPrintExtraLinesForTesting = willPrintExtraLinesForTesting;
}


void TestSettings::setWillRunSpeedTest(bool willRunSpeedTest) {
    this->willRunSpeedTest = willRunSpeedTest;
}

void TestSettings::setWillExitAfterFirstTestFailure(bool willExitAfterFirstTestFailure) {
    this->willExitAfterFirstTestFailure = willExitAfterFirstTestFailure;
}