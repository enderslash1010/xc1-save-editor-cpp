#include "SaveFile.h"

#define NUM_SECTIONS 12

const int sectionRanges[NUM_SECTIONS][2] =
{
	{0x20, 0x9CA0},      // THUM 0
	{0xA030, 0xB244},    // FLAG 1
	{0xB260, 0x11E88},   // GAME 2
	{0x11EB0, 0x11EBC},  // TIME 3
	{0x11EE0, 0x11F14},  // PCPM 4
	{0x11F30, 0x11F40},  // CAMD 5
	{0x11F60, 0x24080},  // ITEM 6
	{0x24090, 0x240A0},  // WTHR 7
	{0x240C0, 0x240D0},  // SNDS 8
	{0x240F0, 0x24474},  // MINE 9
	{0x244A0, 0x246D4}, // TBOX 10
	{0x248B0, 0x248F0}  // OPTD 11
};

const int checksumLocations[NUM_SECTIONS] = { 0x1E, 0xA02E, 0xB25E, 0x11EAE, 0x11EDE, 0x11F2E, 0x11F5E, 0x2408E, 0x240BE, 0x240EE, 0x2449E, 0x248AE };
const char* sectionNames[NUM_SECTIONS] = { "THUM", "FLAG", "GAME", "TIME", "PCPM", "CAMD", "ITEM", "WTHR", "SNDS", "MINE", "TBOX", "OPTD" };

// dataMap stores all DataObjects in the save file
// Make sure there is a SaveFieldID enum for each DataObject here, in order
const DataObject dataMap[] =
{
	// THUM
	DataObject(0x84, 2, UINT16_T), // THUMLevel
	DataObject(0x2A, 2, UINT16_T), // THUMPlayTimeHours
	DataObject(0x2C, 2, UINT16_T), // THUMPlayTimeMinutes
	DataObject(0x23, 1, UINT8_T), // THUMPlayTimeSeconds
	DataObject(0x29, 2, UINT16_T), // THUMSaveTimeDay
	DataObject(0x26, 2, UINT16_T), // THUMSaveTimeMonth
	DataObject(0x24, 2, UINT16_T), // THUMSaveTimeYear
	DataObject(0x28, 1, UINT8_T), // THUMSaveTimeHour
	DataObject(0x22, 1, UINT8_T), // THUMSaveTimeMinute
	DataObject(0x37, 1, UINT8_T), // THUMPictureSlot1
	DataObject(0x3B, 1, UINT8_T), // THUMPictureSlot2
	DataObject(0x3F, 1, UINT8_T), // THUMPictureSlot3
	DataObject(0x43, 1, UINT8_T), // THUMPicutreSlot4
	DataObject(0x47, 1, UINT8_T), // THUMPictureSlot5
	DataObject(0x4B, 1, UINT8_T), // THUMPictureSlot6
	DataObject(0x4F, 1, UINT8_T), // THUMPictureSlot7
	DataObject(0x64, 32, STRING), // THUMNameString
	DataObject(0x86, 1, UINT8_T), // THUMSystemSaveFlag
	DataObject(0x87, 1, UINT8_T), // THUMNGPlusFlag
	DataObject(0xE0, 38048, TPL), // THUMSaveImage

	// FLAG
	DataObject(0xA0B2, 2, UINT16_T), // FLAGScenarioID

	// GAME
	DataObject(0xB260, 4, UINT32_T), // GAMEMapNum
	DataObject(0xB264, 4, STRING), // GAMEMapNumString
	DataObject(0xD1FE, 2, UINT16_T), // GAMEPlayer1
	DataObject(0xD202, 2, UINT16_T), // GAMEPlayer2
	DataObject(0xD206, 2, UINT16_T), // GAMEPlayer3
	DataObject(0xD20A, 2, UINT16_T), // GAMEPlayer4
	DataObject(0xD20E, 2, UINT16_T), // GAMEPlayer5
	DataObject(0xD212, 2, UINT16_T), // GAMEPlayer6
	DataObject(0xD216, 2, UINT16_T), // GAMEPlayer7
	DataObject(0xF8D0, 4, UINT32_T), // GAMEShulkLevel
	DataObject(0xFBD4, 4, UINT32_T), // GAMEReynLevel
	DataObject(0xFEC8, 4, UINT32_T), // GAMEFioraLevel
	DataObject(0x101DC, 4, UINT32_T), // GAMEDunbanLevel
	DataObject(0x104E0, 4, UINT32_T), // GAMESharlaLevel
	DataObject(0x107E4, 4, UINT32_T), // GAMERikiLevel
	DataObject(0x10AE8, 4, UINT32_T), // GAMEMeliaLevel
	DataObject(0x10DEC, 4, UINT32_T), // GAMESevenLevel
	DataObject(0x110F0, 4, UINT32_T), // GAMEDicksonLevel
	DataObject(0x113F4, 4, UINT32_T), // GAMEMumkharLevel
	DataObject(0x116F8, 4, UINT32_T), // GAMEAlvisLevel
	DataObject(0x119FC, 4, UINT32_T), // GAMEPrologueDunbanLevel

	// TIME
	DataObject(0x11EB0, 4, UINT32_T), // TIMEPlayTime
	DataObject(0x11EB8, 4, UINT32_T), // TIMEDayCount
	DataObject(0x11EB4, 4, UINT32_T), // TIMEDayTime
	DataObject(0x11EBA, 2, UINT16_T), // TIMEYearCount

	// PCPM
	DataObject(0x11EE0, 4, FLOAT), // PCPMPlayer1X
	DataObject(0x11EE4, 4, FLOAT), // PCPMPlayer1Y
	DataObject(0x11EE8, 4, FLOAT), // PCPMPlayer1Z
	DataObject(0x11EEC, 4, FLOAT), // PCPMPlayer1Angle
	DataObject(0x11EF0, 4, FLOAT), // PCPMPlayer2X
	DataObject(0x11EF4, 4, FLOAT), // PCPMPlayer2Y
	DataObject(0x11EF8, 4, FLOAT), // PCPMPlayer2Z
	DataObject(0x11EFC, 4, FLOAT), // PCPMPlayer2Angle
	DataObject(0x11F00, 4, FLOAT), // PCPMPlayer3X
	DataObject(0x11F04, 4, FLOAT), // PCPMPlayer3Y
	DataObject(0x11F08, 4, FLOAT), // PCPMPlayer3Z
	DataObject(0x11F0C, 4, FLOAT), // PCPMPlayer3Angle

	// CAMD
	DataObject(0x11F30, 4, FLOAT), // CAMDVerticalPosition
	DataObject(0x11F34, 4, FLOAT), // CAMDHorizontalPosition
	DataObject(0x11F3C, 4, FLOAT), // CAMDDistance

	// ITEM
	DataObject(0x24048, 4, INT32_T), // ITEMMoney
	DataObject(0x1C4EC, 7800, ARRAY), // ITEMWeaponArray
	DataObject(0x206D8, 4800, ARRAY), // ITEMGemArray

	// WTHR
	DataObject(0x24090, 4, UINT32_T), // WTHRReroll
	DataObject(0x24098, 4, UINT32_T), // WTHRMap
	DataObject(0x24095, 1, UINT8_T), // WTHRForegreoundWeather
	DataObject(0x24096, 2, UINT16_T), // WTHRUnk1
	DataObject(0x2409D, 1, UINT8_T), // WTHRBackgroundWeather
	DataObject(0x2409F, 1, UINT8_T), // WTHRUnk2

	// SNDS

	// MINE
	DataObject(0x240F0, 900, ARRAY), // MINEArray

	// TBOX
	DataObject(0x244A3, 1, UINT8_T), // TBOXBoxCount
	DataObject(0x244A4, 592, ARRAY), // TBOXArray

	// OPTD
	DataObject(0x248B0, 1, BOOL), // OPTDNonInvertedYAxis
	DataObject(0x248B1, 1, BOOL), // OPTDNonInvertedXAxis
	DataObject(0x248B2, 1, UINT8_T), // OPTDYAxisSpeed
	DataObject(0x248B3, 1, UINT8_T), // OPTDXAxisSpeed
	DataObject(0x248B4, 1, UINT8_T), // OPTDZoomSpeed
	DataObject(0x248B5, 1, UINT8_T), // OPTDPointOfView
	DataObject(0x248B6, 1, BOOL), // OPTDAngleCorrection
	DataObject(0x248B7, 1, BOOL), // OPTDBattleCamera
	DataObject(0x248BF, 1, UINT8_T), // OPTDGamma
	DataObject(0x248C0, 1, BOOL), // OPTDMinimapOn
	DataObject(0x248C1, 1, BOOL), // OPTDMinimapRotate
	DataObject(0x248CC, 1, BOOL), // OPTDJapaneseVoice
	DataObject(0x248D0, 1, BOOL), // OPTDShowControls
	DataObject(0x248D1, 1, BOOL), // OPTDShowArtDescriptions
	DataObject(0x248D2, 1, BOOL), // OPTDShowBuffDebuffInfoEveryTime
	DataObject(0x248D3, 1, BOOL), // OPTDShowEnemyIcons
	DataObject(0x248D4, 1, BOOL), // OPTDShowBuffDefbuffIndicator
	DataObject(0x248D5, 1, BOOL), // OPTDShowDestinationMarker
	DataObject(0x248E0, 1, BOOL), // OPTDAutoEventScrolling
	DataObject(0x248E1, 1, BOOL), // OPTDFastDialogueText
	DataObject(0x248E2, 1, BOOL) // OPTDShowSubtitles
};

static void fixChecksums(uint8_t(&saveFile)[SAVEFILE_LENGTH_BYTES]);

SaveFile::SaveFile(std::string fileLocation)
{
	std::cout << "Opening " << fileLocation << "...\n";

	this->fileLocation = fileLocation;
    std::ifstream buffer(fileLocation, std::ios::binary);

    // Throw error if unable to open file
    if (!buffer) throw std::runtime_error("Unable to open file " + fileLocation);

    // Read file into array
    buffer.seekg(0, std::ios::beg); // Go to beginning of buffer
    buffer.read((char*) saveFile, SAVEFILE_LENGTH_BYTES); // Read file into saveFile array
    buffer.close();

    // Check if file magic is "USRD"
    if (saveFile[0] != 'U' || saveFile[1] != 'S' || saveFile[2] != 'R' || saveFile[3] != 'D') throw std::runtime_error("Invalid save file " + fileLocation);

	saveToFile();

	std::cout << "Successfully opened " << fileLocation << '\n';
}

// Saves saveFile byte array to file, automatically fixing checksums
void SaveFile::saveToFile()
{
	fixChecksums(saveFile);

	std::ofstream outputFile(fileLocation, std::ios::binary);
	if (!outputFile)
	{
		outputFile.close();
		throw std::runtime_error("Error writing to file " + fileLocation);
	}
	outputFile.write((char *) saveFile, SAVEFILE_LENGTH_BYTES);
	outputFile.close();
}

inline uint8_t SaveFile::getByteAt(unsigned int x)
{
	return this->saveFile[x];
}

inline void SaveFile::setByteAt(unsigned int x, uint8_t b)
{
	this->saveFile[x] = b;
}

std::vector<uint8_t> SaveFile::getRawBytes(SaveFieldID sfID)
{
	DataObject dataObj = dataMap[sfID];
	std::vector<uint8_t> result = dataObj.getRawBytes(this->saveFile);
	return result;
}

// For up to 8 bytes
void SaveFile::setRawBytes(SaveFieldID sfID, uint64_t value)
{
	((DataObject) dataMap[sfID]).setRawBytes(this->saveFile, value);
}

// For more than 8 bytes
void SaveFile::setRawBytes(SaveFieldID sfID, std::vector<uint8_t> value)
{
	((DataObject) dataMap[sfID]).setRawBytes(this->saveFile, value);
}

// CRC16 Polynomial: 1 + x^2 + x^15 + x^16 -> 0x8005 (1000 0000 0000 0101)
const int lookupTable[] =
{
	0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
	0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
	0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
	0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
	0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
	0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
	0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
	0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
	0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
	0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
	0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
	0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
	0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
	0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
	0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
	0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
	0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
	0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
	0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
	0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
	0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
	0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
	0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
	0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
	0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
	0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
	0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
	0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
	0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
	0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
	0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
	0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

// Computes and fixes checksums in the provided save file
// Modifies input parameter, not actual file; Will need to save to file to preserve changes
static void fixChecksums(uint8_t (&saveFile)[SAVEFILE_LENGTH_BYTES])
{
	for (int section = 0; section < NUM_SECTIONS; section++)
	{
		// Compute CRC16
		unsigned int crc = 0x0;
		for (int b = sectionRanges[section][0]; b < sectionRanges[section][1]; b++)
		{
			crc = (crc >> 8) ^ lookupTable[(crc ^ saveFile[b]) & 0xFF];
		}
		
		// Output computed checksum with the save file's checksum
		std::cout << sectionNames[section] << ": " << std::hex << crc << ", " << (int) saveFile[checksumLocations[section]] << (int) saveFile[checksumLocations[section] + 1] << '\n';

		// Save computed value to saveFile
		saveFile[checksumLocations[section]] = crc >> 8;
		saveFile[checksumLocations[section] + 1] = crc & 0xFF;
	}
}
