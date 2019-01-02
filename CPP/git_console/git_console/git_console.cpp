// git_console.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestTools.h"

using namespace std;

#define MY_MSG 1001
DWORD threadFunc(LPVOID lpParam);
DWORD ActiveWindow(LPVOID lpParam);
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

	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ActiveWindow, "", 0, NULL);
	if (INVALID_HANDLE_VALUE == hThread)
	{
		return H_FAIL;
	}

	MessageBox(NULL, "hello world", "Tips", MB_OK|MB_ICONINFORMATION);

	CloseHandle(hThread);
	return H_PASS;
}

DWORD ActiveWindow(LPVOID lpParam)
{
	if (NULL == lpParam)
	{
		return H_FAIL;
	}

	HWND hwnd = NULL;
	char* chWinName = (char*)lpParam;
	do 
	{
		hwnd = FindWindow(NULL, chWinName);
		if (NULL != hwnd)
		{
			std::cout << "Find the window!" << std::endl;
			break;
		}
	} while (1);

	CTime t_start = CTime::GetCurrentTime();
	CTime t_end = CTime::GetCurrentTime();
	CRect rect;
	GetWindowRect(hwnd, &rect);
	while (1)
	{
		Sleep(100);
		// ActiveWindow(hwnd);
		// SetActiveWindow(hwnd);
		// SetWindowPos(hwnd, HWND_TOP, rect.top, rect.bottom, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
		t_end = CTime::GetCurrentTime();
		CTimeSpan spanTime = t_end - t_start;
		if (spanTime.GetTotalSeconds() >= 5)
		{
			CloseWindow(hwnd);
			break;
		}
	}
	std::cout << "Bye!" << std::endl;

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

