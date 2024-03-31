#include "Types.h"
#include <stdexcept>

/* Assume all vectors are big endian
*  Raw types (int, float, etc) depend on the underlying architecture
*/

union floatUnion
{
	float f;
	uint8_t fBytes[sizeof(float)];
};

float Types::toFloat(std::vector<uint8_t> rawBytes)
{
	if (rawBytes.size() != 4) throw std::runtime_error("Expected 4 byte float");

	floatUnion f;
	if (ENDIANNESS == LITTLE) for (int i = 0; i < 4; i++) f.fBytes[i] = rawBytes.at(3 - i);
	else for (int i = 0; i < 4; i++) f.fBytes[i] = rawBytes.at(i);

	return f.f;
}

unsigned int Types::toUInt(std::vector<uint8_t> rawBytes)
{
	if (rawBytes.size() > 8) throw std::runtime_error("Maximum 8 byte integer allowed");

	unsigned int result = 0;
	for (int i = 0; i < rawBytes.size(); i++)
	{
		result <<= 8;
		result |= rawBytes.at(i);
	}

	return result;
}

int Types::toSInt(std::vector<uint8_t> rawBytes)
{
	if (rawBytes.size() > 8) throw std::runtime_error("Maximum 8 byte integer allowed");

	int result = 0;
	for (int i = 0; i < rawBytes.size(); i++)
	{
		result <<= 8;
		result |= rawBytes.at(i);
	}

	return result;
}

std::string Types::toString(std::vector<uint8_t> rawBytes)
{
	std::string result;
	for (int i = 0; i < rawBytes.size(); i++) result += rawBytes.at(i);
	return result;
}

bool Types::toBool(std::vector<uint8_t> rawBytes)
{
	if (rawBytes.size() == 0) return false;
	return rawBytes.at(rawBytes.size() - 1);
}

std::vector<uint8_t> Types::toRaw(float x)
{
	floatUnion f;
	f.f = x;
	std::vector<uint8_t> v;

	if (ENDIANNESS == LITTLE) for (int i = 3; i >= 0; i--) v.push_back(f.fBytes[i]);
	else for (int i = 0; i < 4; i++) v.push_back(f.fBytes[i]);

	return v;
}

std::vector<uint8_t> Types::toRaw(unsigned int x)
{
	std::vector<uint8_t> v;
	do // When x==0, loop is run once to put 0 into v
	{
		v.insert(v.begin(), x & 0xFF);
		x >>= 8;
	} while (x != 0);
	return v;
}

std::vector<uint8_t> Types::toRaw(int x)
{
	return toRaw((unsigned int) x);
}

std::vector<uint8_t> Types::toRaw(std::string x)
{
	std::vector<uint8_t> v;
	for (int i = 0; i < x.size(); i++) v.push_back(x.at(i));
	return v;
}
