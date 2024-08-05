#pragma once
#include <vector>
#include <string>
#include <stdint.h>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#endif

enum Type
{
	UINT_T,
	INT_T,
	BOOL_T,
	FLOAT_T,
	STRING_T,
	TPL_T,
	ARRAY_T
};

class Types
{
private:
public:

	template <typename T>
	static T toValue(std::vector<uint8_t> rawBytes)
	{
		T result = 0;

		for (uint8_t byte : rawBytes)
		{
			result <<= 8;
			result |= byte;
		}

		return result;
	}

	// Returns the big-endian representation of x
	template <typename T>
	static std::vector<uint8_t> toRaw(T x)
	{
		std::vector<uint8_t> v;
		do // When x==0, loop is run once to put 0 into v
		{
			v.insert(v.begin(), x & (T) 0xFF);
			x >>= (T)8;
		} while (x != 0);
		return v;
	}

	static std::vector<uint8_t> toRaw(float x);
	static std::vector<uint8_t> toRaw(bool x);
	static std::vector<uint8_t> toRaw(int x);
	static std::vector<uint8_t> toRaw(std::string x);

	static std::string toString(Type t);
};

template <>
float Types::toValue(std::vector<uint8_t> rawBytes);

template <>
std::string Types::toValue(std::vector<uint8_t> rawBytes);

template <>
bool Types::toValue(std::vector<uint8_t> rawBytes);
