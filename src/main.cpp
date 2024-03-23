#include "SaveFile.h"
#include <iostream>

int main()
{
	try
	{
		SaveFile* saveFile = new SaveFile("testSave");
		std::vector<uint8_t> bytes = saveFile->getRawBytes(THUMSystemSaveFlag);
		
		std::cout << "0x";
		for (uint8_t byte : bytes)
		{
			std::cout << (int)byte;
		}
		std::cout << '\n';

		saveFile->setRawBytes(ITEMMoney, (uint64_t) 42069);
		saveFile->setRawBytes(ITEMMoney, { 0x12, 0x34 });
		saveFile->setValue(ITEMMoney, "abcd");
		saveFile->saveToFile();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}
