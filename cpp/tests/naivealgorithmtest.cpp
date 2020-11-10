#include "../src/ownAlgorithm/naiveAlgorithm.h"
#include <gtest/gtest.h>
#include <stdexcept>

using namespace std;
class NaiveAlgorithmTest : public ::testing::Test {
  protected:
	void SetUp() override {}

	void TearDown() override {}
};

TEST_F(NaiveAlgorithmTest, SmallPathUnevenConstraint) {
	bool identical = true;
	double timeInterval = 11;
	// Mock graph
	Graph graph;
	Node n1(1);
	Node n2(2);
	Node n3(3);

	// edges for n1
	Edge e1(1, 2, 5.0);
	Edge e2(1, 3, 5.0);
	n1.AddEdge(e1);
	n1.AddEdge(e2);

	// edges for n2
	Edge e3(2, 1, 5.0);
	Edge e4(2, 3, 5.0);
	n2.AddEdge(e3);
	n2.AddEdge(e4);
	// edges for n3
	Edge e5(3, 1, 5.0);
	Edge e6(3, 2, 5.0);
	n3.AddEdge(e5);
	n3.AddEdge(e6);

	graph.AddNode(n1);
	graph.AddNode(n2);
	graph.AddNode(n3);

	// created expected path
	vector<Node> expectedPath;
	expectedPath.push_back(n1);
	expectedPath.push_back(n2);
	expectedPath.push_back(n1);

	NaiveAlgorithm naive(timeInterval, graph);
	vector<Node> actualPath = naive.FirstDraftAlgo();
	for (int i = 0; i < expectedPath.size(); i++) {
		if (expectedPath[i].ID != actualPath[i].ID) {
			identical = false;
		}
	}
	ASSERT_TRUE(identical);
}

TEST_F(NaiveAlgorithmTest, SmallPathTestEvenConstraint) {
	bool identical = true;
	double timeInterval = 15;
	// Mock graph
	Graph graph;
	Node n1(1);
	Node n2(2);
	Node n3(3);

	// edges for n1
	Edge e1(1, 2, 5.0);
	Edge e2(1, 3, 5.0);
	n1.AddEdge(e1);
	n1.AddEdge(e2);

	// edges for n2
	Edge e3(2, 1, 5.0);
	Edge e4(2, 3, 5.0);
	n2.AddEdge(e3);
	n2.AddEdge(e4);
	// edges for n3
	Edge e5(3, 1, 5.0);
	Edge e6(3, 2, 5.0);
	n3.AddEdge(e5);
	n3.AddEdge(e6);

	graph.AddNode(n1);
	graph.AddNode(n2);
	graph.AddNode(n3);

	// created expected path
	vector<Node> expectedPath;
	expectedPath.push_back(n1);
	expectedPath.push_back(n2);
	expectedPath.push_back(n3);
	expectedPath.push_back(n1);

	NaiveAlgorithm naive(timeInterval, graph);
	vector<Node> actualPath = naive.FirstDraftAlgo();
	for (int i = 0; i < expectedPath.size(); i++) {
		if (expectedPath[i].ID != actualPath[i].ID) {
			identical = false;
		}
	}
	ASSERT_TRUE(identical);
	ASSERT_TRUE(true);
}
