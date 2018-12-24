// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
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

// TODO: 在此处引用程序需要的其他头文件
