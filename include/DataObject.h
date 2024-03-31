#pragma once
#include "SaveDefines.h"
#include <vector>
#include <stdint.h>
#include <iostream>
#include "Types.h"

class DataObject
{
protected:
	unsigned int startByte;
	unsigned int size;
	Type type;

	unsigned int numRows, numColumns;

public:
	DataObject(unsigned int startByte, unsigned int lengthInBytes, Type type);

	unsigned int getLengthInBytes() const;
	Type getType() const;
	unsigned int getStartByte() const;

	std::vector<uint8_t> getRawBytes(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES]) const;
	void setRawBytes(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES], uint64_t value) const;
	void setRawBytes(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES], std::vector<uint8_t> value) const;

	virtual const DataObject* at(unsigned int row, unsigned int column) const
	{
		if (row < this->numRows && column < this->numColumns) return this;
		else return NULL;
	}

	void print();
};
