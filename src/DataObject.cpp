#include "DataObject.h"
#include <ios>
#include <iostream>
#include <stdexcept>

DataObject::DataObject(unsigned int startByte, unsigned int lengthInBytes, Type type)
{
	if (lengthInBytes == 0) throw std::invalid_argument("Cannot instantiate DataObject with 0 length");
	if (startByte + lengthInBytes > SAVEFILE_LENGTH_BYTES) throw std::invalid_argument("DataObject exceeds save file length");

	this->startByte = startByte;
	this->startBit = 7;
	this->bitLength = lengthInBytes * 8;
	this->type = type;

	this->numRows = 1;
	this->numColumns = 1;

	this->endBit = 0;
	this->endByte = startByte + lengthInBytes - 1;
}

DataObject::DataObject(unsigned int startByte, unsigned int startBit, unsigned int lengthInBits, Type type)
{
	if (lengthInBits == 0) throw std::invalid_argument("Cannot instantiate DataObject with 0 length");
	
	this->startByte = startByte;
	this->startBit = startBit;
	this->bitLength = lengthInBits;
	this->type = type;

	this->numRows = 1;
	this->numColumns = 1;

	this->endBit = 7 - (((7 - startBit) + lengthInBits - 1) % 8);
	this->endByte = ((startByte * 8) + (7 - startBit) + lengthInBits - 1) / 8;

	if (this->endByte + 1 > SAVEFILE_LENGTH_BYTES) throw std::invalid_argument("DataObject exceeds save file length");
}

DataObject::DataObject(unsigned int startByte, unsigned int lengthInBytes, Type type, unsigned int numRows, unsigned int numColumns)
{
    DataObject(startByte, lengthInBytes, type);

    this->numRows = numRows;
    this->numColumns = numColumns;
}

std::vector<uint8_t> DataObject::getRawBytes(uint8_t (&saveFile)[SAVEFILE_LENGTH_BYTES]) const
{
	std::vector<uint8_t> result;

	uint8_t constructedByte = 0;

	unsigned int currByte = this->endByte;
	unsigned int currBufferBit = this->endBit;
	for (int i = 0; i < this->bitLength; i++)
	{
		if ((saveFile[currByte] >> currBufferBit) & 0x1) constructedByte |= (1 << (i % 8));

		currBufferBit++;
		currBufferBit = currBufferBit % 8;

		if (currBufferBit == 0) currByte--;
		if (currBufferBit == this->endBit)
		{
			result.insert(result.begin(), constructedByte);
			constructedByte = 0;
		}
	}
	if (constructedByte != 0) result.insert(result.begin(), constructedByte); // add MSB if it's not zero
	else if (result.size() == 0) result.push_back(0); // if constructed byte and result size is zero, then the raw bytes are 0

	return result;
}

/*
*	Sets the saveFile bytes associated with this DataObject to the bytes in value
*
*	In the case when bytes.size() > this.size(), the additional MSB in bytes are ignored (bytes = 0xABCD -> DataObject = 0xCD for this.size() = 1)
*	In the case when bytes.size() < this.size(), the additional MSB associated with the DataObject are cleared (bytes = 0xFF -> DataObject = 0x00FF for this.size() = 2)
*/
bool DataObject::setRawBytes(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES], std::vector<uint8_t> value) const
{
    //if (value.size() > (this->getLengthInBits() / 8))
	for (int i = 0, currBit = this->endBit, currByte = this->endByte, currValueByte = value.size() - 1; i < this->bitLength; i++, (++currBit) %= 8, currByte = ((currBit == 0) ? currByte - 1 : currByte), currValueByte = ((currBit == this->endBit) ? currValueByte - 1 : currValueByte)) saveFile[currByte] = ((currValueByte >= 0) && ((value.at(currValueByte) >> (i % 8)) & 0x1)) ? (saveFile[currByte] | (1 << currBit)) : (saveFile[currByte] & ~(1 << currBit));
    return true;
}

void DataObject::setValue(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES], std::string value) const
{
    for (int i = value.size(); i < (this->bitLength / 8); i++) value += (char)0;
    this->setRawBytes(saveFile, Types::toRaw(value));
}

unsigned int DataObject::getLengthInBits() const
{
	return this->bitLength;
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
		"startBit = " << this->startBit << ", " <<
		"lengthInBits = " << std::dec << this->bitLength << ", " <<
		"type = " << Types::toString(this->type) << ");\n";
}
