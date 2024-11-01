#pragma once

#include <vector>
#include "DataObject.h"

typedef struct
{
	DataObject dataObject;
	int staticValue;
} Element;

class ArrayObject : public DataObject
{
	std::vector<std::vector<DataObject>> dataObjs = std::vector<std::vector<DataObject>>();
	std::vector<int> staticValues;
public:
	ArrayObject(unsigned int elementSizeBytes, unsigned int arraySize, const std::vector<Element> elements);
    const DataObject* at(unsigned int row, unsigned int column) const;
	virtual const int getStaticValue(unsigned int column) const;
};
