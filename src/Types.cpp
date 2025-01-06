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
    memcpy(&f, &floatInIntRep, sizeof(float));

	return f;
}

template <>
std::string Types::toValue<std::string>(std::vector<uint8_t> rawBytes)
{
	std::string string = "";
	for (uint8_t rawByte : rawBytes)
    {
        if (!rawByte) break;
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

template<>
int Types::toValue(std::vector<uint8_t> rawBytes)
{
    unsigned int result = 0;

    for (uint8_t byte : rawBytes)
    {
        result <<= 8;
        result |= byte;
    }

    if ((rawBytes.at(0) & 0x80) == 0x80) // negative
    {
        unsigned int mask = 0;
        for (int b = rawBytes.size(); b < sizeof(unsigned int); b++) mask |= 0xFF << (b*8);
        result |= mask;
    }

    return result;
}

std::vector<uint8_t> Types::toRaw(float x, unsigned int maxBits)
{
	std::vector<uint8_t> v;
    if (sizeof(float) <= (maxBits / 8))
    {
        uint8_t floatBytes[sizeof(float)];
        memcpy(floatBytes, &x, sizeof(x));

        int floatInIntRep = 0;
        for (uint8_t byte : floatBytes)
        {
            floatInIntRep <<= 8;
            floatInIntRep |= byte;
        }

        uint32_t bigEndianFloat = htonl(floatInIntRep);

        for (int i = 0; i < sizeof(float); i++)
        {
            v.insert(v.begin(), bigEndianFloat & 0xFF);
            bigEndianFloat >>= 8;
        }
    }

	return v;
}

std::vector<uint8_t> Types::toRaw(int x, unsigned int maxBits)
{
    unsigned int mask = maxBits < 32 ? ((1 << maxBits) - 1) : 0xFFFFFFFF;
    return toRaw(((unsigned int) x) & mask, maxBits);
}

std::vector<uint8_t> Types::toRaw(std::string x, unsigned int maxBits)
{
	std::vector<uint8_t> v;
    if (x.size() == 0) v.push_back(0);
    else if (x.size() <= (maxBits / 8)) for (int i = 0; i < x.size(); i++) v.push_back(x.at(i));
	return v;
}

std::vector<uint8_t> Types::toRaw(bool x, unsigned int maxBits) { return x ? toRaw(1, maxBits) : toRaw(0, maxBits); }

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
