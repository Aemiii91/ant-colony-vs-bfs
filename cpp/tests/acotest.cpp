#include <gtest/gtest.h>

#include <chrono>
#include <locale.h>
#include <stdexcept>
#include <vector>

#include <aco/AntColony.hpp>
#include <graph/graph.h>
#include <jsonparser.h>
#include <utils/ArgumentParser.hpp>

using namespace aco;

class ACOTest : public ::testing::Test {
  public:
	Graph graph;

  protected:
	void SetUp() override {
		setlocale(LC_ALL, "");

		JsonParser json;
		this->graph = json.ParseData("../data/matrix10");
	}

	void TearDown() override {}
};

TEST_F(ACOTest, AntColonyTest) {
	// Save cout's buffer
	std::streambuf *sbuf = std::cout.rdbuf();
	std::stringstream buffer;

	// Redirect cout to stringstream buffer
	std::cout.rdbuf(buffer.rdbuf());

	// remove colors from output
	termcolor::setEnabled(false);

	int test_argc = 10;
	char *test_argv[] = {
		const_cast<char *>("routeplanner"), const_cast<char *>("aco"),
		const_cast<char *>("--ants"),       const_cast<char *>("20"),
		const_cast<char *>("--iterations"), const_cast<char *>("50"),
		const_cast<char *>("--colonies"),   const_cast<char *>("10"),
		const_cast<char *>("--cost"),       const_cast<char *>("4000")};

	utils::ArgumentParser args(test_argc, test_argv);

	AntColony::run(&this->graph, &args);

	// redirect cout to its old self
	std::cout.rdbuf(sbuf);

	std::vector<std::string> content;
	for (std::string line; std::getline(buffer, line);) {
		content.push_back(line);
		std::cout << line << std::endl;
	}

	std::string result = content[2];

	ASSERT_EQ("( 3550, 8 )", result);
}

TEST_F(ACOTest, ColonyTest) {
	int colonies = 10;
	Parameters params;
	params.antCount = 20;
	params.iterations = 50;
	params.costConstraint = 4000.0;

	Colony colony(&this->graph, params);

	Solution solution = colony.Solve(colonies);

	std::cout << solution;

	ASSERT_EQ(8, solution.score);
}

TEST_F(ACOTest, AntTest) {
	Parameters params;
	MatrixData matrixData(&this->graph, &params);

	std::vector<int> allVertices;
	size_t size = this->graph.nodelist.size();
	for (int i = 0; i < size; i++) {
		allVertices.push_back(i);
	}

	Ant ant(allVertices, 0, &params, &matrixData);

	// start timer
	auto start = std::chrono::high_resolution_clock::now();

	ant.Run();

	// stop timer
	auto stop = std::chrono::high_resolution_clock::now();

	bool result = ant.isComplete();
	bool expected = true;

	// calculate and print runtime
	auto duration =
		std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << (double)duration.count() / 1000 << " ms" << std::endl;

	std::cout << ant.solution();

	ASSERT_EQ(expected, result);
}

TEST_F(ACOTest, MatrixDataTest) {
	Parameters params;
	params.evaporation = 0.5;

	MatrixData matrixData(&this->graph, &params);

	int fromIndex = 0;
	int toIndex = 1;
	double heuristic =
		std::pow(1.0 / matrixData.Cost(fromIndex, toIndex), params.beta);

	double probBefore = matrixData.Probability(fromIndex, toIndex);
	double expectedBefore = std::pow(1.0, params.alpha) * heuristic;

	matrixData.EvaporatePheromone();

	double probAfter = matrixData.Probability(fromIndex, toIndex);
	double expectedAfter = std::pow(0.5, params.alpha) * heuristic;

	ASSERT_EQ(true,
			  (probBefore == expectedBefore) && (probAfter == expectedAfter));
}

TEST_F(ACOTest, SolutionTest) {
	Solution solution(3550, {0, 3, 8, 9, 6, 2, 1, 4, 0});

	int expected = 8;
	int result = solution.score;

	ASSERT_EQ(expected, result);
}
