#pragma once
#include "SaveDefines.h"
#include <vector>
#include <stdint.h>

enum Type
{
	UINT8_T,
	UINT16_T,
	INT32_T,
	UINT32_T,
	BOOL,
	FLOAT, 
	STRING,
	TPL,
	ARRAY
};

class DataObject
{
	unsigned int startByte;
	unsigned int size;
	Type type;

public:
	DataObject(unsigned int startByte, unsigned int lengthInBytes, Type type);

	std::vector<uint8_t> getRawBytes(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES]);
	void setRawBytes(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES], uint64_t value);
	void setRawBytes(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES], std::vector<uint8_t> value);
};
