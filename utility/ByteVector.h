#pragma once
#include <vector>
#include <string>
#include <limits>
#include "BitConverter.h"

typedef char byte;

class ByteVector
{
public:
	inline void push_back(char value)
	{
		m_bytes.push_back(value);
	}

	inline void push_back(bool value)
	{
		m_bytes.push_back(value);
	}

	inline void push_back(int16_t value)
	{
		BitConverter::GetBytes(value, m_bytes);
	}

	inline void push_back(int32_t value)
	{
		BitConverter::GetBytes(value, m_bytes);
	}

	inline void push_back(int64_t value)
	{
		BitConverter::GetBytes(value, m_bytes);
	}

	inline void push_back(uint16_t value)
	{
		BitConverter::GetBytes(value, m_bytes);
	}

	inline void push_back(uint32_t value)
	{
		BitConverter::GetBytes(value, m_bytes);
	}

	inline void push_back(uint64_t value)
	{
		BitConverter::GetBytes(value, m_bytes);
	}

	inline void push_back(float value)
	{
		BitConverter::GetBytes(value, m_bytes);
	}

	inline void push_back(double value)
	{
		BitConverter::GetBytes(value, m_bytes);
	}

	inline void push_back(const std::string& str)
	{
		m_bytes.insert(m_bytes.end(), str.cbegin(), str.cend());
	}

	inline void push_back(const char* str, const size_t size)
	{
		m_bytes.insert(m_bytes.end(), str, str + size);
	}

	operator std::vector<byte>& () { return m_bytes; }
	operator const std::vector<byte>& () const { return m_bytes; }

private:
	std::vector<byte> m_bytes;
};

