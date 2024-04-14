#include "SaveFile.h"

int main()
{
	try
	{
		SaveFile* saveFile = new SaveFile("testSave");

		saveFile->setArrayValue(MINEArray, 4, MINENumHarvests, 0xCD);

		unsigned int value = saveFile->getArrayValue<unsigned int>(MINEArray, 4, MINENumHarvests);
		std::cout << "Output: " << std::hex << value << '\n';

		saveFile->saveToFile();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}
