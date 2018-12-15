// git_console.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestTools.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	CTestTools mTools;
	CString csCurDir = mTools.GetCurDir();
	CString csInput = csCurDir + "Input.txt";

	CString csInfo = "";
	mTools.GetFileContent(csInput, csInfo);

	CStringArray ca_finds;
	string strInfo = csInfo.GetBuffer(csInfo.GetLength());
	csInfo.ReleaseBuffer();
	// string strRegex = "(It).*(UNIX).*(X\\.)";
	string strRegex = "CRC32\\s+for\\s+data:\\s+(\\w+)";

	ca_finds.RemoveAll();
	BOOL bMatched = mTools.PickStringWithRegex(csInfo, ca_finds, strRegex);
	if (!bMatched)
	{
		cout << "Find nothing!\n";

		return H_FAIL;
	}

	for (int index = 0; index < ca_finds.GetSize(); index++)
	{
		cout << ca_finds.GetAt(index) << endl;
	}

	char chstr[] = "I'm from china, my name is hufusheng";
	char *chptr = chstr;
	CAutopara<char> mParam(100);
	mParam.Copy(chptr, strlen(chptr));

	cout << mParam.m_pVal << endl;

	return H_PASS;
}

