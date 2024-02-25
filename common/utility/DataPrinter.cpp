//
// Created by Luca Massei on 23/2/2024.
//

#include "DataPrinter.h++"

void DataPrinter::print2DVector(const std::vector<std::vector<int>>& a, bool useZeroBase) {
    for (int i = 0; i < a.size(); i++) {
        useZeroBase ? std::cout << i << ": " : std::cout << i + 1 << ": ";
        for (int j = 0; j < a[i].size(); j++)
            useZeroBase ? std::cout << a[i][j] : std::cout << a[i][j] + 1;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}