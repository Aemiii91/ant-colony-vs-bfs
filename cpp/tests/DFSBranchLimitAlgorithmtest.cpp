#include "../src/ownAlgorithm/DFSBranchLimitAlgorithm.h"
#include <gtest/gtest.h>
#include <stdexcept>

using namespace std;
class DFSBranchLimitAlgorithmTest : public ::testing::Test {
  protected:
	void SetUp() override {}

	void TearDown() override {}
};

TEST_F(DFSBranchLimitAlgorithmTest, SmallPathUnlimitedTime) {
	bool identical = true;
	double timeInterval = 10;

	Graph graph;
	Node n1(1);
	Node n2(2);
	Node n3(3);
	Node n4(4);
	Node n5(5);
	Node n6(6);
	Node n7(7);
	Node n8(8);
	Node n9(9);
	Node n10(10);
	Node n11(11);

	Edge n1n2(1, 2, 1.0);
	Edge n1n3(1, 3, 2.0);
	Edge n1n4(1, 4, 3.0);
	n1.AddEdge(n1n2);
	n1.AddEdge(n1n3);
	n1.AddEdge(n1n4);

	Edge n2n5(2, 5, 10.0);
	n2.AddEdge(n2n5);

	Edge n3n6(3, 6, 5.0);
	Edge n3n7(3, 7, 6.0);
	n3.AddEdge(n3n6);
	n3.AddEdge(n3n7);

	Edge n4n8(4, 8, 3.0);
	Edge n4n9(4, 9, 2.0);
	Edge n4n10(4, 10, 1.0);
	n4.AddEdge(n4n8);
	n4.AddEdge(n4n9);
	n4.AddEdge(n4n10);

	Edge n8n11(8, 11, 1.0);
	n8.AddEdge(n8n11);

	Edge n5n1(5, 1, 1.0);
	n5.AddEdge(n5n1);
	Edge n6n1(6, 1, 1.0);
	n6.AddEdge(n6n1);
	Edge n7n1(7, 1, 1.0);
	n7.AddEdge(n7n1);
	Edge n8n1(8, 1, 1.0);
	n8.AddEdge(n8n1);
	Edge n9n1(9, 1, 1.0);
	n9.AddEdge(n9n1);
	Edge n10n1(10, 1, 1.0);
	n10.AddEdge(n10n1);
	Edge n11n1(11, 1, 1.0);
	n11.AddEdge(n11n1);

	graph.AddNode(n1);
	graph.AddNode(n2);
	graph.AddNode(n3);
	graph.AddNode(n4);
	graph.AddNode(n5);
	graph.AddNode(n6);
	graph.AddNode(n7);
	graph.AddNode(n8);
	graph.AddNode(n9);
	graph.AddNode(n10);
	graph.AddNode(n11);

	vector<Node> expectedPath;
	expectedPath.push_back(n1);
	expectedPath.push_back(n4);
	expectedPath.push_back(n8);
	expectedPath.push_back(n11);
	expectedPath.push_back(n1);

	DFSBranchLimitAlgorithm algorithm(timeInterval, graph);
	int limit = 3;
	vector<Node> actualPath = algorithm.FourthDraft(limit);
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

TEST_F(DFSBranchLimitAlgorithmTest, SevenChildrenTest) {
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
	Node n9(9);

	Edge n1n2(1, 2, 1.0);
	Edge n1n3(1, 3, 2.0);
	Edge n1n4(1, 4, 3.0);
	Edge n1n5(1, 5, 4.0);
	Edge n1n6(1, 6, 5.0);
	Edge n1n7(1, 7, 6.0);
	Edge n1n8(1, 8, 7.0);
	n1.AddEdge(n1n2);
	n1.AddEdge(n1n3);
	n1.AddEdge(n1n4);
	n1.AddEdge(n1n5);
	n1.AddEdge(n1n6);
	n1.AddEdge(n1n7);
	n1.AddEdge(n1n8);

	Edge n8n9(8, 9, 5.0);
	n8.AddEdge(n8n9);

	Edge n2n1(2, 1, 1.0);
	n2.AddEdge(n2n1);
	Edge n3n1(3, 1, 1.0);
	n3.AddEdge(n3n1);
	Edge n4n1(4, 1, 1.0);
	n4.AddEdge(n4n1);
	Edge n5n1(5, 1, 1.0);
	n5.AddEdge(n5n1);
	Edge n6n1(6, 1, 1.0);
	n6.AddEdge(n6n1);
	Edge n7n1(7, 1, 1.0);
	n7.AddEdge(n7n1);
	Edge n8n1(8, 1, 1.0);
	n8.AddEdge(n8n1);
	Edge n9n1(9, 1, 1.0);
	n9.AddEdge(n9n1);

	graph.AddNode(n1);
	graph.AddNode(n2);
	graph.AddNode(n3);
	graph.AddNode(n4);
	graph.AddNode(n5);
	graph.AddNode(n6);
	graph.AddNode(n7);
	graph.AddNode(n8);
	graph.AddNode(n9);

	vector<Node> expectedPath;
	expectedPath.push_back(n1);
	expectedPath.push_back(n8);
	expectedPath.push_back(n9);
	expectedPath.push_back(n1);

	DFSBranchLimitAlgorithm algorithm(timeInterval, graph);
	int limit = 7;
	vector<Node> actualPath = algorithm.FourthDraft(limit);
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
