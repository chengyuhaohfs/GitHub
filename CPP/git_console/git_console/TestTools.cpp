#include "StdAfx.h"
#include "TestTools.h"

using std::cout;
using std::endl;

CTestTools::CTestTools(void)
{
}


CTestTools::~CTestTools(void)
{
}


CString CTestTools::GetCurDir()
{
	CString csModuleFile = "";
	DWORD dwRes = GetModuleFileName(AfxGetStaticModuleState()->m_hCurrentInstanceHandle, csModuleFile.GetBuffer(MAX_PATH), MAX_PATH);
	csModuleFile.ReleaseBuffer();

	if (dwRes == 0)
	{
		cout << "Get current Module file failed!\n";

		return csModuleFile;
	}
	
	return csModuleFile.Mid(0, csModuleFile.ReverseFind('\\') + 1);
}

void CTestTools::GetFileContent(CString csFile, CString &csContent)
{
	{
		WIN32_FIND_DATA wData;
		ZeroMemory(&wData, sizeof(wData));
		HANDLE hFile = FindFirstFile(csFile, &wData);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			std::cout << "Can't find file " << csFile << std::endl;
			CloseHandle(hFile);
			return;
		}
	}

	CFile cfile;
	if (cfile.Open(csFile, CFile::modeRead))
	{
		UINT fileSize = (UINT)cfile.GetLength();
		char *chBuffer = new char[fileSize + 1];
		ZeroMemory(chBuffer, fileSize + 1);
		UINT uiLen = cfile.Read(chBuffer, fileSize);
		if (uiLen == 0)
		{
			std::cout << "Read nothing from file " << csFile << std::endl;

			delete[] chBuffer;
			cfile.Close();
			return;
		}

		csContent.Format("%s", chBuffer);
		delete[] chBuffer;
		cfile.Close();
	}
	else
	{
		std::cout << "Can't open file " << csFile << std::endl;
		return;
	}
}

BOOL CTestTools::PickStringWithRegex(CString cstrRev, CStringArray &ca_finds, std::string strRegex)
{
	std::string strRev = cstrRev.GetBuffer(cstrRev.GetLength());
	cstrRev.ReleaseBuffer();
	std::regex partten(strRegex);
	std::smatch match_value;
	bool bMatched = std::regex_search(strRev, match_value, partten);
	if (bMatched)
	{
		std::string strFind = match_value[0];
		for (auto iter = match_value.begin(); iter != match_value.end(); iter++)
		{
			ca_finds.Add(iter->str().c_str());
		}
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}