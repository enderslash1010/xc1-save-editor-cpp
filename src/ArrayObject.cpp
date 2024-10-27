#include "ArrayObject.h"
#include <stdexcept>

ArrayObject::ArrayObject(unsigned int elementSizeBytes, unsigned int arraySize, const std::vector<Element> elements) :
    DataObject(elements.at(0).dataObject.getStartByte(), (elementSizeBytes * arraySize), ARRAY_T, arraySize, elements.size())
{
	if (elements.size() == 0 || elementSizeBytes == 0) throw std::invalid_argument("Cannot instantiate ArrayObject: Empty element");

	// Ensure elements has same number of bytes as elementSizeBytes
	int numBits = 0;
	for (int i = 0; i < elements.size(); i++)
    {
		numBits += elements.at(i).dataObject.getLengthInBits();
		this->staticValues.push_back(elements.at(i).staticValue);
	}
	if (numBits % 8 != 0) throw std::invalid_argument("Cannot instantiate ArrayObject: element not byte aligned");
	else if ((numBits / 8) != elementSizeBytes) throw std::invalid_argument("Cannot instantiate ArrayObject: Mismatched element size");

	// Process dataObj into a 2D array of DataObjects
	unsigned int currByte = elements.at(0).dataObject.getStartByte();
	int currBit = 7;

    for (int row = 0; row < arraySize; row++)
	{
		// Initialize element for row n
		std::vector<DataObject> element;

		// Populate element with same DataObjects in dataObj, with their own startByte
        for (int column = 0; column < elements.size(); column++)
		{
			unsigned int sizeInBits = elements.at(column).dataObject.getLengthInBits();
            Type type = elements.at(column).dataObject.getType();

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

const int ArrayObject::getStaticValue(unsigned int column) const
{
	if (column >= this->staticValues.size()) throw std::out_of_range("Array element " + std::to_string(column) + " out of bounds");
	return this->staticValues.at(column);
}
