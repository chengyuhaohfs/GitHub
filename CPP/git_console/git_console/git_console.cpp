// git_console.cpp : �������̨Ӧ�ó������ڵ㡣
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

