// git_console.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestTools.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	short s_array[] = {1, 2, 3};
	MY_VECTOR(short, s_array, mVector);

	vector<short> v_short = mVector.GetVector();

	return 0;
}

