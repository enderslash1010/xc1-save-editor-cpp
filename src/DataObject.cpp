#include "DataObject.h"

DataObject::DataObject(unsigned int startByte, unsigned int lengthInBytes, Type type)
{
	this->startByte = startByte;
	this->size = lengthInBytes;
	this->type = type;

	this->numRows = 1;
	this->numColumns = 1;
}

std::vector<uint8_t> DataObject::getRawBytes(uint8_t (&saveFile)[SAVEFILE_LENGTH_BYTES]) const
{
	std::vector<uint8_t> result;
	for (int i = 0; i < this->size; i++)
	{
		result.push_back(saveFile[this->startByte + i]);
	}
	return result;
}

/*
*	Sets the saveFile bytes associated with this DataObject to the bytes in value
*	Can set up to 8 bytes, if need to set more use other function with array parameter
* 
*	In the case when bytes.size() > this.size(), the additional MSB in bytes are ignored (bytes = 0xABCD -> DataObject = 0xCD for this.size() = 1)
*	In the case when bytes.size() < this.size(), the additional MSB associated with the DataObject are cleared (bytes = 0xFF -> DataObject = 0x00FF for this.size() = 2)
* 
*	This has got to be my favorite function I've created, a wild one-liner
*/
void DataObject::setRawBytes(uint8_t (&saveFile)[SAVEFILE_LENGTH_BYTES], uint64_t value) const
{
	for (int saveFileIdx = this->startByte + this->size - 1; saveFileIdx >= this->startByte; saveFileIdx--, value >>= 8) saveFile[saveFileIdx] = value < 0 ? 0x0 : (value & 0xFF);
}

/*
*	Does the same as function above, but can set more than 8 bytes
*/
void DataObject::setRawBytes(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES], std::vector<uint8_t> value) const
{
	for (int saveFileIdx = this->startByte + this->size - 1, valueIdx = value.size() - 1; saveFileIdx >= this->startByte; saveFileIdx--, valueIdx--) saveFile[saveFileIdx] = valueIdx < 0 ? 0x0 : value.at(valueIdx);
}

unsigned int DataObject::getLengthInBytes() const
{
	return this->size;
}

Type DataObject::getType() const
{
	return this->type;
}

unsigned int DataObject::getStartByte() const
{
	return this->startByte;
}

void DataObject::print()
{
	std::cout << "DataObject(" <<
		"startByte = 0x" << std::hex << this->startByte << ", " <<
		"lengthInBytes = " << std::dec << this->size << ", " <<
		"type = " << Types::toString(this->type) << ");\n";
}
