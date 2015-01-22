#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {

class TestTest : public ::testing::Test {
protected:
	TestTest() {}
	virtual ~TestTest() {
	}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}	
};

TEST_F(TestTest, SimplePass) {
	int value = 0;
	EXPECT_EQ(0, value);
}

TEST_F(TestTest, SimplePass1) {
	int value = 0;
	EXPECT_EQ(0, value);
}

TEST_F(TestTest, SimplePass2) {
	int value = 0;
	EXPECT_EQ(0, value);
}

TEST_F(TestTest, SimplePass3) {
	int value = 0;
	EXPECT_EQ(0, value);
}

TEST_F(TestTest, SimpleFail1) {
	int value = 2;
EXPECT_EQ(1, value);
}

TEST_F(TestTest, SimpleFail2) {
	int value = 2;
	EXPECT_EQ(1, value);
}

TEST_F(TestTest, SimpleFail3) {
	int value = 2;
	EXPECT_EQ(1, value);
}

TEST_F(TestTest, SimpleFail4) {
	int value = 2;
	EXPECT_EQ(1, value);
}



}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
