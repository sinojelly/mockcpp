
#include <testngpp/testngpp.hpp>

FIXTURE(CFoo, 中文用例样例())
{
	TEST(中文())
	{
		INFO("yes");
	}

	TEST(测试: 1+1 = 2)
	{
		ASSERT_EQ(2, 1+1);
	}

	TEST(__DO__/__CLEANUP__/__DONE__)
	{
		__DO__
			FAIL("I'm gonna fail");
		    WARN("I should not be shown");
		__CLEANUP__
			INFO("I should be shown always");
		__DONE__
	}

	TEST(again: __DO__/__CLEANUP__/__DONE__)
	{
		__DO__
			INFO("I'm ok");
		__CLEANUP__
			INFO("I should be shown always");
		__DONE__
	}

	TEST(EXPECT_XXX)
	{
		EXPECT_TRUE(false);
		EXPECT_FALSE(true);
		EXPECT_EQ(1, 2);
		EXPECT_NE(1, 1);
	}
};