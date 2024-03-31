#include "SaveFile.h"

int main()
{
	try
	{
		SaveFile* saveFile = new SaveFile("testSave");

		saveFile->setValue(TIMEPlayTime, -222);

		int value = saveFile->getValue<int>(TIMEPlayTime, false);
		std::cout << "Output: " << std::dec << value << '\n';

		saveFile->saveToFile();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}
