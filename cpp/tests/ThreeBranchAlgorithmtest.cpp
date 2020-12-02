#include "../src/ownAlgorithm/threeBranchAlgorithm.h"
#include <gtest/gtest.h>
#include <stdexcept>

using namespace std;
class ThreeBranchAlgorithmTest : public ::testing::Test {
  protected:
	void SetUp() override {}

	void TearDown() override {}
};

TEST_F(ThreeBranchAlgorithmTest, SmallPathUnlimitedTime) {
	bool identical = true;
	double timeInterval = 100;

	Graph graph;
	Node n1(1);
	Node n2(2);
	Node n3(3);
	Node n4(4);
	Node n5(5);
	Node n6(6);
	Node n7(7);
	Node n8(8);

	Edge n1n2(1, 2, 1.0);
	Edge n1n3(1, 3, 2.0);
	Edge n1n4(1, 4, 3.0);
	n1.AddEdge(n1n2);
	n1.AddEdge(n1n3);
	n1.AddEdge(n1n4);

	Edge n2n5(2, 5, 5.0);
	n2.AddEdge(n2n5);

	Edge n3n6(3, 6, 4.0);
	n3.AddEdge(n3n6);

	Edge n4n7(4, 7, 3.0);
	n4.AddEdge(n4n7);

	Edge n7n8(7, 8, 2.0);
	n7.AddEdge(n7n8);

	Edge n5n1(5, 1, 1.0);
	n5.AddEdge(n5n1);

	Edge n6n1(6, 1, 1.0);
	n6.AddEdge(n6n1);

	Edge n7n1(7, 1, 1.0);
	n7.AddEdge(n7n1);

	Edge n8n1(8, 1, 1.0);
	n8.AddEdge(n8n1);

	graph.AddNode(n1);
	graph.AddNode(n2);
	graph.AddNode(n3);
	graph.AddNode(n4);
	graph.AddNode(n5);
	graph.AddNode(n6);
	graph.AddNode(n7);
	graph.AddNode(n8);

	vector<Node> expectedPath;
	expectedPath.push_back(n1);
	expectedPath.push_back(n4);
	expectedPath.push_back(n7);
	expectedPath.push_back(n8);
	expectedPath.push_back(n1);

	ThreeBranchAlgorithm algorithm(timeInterval, graph);
	vector<Node> actualPath = algorithm.ThirdDraft();
	cout << "Actual path size:   " << actualPath.size() << endl;
	cout << "Expected path size: " << expectedPath.size() << endl;
	for (int i = 0; i < actualPath.size(); i++) {
		cout << expectedPath[i].ID << "   " << actualPath[i].ID << endl;
	}
	if (actualPath.size() == expectedPath.size()) {
		for (int i = 0; i < expectedPath.size(); i++) {
			if (expectedPath[i].ID != actualPath[i].ID) {
				identical = false;
			}
		}
	} else {
		identical = false;
	}
	ASSERT_TRUE(identical);
}