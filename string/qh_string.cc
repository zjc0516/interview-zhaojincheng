#include "qh_string.h"

#include <string.h>
#include <assert.h>

namespace qh
{
	// TODO 将在这里写实现代码

	string::string()
		: data_(NULL), len_(0)
	{
	}

	string::string( const char* s )
	{
		if (s == NULL)
		{
			return;
		}
		else
		{
			len_ = strlen(s);
			data_ = new char[len_ + 1];
			strcpy(data_, s);
		}		
	}

	string::string( const char* s, size_t len )
	{
		len_ = len;
		data_ = new char[len_ +1];
		strncpy(data_, s, len_+1);
		if (len_ < strlen(s))
		{
			data_[len] = 0;
		}
	}


	string::string( const string& rhs )
	{
		len_ = rhs.size();
		data_ = new char[len_+1];
		strcpy(data_, rhs.data_);
	}

	string& string::operator=( const string& rhs )
	{
		if (this != &rhs)
		{
			string sTemp(rhs);
			char* pTemp = sTemp.data_;
			sTemp.data_ = data_;
			data_ = pTemp;
		}		
		return *this;
	}

	string::~string()
	{
		delete[] data_;
	}

	size_t string::size() const
	{
		return len_;
	}

	const char* string::data() const
	{
		return data_;
	}

	const char* string::c_str() const
	{
		return data_;
	}

	char* string::operator[]( size_t index )
	{
		assert(index>=0 && index <= len_);
		return data_+index;
	}
}
