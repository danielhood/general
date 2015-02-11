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

} // namespace

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
