#include "../src/ownAlgorithm/depthFirstAlgorithm.h"
#include <gtest/gtest.h>
#include <stdexcept>

using namespace std;
class SecondDraftAlgorithmTest : public ::testing::Test {
  protected:
	void SetUp() override {}

	void TearDown() override {}
};

TEST_F(SecondDraftAlgorithmTest, SmallPathUnlimitedTime) {
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
	Node n10(10);
	Node n11(11);
	Node n12(12);

	Edge n1n2(1, 2, 1.0);
	Edge n1n7(1, 7, 2.0);
	n1.AddEdge(n1n2);
	n1.AddEdge(n1n7);

	Edge n2n3(2, 3, 3.0);
	Edge n2n4(2, 4, 4.0);
	n2.AddEdge(n2n3);
	n2.AddEdge(n2n4);

	Edge n4n5(4, 5, 5.0);
	Edge n4n6(4, 6, 6.0);
	n4.AddEdge(n4n5);
	n4.AddEdge(n4n6);

	Edge n7n8(7, 8, 3.0);
	Edge n7n11(7, 11, 4.0);
	n7.AddEdge(n7n8);
	n7.AddEdge(n7n11);

	Edge n8n9(8, 9, 5.0);
	Edge n9n10(9, 10, 6.0);
	n8.AddEdge(n8n9);
	n9.AddEdge(n9n10);

	Edge n11n12(11, 12, 7.0);
	n11.AddEdge(n11n12);

	Edge n3n1(3, 1, 1.0);
	n3.AddEdge(n3n1);

	Edge n4n1(4, 1, 1.0);
	n4.AddEdge(n4n1);

	Edge n5n1(5, 1, 1.0);
	n5.AddEdge(n5n1);

	Edge n6n1(6, 1, 1.0);
	n6.AddEdge(n6n1);

	Edge n8n1(8, 1, 1.0);
	n8.AddEdge(n8n1);

	Edge n9n1(9, 1, 1.0);
	n9.AddEdge(n9n1);

	Edge n10n1(10, 1, 1.0);
	n10.AddEdge(n10n1);

	Edge n11n1(11, 1, 1.0);
	n11.AddEdge(n11n1);

	Edge n12n1(12, 1, 1.0);
	n12.AddEdge(n12n1);

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
	graph.AddNode(n12);

	vector<Node> expectedPath;
	expectedPath.push_back(n1);
	expectedPath.push_back(n7);
	expectedPath.push_back(n8);
	expectedPath.push_back(n9);
	expectedPath.push_back(n10);
	expectedPath.push_back(n1);

	DFSAlgorithm algorithm(timeInterval, graph);
	vector<Node> actualPath = algorithm.SecondDraft();
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
}

TEST_F(SecondDraftAlgorithmTest, SmallPathLimitedTime) {
	bool identical = true;
	double timeInterval = 12;

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
	Node n12(12);

	Edge n1n2(1, 2, 1.0);
	Edge n1n7(1, 7, 2.0);

	Edge n2n3(2, 3, 3.0);
	Edge n2n4(2, 4, 4.0);

	Edge n4n5(4, 5, 6.0);
	Edge n4n6(4, 6, 6.0);

	Edge n7n8(7, 8, 3.0);
	Edge n7n11(7, 11, 4.0);
	Edge n8n9(8, 9, 5.0);
	Edge n9n10(9, 10, 6.0);

	Edge n11n12(11, 12, 7.0);

	n1.AddEdge(n1n2);
	n1.AddEdge(n1n7);
	n2.AddEdge(n2n3);
	n2.AddEdge(n2n4);
	n4.AddEdge(n4n5);
	n4.AddEdge(n4n6);
	n7.AddEdge(n7n8);
	n7.AddEdge(n7n11);
	n8.AddEdge(n8n9);
	n9.AddEdge(n9n10);
	n11.AddEdge(n11n12);

	Edge n3n1(3, 1, 1.0);
	n3.AddEdge(n3n1);

	Edge n4n1(4, 1, 1.0);
	n4.AddEdge(n4n1);

	Edge n5n1(5, 1, 1.0);
	n5.AddEdge(n5n1);

	Edge n6n1(6, 1, 1.0);
	n6.AddEdge(n6n1);

	Edge n8n1(8, 1, 1.0);
	n8.AddEdge(n8n1);

	Edge n9n1(9, 1, 1.0);
	n9.AddEdge(n9n1);

	Edge n10n1(10, 1, 1.0);
	n10.AddEdge(n10n1);

	Edge n11n1(11, 1, 1.0);
	n11.AddEdge(n11n1);

	Edge n12n1(12, 1, 1.0);
	n12.AddEdge(n12n1);

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
	graph.AddNode(n12);

	vector<Node> expectedPath;
	expectedPath.push_back(n1);
	expectedPath.push_back(n2);
	expectedPath.push_back(n4);
	expectedPath.push_back(n5);
	expectedPath.push_back(n1);

	DFSAlgorithm algorithm(timeInterval, graph);
	vector<Node> actualPath = algorithm.SecondDraft();
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
