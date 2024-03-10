#pragma once
#include "SaveDefines.h"
#include <vector>
#include <stdint.h>

class DataObject
{
	unsigned int startByte;
	unsigned int size;

public:
	DataObject(unsigned int startByte, unsigned int lengthInBytes);
	std::vector<uint8_t> getRawBytes(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES]);
	void setRawBytes(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES], uint64_t value);
	void setRawBytes(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES], std::vector<uint8_t> value);
};
