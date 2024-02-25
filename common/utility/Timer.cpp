//
// Created by Luca Massei on 17/2/2024.
//

#include "Timer.h++"

Timer::Timer() : totalTime(0.0), isRunning(false) {
    // Initializer list initializes totalTime and isRunning
}

void Timer::startTimer() {
    if (!isRunning) {  // Start only if not already running
        start = Clock::now();
        isRunning = true;
    }
}

void Timer::stopTimer() {
    if (isRunning) {
        auto end = Clock::now();
        std::chrono::duration<double> elapsed = end - start;
        totalTime += elapsed.count();  // Accumulate elapsed time
        isRunning = false;
    }
}

double Timer::getTotalTime() const {
    return totalTime;  // Return the total accumulated time
}

void Timer::resetTimer() {
    totalTime = 0.0;  // Reset the accumulated time
    isRunning = false;  // Ensure the timer is stopped
}