#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "../src/poi.h"


using namespace std;

class BasicTest : public ::testing::Test {
    protected:
        void SetUp() override {}

        void TearDown() override {}
};

TEST_F(BasicTest, BasicExample) {
    ASSERT_EQ(1,1);
}

TEST_F(BasicTest, ImportPoiTest) {
    fstream fileStream;
    PoiImport importer;
    fileStream.open("../tests/testfile.csv");
    importer.ImportPoi(&fileStream);

    poi ExpectedPoi;
    ExpectedPoi.name = "Country, city";
    ExpectedPoi.lattitude_radian = 0.123;
    ExpectedPoi.longitude_radian = 0.321;
    ExpectedPoi.num_links = 1;
    ExpectedPoi.links = "Some link";
    ExpectedPoi.num_categories = 12;
    ExpectedPoi.categories = "Some categories;";

    poi ActualPoi;
    if(!importer.importedPoi.empty()) {
        ActualPoi = importer.importedPoi.back();
    }

    EXPECT_EQ(ActualPoi.name, ExpectedPoi.name);
    EXPECT_EQ(ActualPoi.categories, ExpectedPoi.categories);
    EXPECT_EQ(ActualPoi.num_categories, ExpectedPoi.num_categories);
    EXPECT_EQ(ActualPoi.links, ExpectedPoi.links);
    EXPECT_EQ(ActualPoi.longitude_radian, ExpectedPoi.longitude_radian);
    EXPECT_EQ(ActualPoi.lattitude_radian, ExpectedPoi.lattitude_radian);
}
