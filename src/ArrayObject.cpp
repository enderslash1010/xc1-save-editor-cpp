#include "ArrayObject.h"

ArrayObject::ArrayObject(const std::vector<DataObject> dataObj, unsigned int elementSize, unsigned int arraySize) : 
	DataObject(((DataObject)dataObj.at(0)).getLengthInBytes(), (elementSize * arraySize), ARRAY)
{
	this->numRows = arraySize;
	this->numColumns = dataObj.size();

	// Process dataObj into a 2D array of DataObjects
	unsigned int currByte = ((DataObject) dataObj.at(0)).getStartByte();
	for (int row = 0; row < this->numRows; row++)
	{
		// Initialize element for row n
		std::vector<DataObject> element;

		// Populate element with same DataObjects in dataObj, with their own startByte
		for (int column = 0; column < this->numColumns; column++)
		{
			unsigned int size = ((DataObject) dataObj.at(column)).getLengthInBytes();
			Type type = ((DataObject)dataObj.at(column)).getType();
			element.push_back(DataObject(currByte, size, type));
			currByte += size;
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
