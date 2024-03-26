#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include "SaveFieldID.h"
#include <iostream>
#include <fstream>
#include "DataObject.h"
#include "ArrayObject.h"
#include "ArrayID.h"

#define SAVEFILE_LENGTH_BYTES 0x28000
#define NUM_SECTIONS 12

class SaveFile
{
    std::string fileLocation;
    uint8_t saveFile[SAVEFILE_LENGTH_BYTES];
    bool isLittleEndian;

    uint8_t getByteAt(unsigned int x);
    void setByteAt(unsigned int x, uint8_t b);

    static const DataObject* dataMap[];

public:
    SaveFile(std::string fileLocation);
    std::vector<uint8_t> getRawBytes(SaveFieldID sfID);

    void setRawBytes(SaveFieldID sfID, unsigned int value);
    void setRawBytes(SaveFieldID sfID, const char* value);
    void setRawBytes(SaveFieldID sfID, std::vector<uint8_t> value);
    void setRawBytes(SaveFieldID sfID, float value);

    void setArrayRawBytes(SaveFieldID aID, unsigned int index, unsigned int elementName, unsigned int value);
    void setArrayRawBytes(SaveFieldID aID, unsigned int index, unsigned int elementName, const char* value);
    void setArrayRawBytes(SaveFieldID aID, unsigned int index, unsigned int elementName, std::vector<uint8_t> value);
    void setArrayRawBytes(SaveFieldID aID, unsigned int index, unsigned int elementName, float value);

    void saveToFile();

    template<typename T>
    void setValue(SaveFieldID sfID, T value)
    {
        this->setRawBytes(sfID, value);
    }

    template<typename T>
    void setArrayValue(SaveFieldID aID, unsigned int index, unsigned int elementName, T value)
    {
        this->setArrayRawBytes(aID, index, elementName, value);
    }
};
