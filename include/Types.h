#pragma once
#include <vector>
#include <string>

enum Type
{
	UINT8_T,
	UINT16_T,
	UINT32_T,
	INT8_T,
	INT16_T,
	INT32_T,
	BOOL,
	FLOAT,
	STRING,
	TPL,
	ARRAY
};

static uint32_t endianness = 0x12345678;
enum endian { BIG, LITTLE };
#define ENDIANNESS (*(const char*)&endianness == 0x78 ? LITTLE : BIG)

class Types
{
public:
	static float toFloat(std::vector<uint8_t> rawBytes);
	static unsigned int toUInt(std::vector<uint8_t> rawBytes);
	static int toSInt(std::vector<uint8_t> rawBytes);
	static std::string toString(std::vector<uint8_t> rawBytes);
	static bool toBool(std::vector<uint8_t> rawBytes);

	static std::vector<uint8_t> toRaw(float x);
	static std::vector<uint8_t> toRaw(unsigned int x); // this function will also handle bool
	static std::vector<uint8_t> toRaw(int x);
	static std::vector<uint8_t> toRaw(std::string x);

	static std::string toString(Type t);
};
