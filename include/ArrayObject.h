#pragma once

#include "SaveDefines.h"
#include <vector>
#include <stdint.h>
#include "DataObject.h"

class ArrayObject : public DataObject
{
	std::vector<std::vector<DataObject>> dataObjs = std::vector<std::vector<DataObject>>();
	unsigned int numRows, numColumns;

public:
	ArrayObject(const std::vector<DataObject> dataObj, unsigned int elementSize, unsigned int arraySize);
	virtual const DataObject* at(unsigned int row, unsigned int column) const;
};
