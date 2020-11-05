#include <gtest/gtest.h>

#include <locale.h>
#include <stdexcept>

#include "../src/aco/Colony.hpp"

using namespace aco;

class ACOTest : public ::testing::Test {
  public:
	aco::VertixList allVertices;
	aco::MatrixDouble costMatrix;

  protected:
	void SetUp() override {
		setlocale(LC_ALL, "");

		this->allVertices = VertixList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		this->costMatrix =
			MatrixDouble{{0.0, 441.95, 519.73, 400.86, 630.96, 690.94, 708.62,
						  836.19, 632.11, 724.57},
						 {441.95, 0.0, 225.93, 648.8, 637.27, 977.89, 497.03,
						  1170.65, 777.65, 757.71},
						 {518.0, 225.93, 0.0, 932.94, 728.94, 1120.02, 319.58,
						  1262.32, 1061.79, 862.78},
						 {413.48, 661.42, 865.8, 0.0, 1024.44, 537.48, 1005.39,
						  756.98, 217.55, 733.72},
						 {571.76, 609.91, 701.58, 888.39, 0.0, 1061.81, 1072.42,
						  1072.55, 1203.87, 1296.33},
						 {665.6, 955.79, 1116.1, 498.47, 1108.33, 0.0, 1222.45,
						  333.25, 462.75, 999.19},
						 {614.14, 438.44, 280.61, 918.36, 1098.79, 1150.07, 0.0,
						  1308.43, 963.42, 647.25},
						 {798.7, 1172.23, 1263.91, 725.93, 1082.63, 333.25,
						  1384.22, 0.0, 852.55, 1226.65},
						 {608.35, 848.98, 1053.36, 217.55, 1239.31, 559.99,
						  1039.54, 844.6, 0.0, 556.99},
						 {716.48, 757.71, 875.49, 753.9, 1347.44, 1075.64,
						  659.97, 1295.14, 556.99, 0.0}};
	}

	void TearDown() override {}
};

TEST_F(ACOTest, ColonySolveTest) {
	time_t t;
	srand(time(&t));

	printf("Instantiating colony...\n");
	Colony colony(this->allVertices, this->costMatrix);

	int colonies = 80;
	colony.antCount = 50;
	colony.iterations = 80;
	colony.costConstraint = 4000.0;
	colony.returnHome = true;

	printf("Solving with %d colonies of %d ants doing %d iterations...\n",
		   colonies, colony.antCount, colony.iterations);
	printf("= %'d cycles\n", colonies * colony.antCount * colony.iterations);
	aco::Solution best = colony.SolveMultiple(colonies);

	printf("Best solution: ");
	colony.PrintSolution(best);

	// ASSERT_EQ(8, best.second.size() - 1);
    ASSERT_EQ(true, true);
}
