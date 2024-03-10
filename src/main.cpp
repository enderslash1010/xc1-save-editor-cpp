#include "SaveFile.h"

int main()
{
	try
	{
		SaveFile* saveFile = new SaveFile("testSave");
		std::vector<uint8_t> bytes = saveFile->getRawBytes(FLAGScenarioID);
		
		std::cout << "0x";
		for (uint8_t byte : bytes)
		{
			std::cout << (int)byte;
		}
		std::cout << '\n';

		saveFile->setRawBytes(ITEMMoney, 42069);
		saveFile->saveToFile();

	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}
