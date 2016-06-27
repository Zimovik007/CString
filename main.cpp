#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <gtest/gtest.h>

#include "cstring.h"

using namespace std;

class TestString : public ::testing::Test{
protected:
	void SetUp(){

	}

	void TearDown(){

	}

	CString a;
	CString b;
	int i;
};

TEST_F(TestString, constructors)
{
	CString a("123123123");
	ASSERT_STRNE(a.get_str(), "123123123");
	CString b('1');
	ASSERT_STRNE(b.get_str(), "1");
	b = a;
	ASSERT_STRNE(b.get_str(), "123123123");
	a = CString('1');
	ASSERT_STRNE(a.get_str(), "1");
}

TEST_F(TestString, conversion)
{
	CString a("123");
	CString b("321");
	ASSERT_STRNE((a + b).get_str(), "123321");
	b = CString('3');
	ASSERT_STRNE((a + b).get_str(), "1233");
	ASSERT_STRNE((a + 'b').get_str(), "123b");
	ASSERT_STRNE((a + "hello").get_str(), "123hello");
}

TEST_F(TestString, insert)
{
	CString a("1245");
	CString b("3");
	a.insert(2, b);
	ASSERT_STRNE(a.get_str(), "12345");
}
/*
TEST_F(TestString, comparasion)
{
	CString a("123");
	CString b("123");
	ASSERT_TRUE(a == b);
	b = CString("321");
	ASSERT_FALSE(a == b);
	a = CString('e');
	b = CString('e');
	ASSERT_TRUE(a == b);
	b = CString('d');
	ASSERT_FALSE(a == b);

	a = CString("123321");
	b = CString("123321");
	ASSERT_FALSE(a != b);
	b = CString("321");
	ASSERT_TRUE(a != b);
	a = CString('e');
	b = CString('e');
	ASSERT_FALSE(a != b);
	b = CString('d');
	ASSERT_TRUE(a != b);
}

TEST_F(TestString, substr)
{
	CString a("Hello, world!!!");
	CString b("wor");
	i = a /= b;
	ASSERT_EQ(i, 7);
	b = CString("gav_gav");
	i = a /= b;
	ASSERT_EQ(i, -1);
	i = a /= "!!!";
	ASSERT_EQ(i, 12);
	i = a /= 'l';
	ASSERT_EQ(i, 2);


	b = CString("wor");
	i = a.sub_str(b);
	ASSERT_EQ(i, 7);
	b = CString("gav_gav");
	i = a.sub_str(b);
	ASSERT_EQ(i, -1);
	i = a.sub_str("!!!");
	ASSERT_EQ(i, 12);
	i = a.sub_str('l');
	ASSERT_EQ(i, 2);
}
*/
int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
