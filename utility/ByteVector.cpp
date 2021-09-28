#include "stdafx.h"
#include "ByteVector.h"

bool ByteVector::replace(size_t index, const std::vector<byte>& bytes)
{
	if (index + bytes.size() > m_bytes.size())
	{
		return false;
	}
	auto it = m_bytes.begin() + index;
	for (size_t i = 0; i < bytes.size(); ++i)
	{
		*it++ = bytes[i];
	}
	return true;
}

bool ByteVector::replace(size_t index, const std::string& str)
{
	if (index + str.size() > m_bytes.size())
	{
		return false;
	}
	auto it = m_bytes.begin() + index;
	for (size_t i = 0; i < str.size(); ++i)
	{
		*it++ = str[i];
	}
	return true;
}

bool ByteVector::replace(size_t index, const char* str, const size_t size)
{
	if (index + size > m_bytes.size())
	{
		return false;
	}
	auto it = m_bytes.begin() + index;
	for (size_t i = 0; i < size; ++i)
	{
		*it++ = str[i];
	}
	return true;
}
