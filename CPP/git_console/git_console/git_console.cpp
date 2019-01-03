// git_console.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestTools.h"

using namespace std;

#define MY_MSG 1001
DWORD threadFunc(LPVOID lpParam);
DWORD CloseMessageBox(LPVOID lpParam);

int _tmain(int argc, _TCHAR* argv[])
{
	CTestTools mTools;
	CString csCurDir = mTools.GetCurDir();
	CString csInput = csCurDir + "Input.txt";

	CString csInfo = "";
	mTools.GetFileContent(csInput, csInfo);
	
	ostream_iterator<string> oo(cout);
	// ostream_iterator<T> 可以写入类型为 T 的值
	*oo = "hello world";
	// 向控制台输出 hello world
	cout << "how are you" << endl;

	return H_PASS;
}

DWORD CloseMessageBox(LPVOID lpParam)
{
	Sleep(1000);
	keybd_event(VK_RETURN, 0, KEYEVENTF_EXTENDEDKEY|0, 0);
	keybd_event(VK_RETURN, 0, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 0);

	return 0;
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

