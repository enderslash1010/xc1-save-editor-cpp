#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include "SaveFieldID.h"
#include "DataObject.h"
#include "ArrayObject.h"
#include "Types.h"
#include "SaveDefines.h"
#include <stdexcept>

#define NUM_SECTIONS 12

class SaveFile
{
    std::string fileLocation;
    uint8_t saveFile[SAVEFILE_LENGTH_BYTES];

	// dataMap stores all DataObjects in the save file
	// Make sure there is a SaveFieldID enum for each DataObject here, in order
	const DataObject* dataMap[LAST_INDEX] =
	{
		// THUM
        new DataObject(0x84, 2, UINT_T), // THUMLevel*
        new DataObject(0x2A, 2, UINT_T), // THUMPlayTimeHours*
        new DataObject(0x2C, 2, UINT_T), // THUMPlayTimeMinutes*
		new DataObject(0x23, 1, UINT_T), // THUMPlayTimeSeconds
        new DataObject(0x29, 1, UINT_T), // THUMSaveTimeDay*
        new DataObject(0x26, 2, UINT_T), // THUMSaveTimeMonth*
        new DataObject(0x24, 2, UINT_T), // THUMSaveTimeYear*
        new DataObject(0x28, 1, UINT_T), // THUMSaveTimeHour*
        new DataObject(0x22, 1, UINT_T), // THUMSaveTimeMinute*
        new DataObject(0x37, 1, UINT_T), // THUMPictureSlot1*
        new DataObject(0x3B, 1, UINT_T), // THUMPictureSlot2*
        new DataObject(0x3F, 1, UINT_T), // THUMPictureSlot3*
        new DataObject(0x43, 1, UINT_T), // THUMPicutreSlot4*
        new DataObject(0x47, 1, UINT_T), // THUMPictureSlot5*
        new DataObject(0x4B, 1, UINT_T), // THUMPictureSlot6*
        new DataObject(0x4F, 1, UINT_T), // THUMPictureSlot7*
        new DataObject(0x64, 32, STRING_T), // THUMNameString*
        new DataObject(0x86, 1, UINT_T), // THUMSystemSaveFlag*
        new DataObject(0x87, 1, UINT_T), // THUMNGPlusFlag*
		new DataObject(0xE0, 38048, TPL_T), // THUMSaveImage

		// FLAG
        new DataObject(0xA0B2, 2, UINT_T), // FLAGScenarioID*

		// GAME
        new DataObject(0xB260, 4, UINT_T), // GAMEMapNum*
        new DataObject(0xB264, 4, STRING_T), // GAMEMapNumString*
        new DataObject(0xB284, 4, UINT_T), // GAMEMapNum2*
        new DataObject(0xB288, 4, STRING_T), // GAMEMapNumString2*
        new DataObject(0xD1FE, 2, UINT_T), // GAMEPlayer1*
        new DataObject(0xD202, 2, UINT_T), // GAMEPlayer2*
        new DataObject(0xD206, 2, UINT_T), // GAMEPlayer3*
        new DataObject(0xD20A, 2, UINT_T), // GAMEPlayer4*
        new DataObject(0xD20E, 2, UINT_T), // GAMEPlayer5*
        new DataObject(0xD212, 2, UINT_T), // GAMEPlayer6*
        new DataObject(0xD216, 2, UINT_T), // GAMEPlayer7*
        new DataObject(0xF8D0, 4, UINT_T), // GAMEShulkLevel*
        new DataObject(0xFBD4, 4, UINT_T), // GAMEReynLevel*
        new DataObject(0xFED8, 4, UINT_T), // GAMEFioraLevel*
        new DataObject(0x101DC, 4, UINT_T), // GAMEDunbanLevel*
        new DataObject(0x104E0, 4, UINT_T), // GAMESharlaLevel*
        new DataObject(0x107E4, 4, UINT_T), // GAMERikiLevel*
        new DataObject(0x10AE8, 4, UINT_T), // GAMEMeliaLevel*
        new DataObject(0x10DEC, 4, UINT_T), // GAMESevenLevel*
        new DataObject(0x110F0, 4, UINT_T), // GAMEDicksonLevel*
        new DataObject(0x113F4, 4, UINT_T), // GAMEMumkharLevel*
        new DataObject(0x116F8, 4, UINT_T), // GAMEAlvisLevel*
        new DataObject(0x119FC, 4, UINT_T), // GAMEPrologueDunbanLevel*

		// TIME
        new DataObject(0x11EB0, 4, UINT_T), // TIMEPlayTime*
        new DataObject(0x11EB8, 2, UINT_T), // TIMEDayCount*
        new DataObject(0x11EB4, 4, FLOAT_T), // TIMEDayTime*
        new DataObject(0x11EBA, 2, UINT_T), // TIMEYearCount*

		// PCPM
        new DataObject(0x11EE0, 4, FLOAT_T), // PCPMPlayer1X*
        new DataObject(0x11EE4, 4, FLOAT_T), // PCPMPlayer1Y*
        new DataObject(0x11EE8, 4, FLOAT_T), // PCPMPlayer1Z*
        new DataObject(0x11EEC, 4, FLOAT_T), // PCPMPlayer1Angle*
        new DataObject(0x11EF0, 4, FLOAT_T), // PCPMPlayer2X*
        new DataObject(0x11EF4, 4, FLOAT_T), // PCPMPlayer2Y*
        new DataObject(0x11EF8, 4, FLOAT_T), // PCPMPlayer2Z*
        new DataObject(0x11EFC, 4, FLOAT_T), // PCPMPlayer2Angle*
        new DataObject(0x11F00, 4, FLOAT_T), // PCPMPlayer3X*
        new DataObject(0x11F04, 4, FLOAT_T), // PCPMPlayer3Y*
        new DataObject(0x11F08, 4, FLOAT_T), // PCPMPlayer3Z*
        new DataObject(0x11F0C, 4, FLOAT_T), // PCPMPlayer3Angle*

		// CAMD
        new DataObject(0x11F30, 4, FLOAT_T), // CAMDVerticalPosition*
        new DataObject(0x11F34, 4, FLOAT_T), // CAMDHorizontalPosition*
        new DataObject(0x11F3C, 4, FLOAT_T), // CAMDDistance*

		// ITEM
		new DataObject(0x24048, 4, INT_T), // ITEMMoney
		new ArrayObject(52, 150, std::vector<Element> { // ITEMWeaponArray
			{DataObject(0x1C4EC, 7, 12, UINT_T), 0}, // ITEMWeaponID1
			{DataObject(0x1C4ED, 3, 4, UINT_T), 2}, // ITEMWeaponStatic1 (2)
			{DataObject(0x1C4EE, 7, 11, UINT_T), 0}, // ITEMWeaponID2
			{DataObject(0x1C4EF, 4, 5, UINT_T), 0 }, // ITEMWeaponStatic2 (0)
			{DataObject(0x1C4F0, 1, UINT_T), 0}, // ITEMWeaponStatic3 (0)
			{DataObject(0x1C4F1, 1, UINT_T), 0}, // ITEMWeaponInventorySlot
			{DataObject(0x1C4F2, 1, UINT_T), 1}, // ITEMWeaponStatic4 (1)
			{DataObject(0x1C4F3, 1, UINT_T), 0}, // ITEMWeaponStatic5 (0)
			{DataObject(0x1C4F4, 8, UINT_T), 0}, // ITEMWeaponGem1ID
			{DataObject(0x1C4FC, 8, UINT_T), 0}, // ITEMWeaponGem2ID
			{DataObject(0x1C504, 8, UINT_T), 0}, // ITEMWeaponGem3ID
			{DataObject(0x1C50C, 8, UINT_T), 0}, // ITEMWeaponGem4ID
			{DataObject(0x1C514, 2, UINT_T), 0}, // ITEMWeaponGem1Index
			{DataObject(0x1C516, 2, UINT_T), 0}, // ITEMWeaponGem2Index
			{DataObject(0x1C518, 2, UINT_T), 0}, // ITEMWeaponGem3Index
			{DataObject(0x1C51A, 2, UINT_T), 0}, // ITEMWeaponGem4Index
			{DataObject(0x1C51C, 1, UINT_T), 0}, // ITEMWeaponNumGemSlots
            {DataObject(0x1C51D, 1, UINT_T), 6}, // ITEMWeaponStatic6 (6)
			{DataObject(0x1C51E, 2, UINT_T), 0}  // ITEMWeaponStatic7 (0)
		}),
		new ArrayObject(16, 300, std::vector<Element> { // ITEMGemArray
			{DataObject(0x206D8, 2, UINT_T), 0xEA33}, // ITEMGemStatic1 (0xEA33); Item ID from ITM_itemlist that doesn't affect gem attributes (just needs to be a gem type item)
			{DataObject(0x206DA, 7, 11, UINT_T), 0}, // ITEMGemID1
			{DataObject(0x206DB, 4, 5, UINT_T), 0}, // ITEMGemUnk1
			{DataObject(0x206DC, 1, UINT_T), 0}, // ITEMGemStatic2 (0)
			{DataObject(0x206DD, 1, UINT_T), 0}, // ITEMGemInventorySlot
			{DataObject(0x206DE, 1, UINT_T), 1},// ITEMGemStatic3 (1)
			{DataObject(0x206DF, 1, UINT_T), 0}, // ITEMGemStatic4 (0/3)
			{DataObject(0x206E0, 7, 11, UINT_T), 0}, // ITEMGemUnk2
			{DataObject(0x206E1, 4, 11, UINT_T), 0}, // ITEMGemValue
			{DataObject(0x206E2, 1, 3, UINT_T), 0}, // ITEMGemRank
			{DataObject(0x206E3, 6, 7, UINT_T), 0}, // ITEMGemUnk3
			{DataObject(0x206E4, 7, 12, UINT_T), 0},// ITEMGemID2
            {DataObject(0x206E5, 3, 4, UINT_T), 2}, // ITEMGemStatic5 (2)
			{DataObject(0x206E6, 2, UINT_T), 0}// ITEMGemStatic6 (0)
		}),

		// WTHR
        new DataObject(0x24090, 4, FLOAT_T), // WTHRReroll*
        new DataObject(0x24098, 4, UINT_T), // WTHRMap*
        new DataObject(0x24095, 1, UINT_T), // WTHRForegroundWeather*
        new DataObject(0x24096, 2, UINT_T), // WTHRUnk1*
        new DataObject(0x2409D, 1, UINT_T), // WTHRBackgroundWeather*
        new DataObject(0x2409F, 1, UINT_T), // WTHRUnk2*

		// SNDS

		// MINE
		new ArrayObject(6, 150, std::vector<Element> { // MINEArray
			{DataObject(0x240F0, 2, UINT_T), 0}, // MINECooldown
			{DataObject(0x240F2, 1, UINT_T), 0}, // MINENumHarvests
			{DataObject(0x240F3, 1, UINT_T), 0}, // MINEMineID
			{DataObject(0x240F4, 2, UINT_T), 0}// MINEMapID
		}),

		// TBOX
		new DataObject(0x244A3, 1, UINT_T), // TBOXBoxCount
		new ArrayObject(28, 21, std::vector<Element> { // TBOXArray
			{DataObject(0x244A4, 4, UINT_T), 0}, // TBOXZeroObject
			{DataObject(0x244A8, 4, FLOAT_T), 0}, // TBOXPositionX
			{DataObject(0x244AC, 4, FLOAT_T), 0}, // TBOXPositionY
			{DataObject(0x244B0, 4, FLOAT_T), 0},// TBOXPositionZ
			{DataObject(0x244B4, 4, FLOAT_T), 0}, // TBOXAngle
			{DataObject(0x244B8, 4, UINT_T), 0}, // TBOXRank
			{DataObject(0x244BC, 2, UINT_T), 0},// TBOXDropTable (?)
			{DataObject(0x244BE, 2, UINT_T), 0} // TBOXMapID
		}),

		// OPTD
        new DataObject(0x248B0, 1, BOOL_T), // OPTDNonInvertedYAxis*
        new DataObject(0x248B1, 1, BOOL_T), // OPTDNonInvertedXAxis*
        new DataObject(0x248B2, 1, UINT_T), // OPTDYAxisSpeed*
        new DataObject(0x248B3, 1, UINT_T), // OPTDXAxisSpeed*
        new DataObject(0x248B4, 1, UINT_T), // OPTDZoomSpeed*
        new DataObject(0x248B5, 1, UINT_T), // OPTDPointOfView*
        new DataObject(0x248B6, 1, BOOL_T), // OPTDAngleCorrection*
        new DataObject(0x248B7, 1, BOOL_T), // OPTDBattleCamera*
        new DataObject(0x248BF, 1, UINT_T), // OPTDGamma*
        new DataObject(0x248C0, 1, BOOL_T), // OPTDMinimapOn*
        new DataObject(0x248C1, 1, BOOL_T), // OPTDMinimapRotate*
        new DataObject(0x248CC, 1, BOOL_T), // OPTDJapaneseVoice*
        new DataObject(0x248D0, 1, BOOL_T), // OPTDShowControls*
        new DataObject(0x248D1, 1, BOOL_T), // OPTDShowArtDescriptions*
        new DataObject(0x248D2, 1, BOOL_T), // OPTDShowBuffDebuffInfoEveryTime*
        new DataObject(0x248D3, 1, BOOL_T), // OPTDShowEnemyIcons*
        new DataObject(0x248D4, 1, BOOL_T), // OPTDShowBuffDefbuffIndicator*
        new DataObject(0x248D5, 1, BOOL_T), // OPTDShowDestinationMarker*
        new DataObject(0x248E0, 1, BOOL_T), // OPTDAutoEventScrolling*
        new DataObject(0x248E1, 1, BOOL_T), // OPTDFastDialogueText*
        new DataObject(0x248E2, 1, BOOL_T)  // OPTDShowSubtitles*
	};

public:
	SaveFile();
    SaveFile(std::string fileLocation);

    uint8_t getByteAt(unsigned int x);

    std::vector<uint8_t> getRawBytes(DataObject data);
    std::vector<uint8_t> getRawBytes(SaveFieldID sfID);
    std::vector<uint8_t> getRawArrayBytes(SaveFieldID sfID, unsigned int index, unsigned int elementName);

    void setByteAt(unsigned int x, uint8_t b);

    void saveToFile();
    void saveToFile(std::string file);

    Type getType(SaveFieldID sfID);

    std::string getFileName() { return this->fileLocation; }
    
    template<typename T>
    T getValue(SaveFieldID sfID)
    {
        return Types::toValue<T>(this->getRawBytes(sfID));
    }

    template<typename T>
    T getArrayValue(SaveFieldID aID, unsigned int index, unsigned int elementName)
    {
        const DataObject* dataObj = (*dataMap[aID]).at(index, elementName);
        if (dataObj == NULL) throw std::out_of_range("Array out of bounds for SaveFieldID " + std::to_string(aID) + " at (row = " + std::to_string(index) + ", column = " + std::to_string(elementName) + ")");

        return Types::toValue<T>(this->getRawBytes(*dataObj));
    }

    template<typename T> bool setValue(SaveFieldID sfID, T value)
    {
        return (*dataMap[sfID]).setValue(this->saveFile, value);
    }

    template<typename T> void setArrayValue(SaveFieldID aID, unsigned int index, unsigned int elementName, T value)
    {
        const DataObject* arrayObj = (dataMap[aID])->at(index, elementName);
        if (arrayObj != NULL) (arrayObj)->setValue(this->saveFile, value);
        else throw std::out_of_range("Array out of bounds for SaveFieldID " + std::to_string(aID) + " at (row = " + std::to_string(index) + ", column = " + std::to_string(elementName) + ")");
    }

    void setArrayIndexNull(bool isNull, SaveFieldID aID, unsigned int index);
};
