#pragma once
#include "SaveDefines.h"
#include <vector>
#include <stdint.h>
#include "Types.h"

class DataObject
{
protected:
	unsigned int startByte;
	unsigned int endByte;
	unsigned int startBit;
	unsigned int endBit;
	unsigned int bitLength;
	Type type;

	unsigned int numRows, numColumns;

    DataObject(unsigned int startByte, unsigned int lengthInBytes, Type type, unsigned int numRows, unsigned int numColumns);

    bool setRawBytes(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES], std::vector<uint8_t> value) const;

public:
	DataObject(unsigned int startByte, unsigned int startBit, unsigned int lengthInBits, Type type);
	DataObject(unsigned int startByte, unsigned int lengthInBytes, Type type);

	unsigned int getLengthInBits() const;
	Type getType() const;
	unsigned int getStartByte() const;

    std::vector<uint8_t> getRawBytes(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES]) const;

    // TODO: range checks in setValue functions
    template <typename T>
    void setValue(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES], T value) const
    {
        std::vector<uint8_t> rawBytes = Types::toRaw(value);
        if (this->type == STRING_T) for (int i = rawBytes.size(); i < (this->bitLength / 8); i++) rawBytes.push_back(0);
        this->setRawBytes(saveFile, rawBytes);
    }

    template<>
    void setValue(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES], std::string value) const
    {
        for (int i = value.size(); i < (this->bitLength / 8); i++) value += (char)0;
        this->setRawBytes(saveFile, Types::toRaw(value));
    }

    void setValue(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES], std::string value) const;

	virtual const DataObject* at(unsigned int row, unsigned int column) const
	{
		if (row < this->numRows && column < this->numColumns) return this;
		else return NULL;
	}

	virtual const int getStaticValue(unsigned int column) const { return 0; }

    unsigned const int getNumRows() const { return this->numRows; }
    unsigned const int getNumColumns() const { return this->numColumns; }

	void print();
};
