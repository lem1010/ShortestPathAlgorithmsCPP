#include "common/graph/factory/GraphFactory.h++"
#include "ContractionHierarchies/ContractionHierarchies.h++"
#include "Dijkstra/Dijkstra.h++"
#include "common/SPAType.h++"
#include "common/factory/SPAFactory.h++"

#define EXPECTED_QUERY_INPUT_LINE_OBJECT_QTY 1
#define EXPECTED_NODE_INPUT_LINE_OBJECT_QTY 2

typedef std::unique_ptr<ShortestPathAlgorithm> ShortestPathAlgorithmPtr;

int main() {
    Graph graph = GraphFactory::makeGraphFromReadData("Testing/test_file_input.txt");
    ShortestPathAlgorithmPtr ch = SPAFactory::makeAlgorithm(SPAType::ContractionHierarchiesSPA, graph);
    ShortestPathAlgorithmPtr dijkstra = SPAFactory::makeAlgorithm(SPAType::DijkstraSPA, graph);

    int queryQty;
    std::cout << "Enter the number of search queries: ";

    assert(scanf("%d", &queryQty) == EXPECTED_QUERY_INPUT_LINE_OBJECT_QTY);

    std::cout << "Enter below the nodes to query in the format 'start_node target_node'" << std::endl;

    for (int i = 0; i < queryQty; i++) {
        int startNode, endNode;
        assert(scanf("%d %d", &startNode, &endNode) == EXPECTED_NODE_INPUT_LINE_OBJECT_QTY);

        int chAns = ch->computeDistance(startNode - 1, endNode - 1);
        int dijkAns = dijkstra->computeDistance(startNode - 1, endNode - 1);

        std::cout << "CH Ans: " << chAns << ",       " << "Dijk Ans: " << dijkAns;

        if (chAns != dijkAns)   std::cout << "    " << "Mismatch!";

        std::cout << std::endl;
    }
}