# ShortestPathAlgorithmsCPP
# Shortest Path Algorithms in C++

This project implements shortest path algorithms (SPAs) in C++ with a focus on performance, extensibility, and testing.

It includes a setup of predefined SPAs that I have included, as well as a testing framework for benchmarking and correctness. Here, you'll find an implementation for the Contraction Hierarchies (CH) speed-up technique.

Feel free to use this project to benchmark your SPAs through the provided testing framework. Extend/modify/re-purpose any of the code as you wish!

## Getting Started

To get started with the project, clone the repository to your local machine:

`git clone https://github.com/lem1010/ShortestPathAlgorithmsCPP.git`

Navigate to the project directory:

`cd ShortestPathAlgorithmsCPP`

### Running the Project

The project comprises two main components:

1. **Main Application (`main.cpp`)**: Provides a pre-configured environment to experiment with various SPAs. To run the main application, compile and execute `main.cpp`:

    ```
    g++ main.cpp -o mainApp
    ./mainApp
    ```

2. **Testing Framework (`mainTest.cpp`)**: Facilitates conducting tests to evaluate the performance and correctness of SPAs. To run the testing framework, compile and execute `mainTest.cpp`:

    ```
    g++ mainTest.cpp -o testApp
    ./testApp
    ```

### Input Format

The application reads graph data either from a predefined file or through user input. The expected input format is as follows:

- First, specify the graph's node and edge quantity:

    ```
    nodeQuantity edgeQuantity
    ```

- Then, input the edges of the graph, where each line represents an edge connecting `startNode` to `targetNode` with an `edgeWeight`:

    ```
    startNode targetNode edgeWeight
    ```

    Repeat this for the number of edges specified.

- Finally, specify the number of queries and input each query, indicating the `startNode` and `targetNode` for pathfinding:

    ```
    queryQuantity
    startNode targetNode
    ```

    Repeat this for the number of queries specified.

Alternatively, you can read input from a `.txt` file:

- By default, `main.cpp` is set up to read the input of a small graph from `cmake-build-debug/Testing/test_file_input.txt`.
- `mainTest.cpp` reads from `cmake-build-debug/Testing/big_data_test.txt`, which contains data of a real-life, large graph, taken from [The 9th DIMACS Implementation Challenge](https://www.diag.uniroma1.it/challenge9/download.shtml). This site is highly recommended if you are in need of large (and real) graph data sets.

Feel free to play around with or modify `main.cpp`, `mainTest.cpp`, and/or the provided `.txt` files.

**IMPORTANT**:
- Randomly-generated graphs are saved under `cmake-build-debug/Testing/latest_random_graph_test.txt`, and this file is always overwritten each time a random graph is generated.
- If this file is not found, the program will create it at the specified file path and will proceed to populate it with random graph data.

### Future Developments

The project plans to include more SPAs (e.g. Bidirectional Search, A* Search) and optimisations of pre-existing ones.

As some SPAs may require additional particular graph data, such as node coordinates, we plan to extend the graph-related classes to handle additional input data as needed (depending on the SPA used).

The classes involved in generating random graphs can also be extended to produce the particular data randomly (e.g. random Cartesian coordinates to arrange nodes with). However, this will require a considerate approach to ensure that realistic graph data is being generated.

In addition, the project plans to expand the documentation, providing deeper insights into the classes, functions, and members. Additional in-line commenting will be added to enhance code readability and understanding.

Lastly, the project could benefit from a user-interface (UI) that would allow users to interact with the algorithms and visualise the graph structures and shortest path computations in a more intuitive manner. A graphical UI could provide functionalities such as:

- **Graph Visualisation**: Displaying the graph with nodes and edges, possibly with options to zoom and pan for larger graphs.
- **Algorithm Step-through**: Allowing users to step through the execution of an SPA, observing how the algorithm progresses, which nodes are visited, and how the shortest path is determined.
- **Performance Metrics**: Showing real-time performance metrics such as execution time, memory usage, and number of nodes/edges processed. This could be valuable for benchmarking purposes.
- **Interactive Graph Editing**: Enabling users to create custom graphs by adding/removing nodes and edges, or modifying edge weights, to experiment with how different graph structures affect algorithm performance.
- **Pathfinding Visualisation**: Highlighting the shortest path computed by the algorithm on the graph, providing immediate visual feedback on the result.

Developing a UI would involve integrating graphical libraries suitable for the chosen programming environment and potentially re-structuring the project to support interactive use cases. This enhancement would make the project more accessible to those less familiar with command-line interfaces and could serve as an excellent educational tool for those learning about shortest path algorithms and graph theory.



Stay tuned for updates, and feel free to contribute or suggest improvements!
