#include "ArrayObject.h"

ArrayObject::ArrayObject(unsigned int elementSizeBytes, unsigned int arraySize, const std::vector<DataObject> dataObj) :
	DataObject(dataObj.at(0).getStartByte(), (elementSizeBytes * arraySize), ARRAY_T)
{
	if (dataObj.size() == 0 || elementSizeBytes == 0) throw std::invalid_argument("Cannot instantiate ArrayObject: Empty element");

	this->numRows = arraySize;
	this->numColumns = dataObj.size();

	// Ensure dataObj element has same number of bytes as elementSizeBytes
	int numBits = 0;
	for (int i = 0; i < dataObj.size(); i++)
	{
		numBits += dataObj.at(i).getLengthInBits();
	}
	if (numBits % 8 != 0) throw std::invalid_argument("Cannot instantiate ArrayObject: element not byte aligned");
	else if ((numBits / 8) != elementSizeBytes) throw std::invalid_argument("Cannot instantiate ArrayObject: Mismatched element size");

	// Process dataObj into a 2D array of DataObjects
	unsigned int currByte = ((DataObject) dataObj.at(0)).getStartByte();
	int currBit = 7;

	for (int row = 0; row < this->numRows; row++)
	{
		// Initialize element for row n
		std::vector<DataObject> element;

		// Populate element with same DataObjects in dataObj, with their own startByte
		for (int column = 0; column < this->numColumns; column++)
		{
			unsigned int sizeInBits = ((DataObject)dataObj.at(column)).getLengthInBits();
			Type type = ((DataObject)dataObj.at(column)).getType();

			element.push_back(DataObject(currByte, currBit, sizeInBits, type));

			for (int i = 0; i < sizeInBits; i++)
			{
				currBit--;
				if (currBit < 0)
				{
					currBit = 7;
					currByte++;
				}
			}

		}

		// Put element in datObjs
		this->dataObjs.push_back(element);
	}
}

const DataObject* ArrayObject::at(unsigned int row, unsigned int column) const
{
	if (row < this->numRows && column < this->numColumns) return &(this->dataObjs.at(row).at(column));
	else return NULL;
}
