#include "SaveFile.h"

int main()
{

	try
	{
		SaveFile* saveFile = new SaveFile("testSave");
		std::vector<uint8_t> bytes = saveFile->getRawBytes(THUMSystemSaveFlag);

		// Setting a save field's raw bytes
		saveFile->setRawBytes(ITEMMoney, (unsigned int) 42069);
		saveFile->setRawBytes(ITEMMoney, {0x12, 0x34});

		// Setting a save field using int, string, and float
		saveFile->setValue(ITEMMoney, (unsigned int) -90);
		saveFile->setValue(ITEMMoney, "abcdef");
		saveFile->setValue(ITEMMoney, 123.123f);

		// Setting a save field as an array using an int, string, and float
		saveFile->setArrayValue(ITEMMoney, 0, 0, (unsigned int) -25);
		saveFile->setArrayValue(ITEMMoney, 0, 0, "blue");
		saveFile->setArrayValue(ITEMMoney, 0, 0, 123.123f);

		saveFile->setArrayValue(TBOXArray, 1, TBOXPositionZ, 3.14159f);

		saveFile->saveToFile();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}
