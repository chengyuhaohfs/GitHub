#pragma once
#include "stdafx.h"

/************************************************************************/
/* ∫Í∂®“Â */
#define MY_VECTOR(data_type, data_array, mvector_name) CMVector<data_type> mvector_name(data_array, sizeof(data_array) / sizeof(data_type))
/************************************************************************/

class CTestTools
{
public:
	CTestTools(void);
	~CTestTools(void);
	CString GetCurDir();
};

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

