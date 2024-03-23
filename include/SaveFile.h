#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <SaveFieldID.h>
#include <iostream>
#include <fstream>
#include <DataObject.h>

#define SAVEFILE_LENGTH_BYTES 0x28000

class SaveFile
{
    std::string fileLocation;
    uint8_t saveFile[SAVEFILE_LENGTH_BYTES];

    uint8_t getByteAt(unsigned int x);
    void setByteAt(unsigned int x, uint8_t b);

public:
    SaveFile(std::string fileLocation);
    std::vector<uint8_t> getRawBytes(SaveFieldID sfID);
    void setRawBytes(SaveFieldID sfID, uint64_t value);
    void setRawBytes(SaveFieldID sfID, std::vector<uint8_t> value);
    void saveToFile();

    template <typename T> void setValue(SaveFieldID sfID, T value);
};
