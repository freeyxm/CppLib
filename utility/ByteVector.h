#pragma once
#include <vector>
#include <string>
#include <limits>
#include "BitConverter.h"

typedef unsigned char byte;

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

	bool replace(size_t index, char value)
	{
		if (index + 1 > m_bytes.size()) return false;
		auto it = m_bytes.begin() + index;
		*it = value;
		return true;
	}
	bool replace(size_t index, bool value)
	{
		if (index + 1 > m_bytes.size()) return false;
		auto it = m_bytes.begin() + index;
		*it = value;
		return true;
	}
	bool replace(size_t index, int16_t value)
	{
		const auto& bytes = BitConverter::GetBytes(value);
		return replace(index, bytes);
	}
	bool replace(size_t index, int32_t value)
	{
		const auto& bytes = BitConverter::GetBytes(value);
		return replace(index, bytes);
	}
	bool replace(size_t index, int64_t value)
	{
		const auto& bytes = BitConverter::GetBytes(value);
		return replace(index, bytes);
	}
	bool replace(size_t index, uint16_t value)
	{
		const auto& bytes = BitConverter::GetBytes(value);
		return replace(index, bytes);
	}
	bool replace(size_t index, uint32_t value)
	{
		const auto& bytes = BitConverter::GetBytes(value);
		return replace(index, bytes);
	}
	bool replace(size_t index, uint64_t value)
	{
		const auto& bytes = BitConverter::GetBytes(value);
		return replace(index, bytes);
	}
	bool replace(size_t index, float value)
	{
		const auto& bytes = BitConverter::GetBytes(value);
		return replace(index, bytes);
	}
	bool replace(size_t index, double value)
	{
		const auto& bytes = BitConverter::GetBytes(value);
		return replace(index, bytes);
	}
	bool replace(size_t index, const std::string& str);
	bool replace(size_t index, const char* str, const size_t size);

	inline size_t size() const { return m_bytes.size(); }

	inline std::vector<byte>& Bytes() { return m_bytes; }
	inline const std::vector<byte>& Bytes() const { return m_bytes; }

	operator std::vector<byte>& () { return m_bytes; }
	operator const std::vector<byte>& () const { return m_bytes; }

private:
	bool replace(size_t index, const std::vector<byte>& bytes);

private:
	std::vector<byte> m_bytes;
};

