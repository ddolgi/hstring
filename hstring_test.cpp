#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "HString.h"

using namespace std;

TEST(HString_test, Left)
{
	string a ="This is test.";
	HString h(a.c_str());

	cout << h.Left(2).GetStr()<<endl;
}
