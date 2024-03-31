#include "SaveFile.h"

int main()
{
	try
	{
		SaveFile* saveFile = new SaveFile("testSave");

		saveFile->setArrayValue(TBOXArray, 1, TBOXZeroObject, "abcd");

		std::string value = saveFile->getArrayValue<std::string>(TBOXArray, 1, TBOXZeroObject, false);
		std::cout << "Output: " << std::dec << value << '\n';

		saveFile->saveToFile();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}
