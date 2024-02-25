//
// Created by Luca Massei on 17/2/2024.
//

#ifndef SHORTESTPATHALGORITHMSCPP_TIMER_H
#define SHORTESTPATHALGORITHMSCPP_TIMER_H


#include <chrono>

class Timer {
private:
    using Clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<Clock> start;
    double totalTime;  // Accumulates total elapsed time across start-stop cycles
    bool isRunning;
public:
    Timer();
    void startTimer();
    void stopTimer();
    double getTotalTime() const;
    void resetTimer();
};


#endif //SHORTESTPATHALGORITHMSCPP_TIMER_H
