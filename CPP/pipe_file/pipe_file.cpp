// pipe_file.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "iostream"
#include "assert.h"

#define NORMAL_SIZE     512
#define MAX_WORD_SIZE   2048
#define SHORT_WORD_SIZE 1024

#define uint unsigned int

using namespace std;

void mStrCpy(char* dst, char* rsc, uint size);
void mStrCat(char* dst, char* rsc, uint size);
void mPickLine(char* rsc, char* strLine, uint size);

int main()
{
	HANDLE hInputRead, hInputWrite;

	SECURITY_ATTRIBUTES pSe;

	pSe.nLength = sizeof(SECURITY_ATTRIBUTES);
	pSe.bInheritHandle       = TRUE;
	pSe.lpSecurityDescriptor = NULL;

/*
	hWriteInput  = GetStdHandle(STD_INPUT_HANDLE);
	hWriteOutput = GetStdHandle(STD_OUTPUT_HANDLE);*/

	if (!CreatePipe(&hInputRead, &hInputWrite, &pSe, MAX_WORD_SIZE))
	{
		MessageBox(NULL, L"创建管道失败！", L"Tips", MB_OK);
		return 0;
	}

	STARTUPINFO         startUpInfo;
	PROCESS_INFORMATION processInformation;

	GetStartupInfo(&startUpInfo);
	startUpInfo.cb          = sizeof(STARTUPINFO);
	startUpInfo.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	startUpInfo.wShowWindow = SW_HIDE;

	startUpInfo.hStdError = hInputWrite;
	startUpInfo.hStdOutput = hInputWrite;

	wchar_t wCmd[] = L"ipconfig /all";
/*	wchar_t wCmd[] = L"py thread.py";*/
/*	wchar_t wCmd[] = L"ping www.baidu.com -t";*/
/*	wchar_t wApp[] = L"thread.exe";*/
	wchar_t wApp[] = L"D:\\myFiles\\Program\\vs2010\\myTest\\usePython\\Debug\\dist\\testpy.exe";

/*	wchar_t* wpCmd = wCmd;*/
	wchar_t* wpCmd = NULL;
	wchar_t* wpApp = wApp;
/*	wchar_t* wpApp = NULL;*/

	if (!CreateProcess(wpApp, wpCmd, NULL, NULL, TRUE, 0, NULL, NULL, &startUpInfo, &processInformation))
	{
		MessageBox(NULL, L"创建进程失败！", L"Tips", MB_OK);
		return 0;
	}

	DWORD bytesRead = 0, totalBytesAvail = 0, bytesLeftThisMessage = 0;
	
	DWORD numberOfBytesRead = 0;
	DWORD dProcessStatus    = STILL_ACTIVE;

	WaitForSingleObject(processInformation.hProcess, 1000);

	

	// 管道内容读取
	char chTail[NORMAL_SIZE]   = "";
	char chBuffer[NORMAL_SIZE] = "";
	char chLongBuffer[MAX_WORD_SIZE + 1]    = "";
	char chShortBuffer[SHORT_WORD_SIZE + 1] = "";

	memset(chLongBuffer, '\0', MAX_WORD_SIZE);

	do 
	{
		memset(chShortBuffer, '\0', SHORT_WORD_SIZE);
		// 先从管道中预读取一个短的字符串
		if (!PeekNamedPipe(hInputRead, chShortBuffer, SHORT_WORD_SIZE, &bytesRead, &totalBytesAvail, &bytesLeftThisMessage))
		{
			CloseHandle(hInputRead);
			CloseHandle(hInputWrite);
			CloseHandle(processInformation.hProcess);
			CloseHandle(processInformation.hThread);

			MessageBox(NULL, L"预读管道失败！", L"Tips", MB_OK);
			return 0;
		}
		GetExitCodeProcess(processInformation.hProcess, &dProcessStatus);

		if (bytesRead == 0)
		{
			if (dProcessStatus != STILL_ACTIVE)
			{
				break;
			}
			continue;
		}

		memset(chShortBuffer, '\0', SHORT_WORD_SIZE);
		// 从管道中读取一个短的字符串
		if (!ReadFile(hInputRead, chShortBuffer, SHORT_WORD_SIZE, &numberOfBytesRead, NULL))
		{
			CloseHandle(hInputRead);
			CloseHandle(hInputWrite);
			CloseHandle(processInformation.hProcess);
			CloseHandle(processInformation.hThread);

			MessageBox(NULL, L"读管道失败！", L"Tips", MB_OK);
			return 0;
		}

		size_t iShortLen = strlen(chShortBuffer);
		mStrCat(chLongBuffer, chShortBuffer, MAX_WORD_SIZE);

		memset(chBuffer, '\0', NORMAL_SIZE);
		while (strstr(chLongBuffer, "\n"))
		{
			mPickLine(chLongBuffer, chBuffer, MAX_WORD_SIZE);

			cout << chBuffer;
			memset(chBuffer, '\0', NORMAL_SIZE);
		}

	} while (1);

	DWORD exitCode = 0;
	GetExitCodeProcess(processInformation.hProcess, &exitCode);

	cout << exitCode << endl;

	CloseHandle(hInputRead);
	CloseHandle(hInputWrite);
	CloseHandle(processInformation.hProcess);
	CloseHandle(processInformation.hThread);

    return 0;
}

void mStrCpy(char* dst, char* rsc, uint size)
{
	assert(strlen(rsc) < size);

	int  i  = 0;
	char ch = '\0';

	char* pfrom = rsc;
	char* pto   = dst;

	memset(dst, '\0', size);
	while (ch = pfrom[i])
	{
		pto[i] = ch;
		i++;
	}
}

void mStrCat(char* dst, char* rsc, uint size)
{
	size_t iDstLen = strlen(dst);
	size_t iRscLen = strlen(rsc);
	assert((iDstLen + iRscLen) < size);

	int  i = 0;
	char ch = '\0';

	char* pfrom = rsc;
	char* pto = dst;

	while (ch = pfrom[i])
	{
		pto[iDstLen + i] = ch;
		i++;
	}
}

void mPickLine(char* rsc, char* strLine, uint size)
{
	char ch = '\0';
	int i   = 0, j = 0;
	char* chBuffer = new char[size];
	memset(chBuffer, '\0', size);

	BOOL flag = TRUE;
	while (ch = rsc[i])
	{
		if (flag)
		{
			if (ch == '\n')
			{
				while ((ch == '\n') || (ch == '\r'))
				{
					strLine[i] = ch;
					i++;
					ch = rsc[i];
				}
				flag = FALSE;
			}
			strLine[i] = ch;
			i++;
		}
		else
		{
			chBuffer[j] = ch;
			j++;
			i++;
		}
	}

	memset(rsc, '\0', size);
	j = 0;
	while (ch = chBuffer[j])
	{
		rsc[j] = ch;
		j++;
	}

	delete[] chBuffer;
}