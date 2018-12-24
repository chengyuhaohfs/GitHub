// git_console.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestTools.h"

using namespace std;

#define MY_MSG 1001
DWORD threadFunc(LPVOID lpParam);

int _tmain(int argc, _TCHAR* argv[])
{
	CTestTools mTools;
	CString csCurDir = mTools.GetCurDir();
	CString csInput = csCurDir + "Input.txt";

	CString csInfo = "";
	mTools.GetFileContent(csInput, csInfo);

	

	return H_PASS;
}

DWORD threadFunc(LPVOID lpParam)
{
	MSG m_msg;
	ZeroMemory(&m_msg, sizeof(m_msg));
	while (1)
	{
		if (PeekMessage(&m_msg, (HWND)-1, 0, 0, PM_NOREMOVE))
		{
			CString csMsg = "";
			csMsg.Format("I get a message %d, %d, %d.", m_msg.message, m_msg.lParam, m_msg.wParam);
			if (IDCANCEL == AfxMessageBox(csMsg, MB_OKCANCEL))
			{
				break;
			}
		}

		Sleep(100);
	}

	return 0;
}

