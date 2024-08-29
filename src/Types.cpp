#include "Types.h"

template <>
float Types::toValue<float>(std::vector<uint8_t> rawBytes)
{
	float f;

	int floatInIntRep = 0;
	for (uint8_t byte : rawBytes)
	{
		floatInIntRep <<= 8;
		floatInIntRep |= byte;
	}
	memcpy(&f, &floatInIntRep, 4);

	return f;
}

template <>
std::string Types::toValue<std::string>(std::vector<uint8_t> rawBytes)
{
	std::string string = "";
	for (uint8_t rawByte : rawBytes)
	{
		string += rawByte;
	}
	return string;
}

template <>
bool Types::toValue<bool>(std::vector<uint8_t> rawBytes)
{
	int rawBool = toValue<int>(rawBytes);
	return rawBool == 0 ? false : true;
}

std::vector<uint8_t> Types::toRaw(float x)
{
	std::vector<uint8_t> v;

	uint8_t floatBytes[sizeof(float)];
	memcpy(floatBytes, &x, sizeof(x));

	int floatInIntRep = 0;
	for (uint8_t byte : floatBytes)
	{
		floatInIntRep <<= 8;
		floatInIntRep |= byte;
	}

	uint32_t bigEndianFloat = htonl(floatInIntRep);

	for (int i = 0; bigEndianFloat != 0 && i < 4; i++)
	{
		v.insert(v.begin(), bigEndianFloat & 0xFF);
		bigEndianFloat >>= 8;
	}

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

std::vector<uint8_t> Types::toRaw(bool x) { return x ? toRaw(1) : toRaw(0);}

std::string Types::toString(Type t)
{
	std::string result;
	switch (t)
	{
	case UINT_T:
		result = "UINT";
		break;
	case INT_T:
		result = "INT";
		break;
	case BOOL_T:
		result = "BOOL";
		break;
	case FLOAT_T:
		result = "FLOAT";
		break;
	case STRING_T:
		result = "STRING";
		break;
	case TPL_T:
		result = "TPL";
		break;
	case ARRAY_T:
		result = "ARRAY";
		break;
	default:
		result = "UNDEFINED";
		break;
	}
	return result;
}
