#include <gtest/gtest.h>

#include <locale.h>
#include <stdexcept>

#include "../src/aco/Colony.hpp"
#include "../src/graph/graph.h"
#include "../src/jsonparser.h"

using namespace aco;

class ACOTest : public ::testing::Test {
  public:
	// std::vector<int> allVertices;
	// aco::MatrixDouble costMatrix;
	Graph graph;

  protected:
	void SetUp() override {
		setlocale(LC_ALL, "");

		JsonParser parser;
		this->graph = parser.ParseData("../data/matrix10");
	}

	void TearDown() override {}
};

TEST_F(ACOTest, ColonySolveTest) {
	time_t t;
	srand(time(&t));

	Parameters params;
	int colonies = 10;
	params.antCount = 20;
	params.iterations = 50;
	params.costConstraint = 4000.0;

	Colony colony(&this->graph, params);

	aco::Solution solution = colony.Solve(colonies);

	std::cout << solution;

	ASSERT_EQ(8, solution.score);
}
