#include "SaveFile.h"

int main()
{
	try
	{
		SaveFile* saveFile = new SaveFile();

		saveFile->setValue(PCPMPlayer1Z, -5553.44f);
		float value = saveFile->getValue<float>(PCPMPlayer1Z);
		std::cout << "Float Output: " << value << '\n';

		saveFile->setValue(THUMLevel, 12345);
		int integer = saveFile->getValue<int>(THUMLevel);
		std::cout << "Integer Output: " << std::dec << integer << '\n';

		saveFile->setValue(OPTDShowSubtitles, true);
		bool boolean = saveFile->getValue<bool>(OPTDShowSubtitles);
		std::cout << "Bool Output: " << (boolean ? "true" : "false") << '\n';

		saveFile->setValue(THUMNameString, "hello, world!");
		std::string string = saveFile->getValue<std::string>(THUMNameString);
		std::cout << "String Output: " << string << '\n';

		saveFile->setArrayValue(MINEArray, 1, MINECooldown, "cd");
		int arrayValue = saveFile->getArrayValue<int>(MINEArray, 1, MINECooldown);
		std::cout << "Array Output: 0x" << std::hex << arrayValue << '\n';

		saveFile->saveToFile();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
