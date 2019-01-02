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

void CTestTools::SplitCommentToLine(CString cstrRev, CStringArray &ca_lines)
{
	int iStart = 0;
	for (int index = 0; index < cstrRev.GetLength(); index++)
	{
		if (cstrRev.GetAt(index) == '\n' || cstrRev.GetAt(index) == '\r')
		{
			while (cstrRev.GetAt(index) == '\n' || cstrRev.GetAt(index) == '\r')
			{
				index++;
			}
			CString cstr = cstrRev.Mid(iStart, index - iStart);
			iStart = index;
			ca_lines.Add(cstr);
		}
	}
}


void CTestTools::GroupByRegex(CStringArray &ca_lines, std::vector<std::string> parttens)
{
	std::string strCurGroup = "";
	std::string strCurRegex = "";
	std::map<std::string, std::vector<std::string>> map_finds;
	for (int index = 0; index < ca_lines.GetSize(); index++)
	{
		CString cstr = ca_lines.GetAt(index);
		if (0 == cstr.Trim().GetLength())
		{
			continue;
		}
		std::string str = cstr.GetBuffer(cstr.GetLength());
		cstr.ReleaseBuffer();
// 		for (auto iter = parttens.begin(); iter != parttens.end(); iter++)
// 		{
// 			std::regex partten(*iter);
// 			std::match_results<std::string::const_iterator> match_values;
// 			if (std::regex_search(str, match_values, partten))
// 			{
// 				strCurRegex = *iter;
// 				// 如果匹配到则进入循环，直到遇到下一个匹配
// 
// 			}
// 		}

		// 当匹配到第一个正则时写入，到遇到下一个时停止
		{
			std::regex partten(parttens[0]);
			std::match_results<std::string::const_iterator> match_values;
			if ( std::regex_search(str, match_values, partten) )
			{
				strCurGroup = str;
				continue;
			}

			if (strCurGroup.length() != 0 && 0 != str.length())
			{
				map_finds[strCurGroup].push_back(str);
			}
		}

// 		if (0 != str.length() && 0 != strCurRegex.length())
// 		{
// 			map_finds[strCurRegex].push_back(str);
// 		}
	}

	for (auto iter = map_finds.begin(); iter != map_finds.end(); iter++)
	{
		cout << iter->first << ":\n";
		for (auto subiter = iter->second.begin(); subiter != iter->second.end(); subiter++)
		{
			cout << *subiter << endl;
		}
	}
}