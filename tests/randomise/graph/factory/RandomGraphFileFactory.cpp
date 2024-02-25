//
// Created by Luca Massei on 20/2/2024.
//

#include "RandomGraphFileFactory.h++"

const std::string RandomGraphFileFactory::LAST_RAND_GRAPH_FILE_NAME = "Testing/latest_random_graph_test.txt";

void RandomGraphFileFactory::generateRandomGraphFile(int nodeQty, int edgeQty, MinMaxRange weightMinMaxRange) {
    std::uniform_int_distribution<> nodes = Randomiser::makeUniformIntDist(1, nodeQty);
    std::uniform_int_distribution<> weights = Randomiser::makeUniformIntDist(weightMinMaxRange.minimum,
                                                                             weightMinMaxRange.maximum);
    try {
        std::ofstream file(RandomGraphFileFactory::LAST_RAND_GRAPH_FILE_NAME);
        if (!file) throw std::runtime_error("Unable to open file");

        file << nodeQty << " " << edgeQty << "\n";

        // First generate a connected graph
        for (int i = 1; i < nodeQty; i++) {
            file << i << " " << i+1 << " " << weights(Randomiser::generator) << "\n";
        }

        // Then add additional edges randomly
        for (int i = nodeQty; i <= edgeQty; i++) {
            int startNode = nodes(Randomiser::generator), endNode = nodes(Randomiser::generator);

            while (startNode == endNode) // Ensure we don't add loops
                endNode = nodes(Randomiser::generator);

            file << startNode << " " << endNode << " " << weights(Randomiser::generator) << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << '\n';
    }
}