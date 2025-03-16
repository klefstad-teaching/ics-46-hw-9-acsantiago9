#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(DjikstrasTest, Test) {
	Graph test_graph;
	file_to_graph("src/small.txt", test_graph);
	vector<int> previous;
	vector<int> dijkstra = dijkstra_shortest_path(test_graph, 0, previous);
	for (int i = 0; i < test_graph.numVertices; ++i) {
		vector<int> path = extract_shortest_path(dijkstra, previous, i);
		print_path(path, dijkstra[i]);
	}
	vector<int> result = {0, 3, 6, 1};
	for (int i = 0; i < 4; ++i)
		EXPECT_EQ(dijkstra[i], result[i]);
}
