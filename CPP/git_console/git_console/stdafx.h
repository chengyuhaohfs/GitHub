// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <afxwin.h>
#include <map>
#include <regex>
#include <vector>
#include <algorithm>


/************************************************************************/
/* macro definition */
#define H_PASS 0
#define H_FAIL 1
#define H_NONE 2

#define HWORD(x) ((x & 0xffff0000) >> 16)
#define LWORD(x) (x & 0x0000ffff)
/************************************************************************/

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
