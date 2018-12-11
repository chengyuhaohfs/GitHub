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