#pragma once

#include "SaveDefines.h"
#include <vector>
#include <stdint.h>
#include "DataObject.h"

typedef struct
{
	DataObject dataObject;
	int staticValue;
} Element;

class ArrayObject : public DataObject
{
	std::vector<std::vector<DataObject>> dataObjs = std::vector<std::vector<DataObject>>();
	unsigned int numRows, numColumns;
	std::vector<int> staticValues;
public:
	ArrayObject(unsigned int elementSizeBytes, unsigned int arraySize, const std::vector<Element> elements);
	virtual const DataObject* at(unsigned int row, unsigned int column) const;
	virtual const int getStaticValue(unsigned int column) const;
};
