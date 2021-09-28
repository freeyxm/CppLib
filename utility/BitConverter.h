#pragma once
#include <vector>
#include <string>
#include <limits>

typedef char byte;

class BitConverter
{
public:
	inline static std::vector<byte> GetBytes(int16_t value)
	{
		byte* bytes = (byte*)&value;
		return std::vector<byte>(bytes, bytes + 2);
	}

	inline static std::vector<byte> GetBytes(int32_t value)
	{
		byte* bytes = (byte*)&value;
		return std::vector<byte>(bytes, bytes + 4);
	}

	inline static std::vector<byte> GetBytes(int64_t value)
	{
		byte* bytes = (byte*)&value;
		return std::vector<byte>(bytes, bytes + 8);
	}

	inline static std::vector<byte> GetBytes(uint16_t value)
	{
		byte* bytes = (byte*)&value;
		return std::vector<byte>(bytes, bytes + 2);
	}

	inline static std::vector<byte> GetBytes(uint32_t value)
	{
		byte* bytes = (byte*)&value;
		return std::vector<byte>(bytes, bytes + 4);
	}

	inline static std::vector<byte> GetBytes(uint64_t value)
	{
		byte* bytes = (byte*)&value;
		return std::vector<byte>(bytes, bytes + 8);
	}

	inline static std::vector<byte> GetBytes(float value)
	{
		byte* bytes = (byte*)&value;
		return std::vector<byte>(bytes, bytes + 4);
	}

	inline static std::vector<byte> GetBytes(double value)
	{
		byte* bytes = (byte*)&value;
		return std::vector<byte>(bytes, bytes + 8);
	}

	inline static void GetBytes(int16_t value, std::vector<byte>& vector)
	{
		byte* bytes = (byte*)&value;
		vector.insert(vector.end(), bytes, bytes + 2);
	}

	inline static void GetBytes(int32_t value, std::vector<byte>& vector)
	{
		byte* bytes = (byte*)&value;
		vector.insert(vector.end(), bytes, bytes + 4);
	}

	inline static void GetBytes(int64_t value, std::vector<byte>& vector)
	{
		byte* bytes = (byte*)&value;
		vector.insert(vector.end(), bytes, bytes + 8);
	}

	inline static void GetBytes(uint16_t value, std::vector<byte>& vector)
	{
		byte* bytes = (byte*)&value;
		vector.insert(vector.end(), bytes, bytes + 2);
	}

	inline static void GetBytes(uint32_t value, std::vector<byte>& vector)
	{
		byte* bytes = (byte*)&value;
		vector.insert(vector.end(), bytes, bytes + 4);
	}

	inline static void GetBytes(uint64_t value, std::vector<byte>& vector)
	{
		byte* bytes = (byte*)&value;
		vector.insert(vector.end(), bytes, bytes + 8);
	}

	inline static void GetBytes(float value, std::vector<byte>& vector)
	{
		byte* bytes = (byte*)&value;
		vector.insert(vector.end(), bytes, bytes + 4);
	}

	inline static void GetBytes(double value, std::vector<byte>& vector)
	{
		byte* bytes = (byte*)&value;
		vector.insert(vector.end(), bytes, bytes + 8);
	}

	inline static int16_t ToInt16(const std::vector<byte>& bytes, int startIndex)
	{
		int16_t value = *(int16_t*)&bytes[startIndex];
		return value;
	}

	inline static int32_t ToInt32(const std::vector<byte>& bytes, int startIndex)
	{
		int32_t value = *(int32_t*)&bytes[startIndex];
		return value;
	}

	inline static int64_t ToInt64(const std::vector<byte>& bytes, int startIndex)
	{
		int64_t value = *(int64_t*)&bytes[startIndex];
		return value;
	}

	inline static uint16_t ToUInt16(const std::vector<byte>& bytes, int startIndex)
	{
		uint16_t value = *(uint16_t*)&bytes[startIndex];
		return value;
	}

	inline static uint32_t ToUInt32(const std::vector<byte>& bytes, int startIndex)
	{
		uint32_t value = *(uint32_t*)&bytes[startIndex];
		return value;
	}

	inline static uint64_t ToUInt64(const std::vector<byte>& bytes, int startIndex)
	{
		uint64_t value = *(uint64_t*)&bytes[startIndex];
		return value;
	}

	inline static float ToFloat(const std::vector<byte>& bytes, int startIndex)
	{
		float value = *(float*)&bytes[startIndex];
		return value;
	}

	inline static double ToDouble(const std::vector<byte>& bytes, int startIndex)
	{
		double value = *(double*)&bytes[startIndex];
		return value;
	}

	inline static int16_t ToInt16(const byte* bytes, int startIndex)
	{
		int16_t value = *(int16_t*)(bytes + startIndex);
		return value;
	}

	inline static int32_t ToInt32(const byte* bytes, int startIndex)
	{
		int32_t value = *(int32_t*)(bytes + startIndex);
		return value;
	}

	inline static int64_t ToInt64(const byte* bytes, int startIndex)
	{
		int64_t value = *(int64_t*)(bytes + startIndex);
		return value;
	}

	inline static uint16_t ToUInt16(const byte* bytes, int startIndex)
	{
		uint16_t value = *(uint16_t*)(bytes + startIndex);
		return value;
	}

	inline static uint32_t ToUInt32(const byte* bytes, int startIndex)
	{
		uint32_t value = *(uint32_t*)(bytes + startIndex);
		return value;
	}

	inline static uint64_t ToUInt64(const byte* bytes, int startIndex)
	{
		uint64_t value = *(uint64_t*)(bytes + startIndex);
		return value;
	}

	inline static float ToFloat(const byte* bytes, int startIndex)
	{
		float value = *(float*)(bytes + startIndex);
		return value;
	}

	inline static double ToDouble(const byte* bytes, int startIndex)
	{
		double value = *(double*)(bytes + startIndex);
		return value;
	}
};
