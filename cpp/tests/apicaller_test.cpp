#include "../apicaller/src/opencaching.hpp"
#include "../apicaller/src/openroute.hpp"
#include <gtest/gtest.h>
#include <regex>
#include <stdexcept>
#include <string>

using namespace apicaller;

class apicallerTest : public ::testing::Test {
  protected:
	void SetUp() override {}

	void TearDown() override {}
};

TEST_F(apicallerTest, OpencachingSearchTest) {
	std::string json_data = opencaching::search(52.518848, 13.399411);

	std::cout << json_data << std::endl;

	bool result = true;
	bool expected = true;
	ASSERT_EQ(expected, result);
}

TEST_F(apicallerTest, OpenrouteMatrixTest) {
	std::string locations = "[[9.70093,48.477473],[9.207916,49.153868],[37."
							"573242,55.801281],[115.663757,38.106467]]";
	std::string json_data = openroute::matrix(locations);

	std::cout << json_data << std::endl;

	bool result = true;
	bool expected = true;
	ASSERT_EQ(expected, result);
}

TEST_F(apicallerTest, OpenrouteMatrixOtmTest) {
	std::string locations = "[[9.70093,48.477473],[9.207916,49.153868],[37."
							"573242,55.801281],[115.663757,38.106467]]";
	std::string json_data = openroute::matrixOTM(locations, 0);

	std::cout << json_data << std::endl;

	bool result = true;
	bool expected = true;
	ASSERT_EQ(expected, result);
}

TEST_F(apicallerTest, OpenrouteMatrixMtoTest) {
	std::string locations = "[[9.70093,48.477473],[9.207916,49.153868],[37."
							"573242,55.801281],[115.663757,38.106467]]";
	std::string json_data = openroute::matrixMTO(locations, 3);

	std::cout << json_data << std::endl;

	bool result = true;
	bool expected = true;
	ASSERT_EQ(expected, result);
}