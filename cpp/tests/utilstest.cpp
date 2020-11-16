#include <gtest/gtest.h>

#include <utils/ArgumentParser.hpp>
#include <utils/vector.hpp>

using namespace utils;

class UtilsTest : public ::testing::Test {
  protected:
	void SetUp() override {
		setlocale(LC_ALL, "");
	}

	void TearDown() override {}
};

TEST_F(UtilsTest, ArgumentParserTest) {
	int test_argc = 8;
	char *test_argv[] = {
		const_cast<char *>("self"),  const_cast<char *>("mystring"),
		const_cast<char *>("abc"),   const_cast<char *>("myint"),
		const_cast<char *>("3550"),  const_cast<char *>("mydouble"),
		const_cast<char *>("40.98"), const_cast<char *>("myflag")};

	utils::ArgumentParser args(test_argc, test_argv);

	std::string mystring;
	args.Get("mystring", &mystring);

	int myint;
	args.Get("myint", &myint);

	double mydouble;
	args.Get("mydouble", &mydouble);

	bool myflag = args.Exists("myflag");

	ASSERT_EQ("abc", mystring);
	ASSERT_EQ(3550, myint);
	ASSERT_GT(0.001, std::abs(40.98 - mydouble));
	ASSERT_TRUE(myflag);
}

TEST_F(UtilsTest, VectorRemoveValueTest) {
	std::vector<int> myvec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	vector::removeValue(&myvec, 1);

	int expected = 2;
	int result = myvec.at(1);

	ASSERT_EQ(expected, result);
}

TEST_F(UtilsTest, VectorMatchTest) {
	std::vector<int> myvec{12, 32, 63, 34, 15, 96, 57, 28, 59};

	int expected = 3;
	int result =
		utils::vector::match(&myvec, [](int *value) { return *value == 34; });

	ASSERT_EQ(expected, result);
}
