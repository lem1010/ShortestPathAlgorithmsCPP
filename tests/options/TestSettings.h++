//
// Created by Luca Massei on 21/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_TESTSETTINGS_H
#define SHORTESTPATHALGORITHMSCPP_TESTSETTINGS_H


class TestSettings {
private:
    bool willRunSpeedTest;
    bool willPrintExtraLinesForTesting;
    bool willExitAfterFirstTestFailure;
public:
    TestSettings(bool willRunSpeedTest = true,
                 bool willPrintExtraLinesForTesting = true,
                 bool willExitAfterFirstTestFailure = true);


    const bool& getWillPrintExtraLinesForTesting() const;
    const bool& getWillExitAfterFirstTestFailure() const;
    const bool& getWillRunSpeedTest() const;

    void setWillPrintExtraLinesForTesting(bool willPrintExtraLinesForTesting);
    void setWillExitAfterFirstTestFailure(bool willExitAfterFirstTestFailure);
    void setWillRunSpeedTest(bool willRunSpeedTest);
};


#endif //SHORTESTPATHALGORITHMSCPP_TESTSETTINGS_H
