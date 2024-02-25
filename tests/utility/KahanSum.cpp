//
// Created by Luca Massei on 21/2/2024.
//

#include "KahanSum.h++"

double KahanSum::calculate(const std::vector<double>& values) {
    double sum = 0.0;
    double c = 0.0; // A running compensation for lost low-order bits.
    int size = values.size();
    for (double value : values) {
        double y = value - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum/size;
}