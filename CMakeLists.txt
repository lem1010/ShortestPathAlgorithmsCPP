cmake_minimum_required(VERSION 3.27)
project(ShortestPathAlgorithmsCPP)

set(CMAKE_CXX_STANDARD 14)

# Group source files by their modules or logical grouping
set(COMMON_SOURCES
        common/ShortestPathAlgorithm.cpp
        common/graph/Graph.cpp
        common/graph/factory/GraphFactory.cpp
        common/graph/io/GraphDataReader.cpp
        common/graph/io/GraphFileReader.cpp
        common/graph/io/GraphInputReader.cpp
        common/utility/Constants.cpp
        common/utility/DataPrinter.cpp
        common/utility/Timer.cpp
        common/factory/SPAFactory.cpp
        common/SPAType.cpp
)

set(DIJKSTRA_SOURCES
        Dijkstra/Dijkstra.cpp
)

set(CH_SOURCES
        ContractionHierarchies/ContractionHierarchies.cpp
        ContractionHierarchies/graph/PreprocessGraph.cpp
        ContractionHierarchies/graph/QueryGraph.cpp
        ContractionHierarchies/graph/factory/ContractionHierarchiesGraphFactory.cpp
        ContractionHierarchies/preprocess/GraphPreprocessor.cpp
        ContractionHierarchies/preprocess/PredecessorDijkstra.cpp
        ContractionHierarchies/preprocess/WitnessPathFinder.cpp
)

set(TEST_SOURCES
        tests/mainTest.cpp
        tests/randomise/graph/options/RandomGraphInitRanges.cpp
        tests/options/TestSettings.cpp
        tests/randomise/graph/factory/RandomGraphFileFactory.cpp
        tests/randomise/Randomiser.cpp
        tests/stress-tests/StressTest.cpp
        tests/stress-tests/ContractionHierarchies/StressTestCH.cpp
        tests/stress-tests/ContractionHierarchies/options/StressTestSettingsCH.cpp
        tests/utility/KahanSum.cpp
)

# Main application
add_executable(Main main.cpp ${COMMON_SOURCES} ${DIJKSTRA_SOURCES} ${CH_SOURCES})

# Test application
add_executable(MainTest ${TEST_SOURCES} ${COMMON_SOURCES} ${DIJKSTRA_SOURCES} ${CH_SOURCES})
enable_testing()
add_test(NAME MainTest COMMAND MainTest)