#pragma once
#include "stdafx.h"

/************************************************************************/
/* 宏定义 */
#define MY_VECTOR(data_type, data_array, mvector_name) CMVector<data_type> mvector_name(data_array, sizeof(data_array) / sizeof(data_type))
/************************************************************************/
template<class T>
class CMVector
{
private:
	std::vector<T> m_vector;

public:
	CMVector(std::vector<T> _vector) : m_vector(_vector) {}
	CMVector(T *pArray, size_t sz)
	{
		for (size_t index = 0; index < sz; index++)
		{
			m_vector.push_back(pArray[index]);
		}
	}
	~CMVector() {}

	BOOL Contains(T _val)
	{
		std::vector<T>::iterator iter_begin;
		std::vector<T>::iterator iter_end;
		if (iter_end == std::find(iter_begin, iter_end, _val))
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}

	const std::vector<T> &GetVector()
	{
		return m_vector;
	}
};

template<class T>
class CAutopara
{
public:
	T *m_pVal;
	size_t m_size;
	size_t m_usedSize;
	CAutopara(size_t _size) : m_size(_size), m_innerSize(_size + 1)
	{
		m_usedSize = 0;
		// 在申请空间时应该多申请一个单元，以免空间不足
		m_pVal = new T[m_innerSize];
		InitParam();
	}

	~CAutopara()
	{
		delete[] m_pVal;
	}

	void Copy(T *_pVal, size_t _size)
	{
		size_t real_size = _size / sizeof(T);
		for (size_t index = 0; index < real_size; index++)
		{
			if (index < m_size)
			{
				m_pVal[index] = _pVal[index];
				m_usedSize++;
				continue;
			}
			
			break;
		}
	}

private:
	size_t m_innerSize;
	void InitParam()
	{
		for (size_t index = 0; index < m_innerSize; index++)
		{
			m_pVal[index] = 0;
		}
	}

	void operator=(CAutopara &_para)
	{
		// not accepted using
	}
};


class CTestTools
{
public:
	CTestTools(void);
	~CTestTools(void);
	CString GetCurDir();
	void GetFileContent(CString csFile, CString &csContent);
	BOOL PickStringWithRegex(CString cstrRev, CStringArray &ca_finds, std::string strRegex);
};