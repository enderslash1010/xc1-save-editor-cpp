#include <gtest/gtest.h>
#include "ArrayID.h"
#include "SaveFile.h"

#define TEST_POINTS 5

template<typename T>
static bool compareBytes(T a, T b)
{
	uint8_t valA[sizeof(T)], valB[sizeof(T)];
	memcpy(&valA, &a, sizeof(T));
	memcpy(&valB, &b, sizeof(T));

	bool result = true;
	for (int i = 0; i < sizeof(T); i++)
	{
		if (valA[i] != valB[i])
		{
			result = false;
			break;
		}
	}
	return result;
}

TEST(Save, floats)
{
	SaveFile* saveFile = new SaveFile();

	// Setting and reading as float
    float floatTestValues[TEST_POINTS] = { 1.222f, 52792035.67f, -12345.6789, 0.25789f, 0.0f };
	for (int i = 0; i < TEST_POINTS; i++)
	{
		saveFile->setValue(PCPMPlayer1Z, floatTestValues[i]);
		EXPECT_EQ(floatTestValues[i], saveFile->getValue<float>(PCPMPlayer1Z));
	}

	// Setting as uinteger, reading as float
	unsigned int uintTestValues[TEST_POINTS] = { 0x1, 0x4640E47E, 0xFFFFFFFF, 0x4A8b3A74, 0x80000001 };
	float testValue = 0;
	for (int i = 0; i < TEST_POINTS; i++)
	{
		memcpy(&testValue, &uintTestValues[i], sizeof(float));
		saveFile->setValue(CAMDDistance, uintTestValues[i]);
		EXPECT_TRUE(compareBytes(testValue, saveFile->getValue<float>(CAMDDistance)));
	}

	// Setting as sinteger, reading as float
	signed int sintTestValues[TEST_POINTS] = { -1, 13489, 32767, -393, 0 };
	for (int i = 0; i < TEST_POINTS; i++)
	{
		memcpy(&testValue, &sintTestValues[i], sizeof(float));
        saveFile->setArrayValue(TBOXArray, 6, TBOX_PositionZ, sintTestValues[i]);
        EXPECT_TRUE(compareBytes(testValue, saveFile->getArrayValue<float>(TBOXArray, 6, TBOX_PositionZ)));
	}

	// Setting as boolean, reading as float
	uint32_t boolTestValues[2] = { 0x0, 0x1 };

	memcpy(&testValue, &boolTestValues[0], sizeof(uint32_t));
	saveFile->setValue(PCPMPlayer3Y, false);
    EXPECT_TRUE(compareBytes(testValue, saveFile->getValue<float>(PCPMPlayer3Y)));

	memcpy(&testValue, &boolTestValues[1], sizeof(uint32_t));
	saveFile->setValue(PCPMPlayer3Z, true);
    EXPECT_TRUE(compareBytes(testValue, saveFile->getValue<float>(PCPMPlayer3Z)));

	// Setting as string, reading as float
    const char stringTestValues[TEST_POINTS][5] = { {'h', 'i', 'i', 'i', 0}, {':', '3', ':', '3', 0}, {'1', '2', '3', '4', 0}, {'0', '0', '0', '0', 0}, {'.', '/', '?', ';', 0}};
    uint32_t stringIntTestValues[TEST_POINTS] = { 0x68696969, 0x3A333A33, 0x31323334, 0x30303030, 0x2E2F3F3B };

	for (int i = 0; i < TEST_POINTS; i++)
	{
		memcpy(&testValue, &stringIntTestValues[i], sizeof(float));
		saveFile->setValue(CAMDVerticalPosition, stringTestValues[i]);
        EXPECT_TRUE(compareBytes(testValue, saveFile->getValue<float>(CAMDVerticalPosition)));
	}

	delete(saveFile);
}

TEST(Save, uintegers)
{
	SaveFile* saveFile = new SaveFile();

	// Setting and reading as uint
    unsigned int uintTestValues[TEST_POINTS] = { 0x8765, 52501, 0, 3, 61286 };
	for (int i = 0; i < TEST_POINTS; i++)
	{
		saveFile->setValue(TIMEDayCount, uintTestValues[i]);
		EXPECT_EQ(uintTestValues[i], saveFile->getValue<unsigned int>(TIMEDayCount));
	}

	// Setting as float, reading as uint
	float floatTestValues[TEST_POINTS] = { 1.12f, 339.3392, -0.1, 452.256, 239.9231 };
	unsigned int uintTestValues2[TEST_POINTS] = { 0x3F8F5C29, 0x43A9AB6B, 0xBDCCCCCD, 0x43E220C5, 0x436FEC50 };
	for (int i = 0; i < TEST_POINTS; i++)
	{
		saveFile->setValue(GAMESevenLevel, floatTestValues[i]);
		EXPECT_EQ(uintTestValues2[i], saveFile->getValue<unsigned int>(GAMESevenLevel));
	}

	// Setting as sint, reading as uint
	int16_t sintTestValues[TEST_POINTS] = { -1, 255, -32, 0, 2 };
	for (int i = 0; i < TEST_POINTS; i++)
	{
		saveFile->setValue(GAMEPlayer4, sintTestValues[i]);
		EXPECT_EQ((uint16_t)sintTestValues[i], saveFile->getValue<unsigned int>(GAMEPlayer4));
	}

	// Setting as boolean, reading as uint
	saveFile->setValue(GAMERikiLevel, true);
	EXPECT_EQ(0x1, saveFile->getValue<unsigned int>(GAMERikiLevel));

	saveFile->setValue(GAMERikiLevel, false);
	EXPECT_EQ(0x0, saveFile->getValue<unsigned int>(GAMERikiLevel));

	// Setting as string, reading as uint
	std::string stringTestValues[4] = { "free", "beef", "0000", "1234" };
	unsigned int uintTestValues3[4] = { 0x66726565, 0x62656566, 0x30303030, 0x31323334 };
	for (int i = 0; i < 4; i++)
	{
		saveFile->setValue(TIMEDayTime, stringTestValues[i]);
		EXPECT_EQ(uintTestValues3[i], saveFile->getValue<unsigned int>(TIMEDayTime));
	}

	delete(saveFile);
}

TEST(Save, sintegers)
{
	SaveFile* saveFile = new SaveFile();

	// Setting and reading as sint
	signed int sintTestValues[TEST_POINTS] = { -1, 32676, -123, 0, 4578 };
	for (int i = 0; i < TEST_POINTS; i++)
	{
		saveFile->setValue(ITEMMoney, sintTestValues[i]);
		EXPECT_EQ(sintTestValues[i], saveFile->getValue<signed int>(ITEMMoney));
	}

	// Setting as uint, reading as sint
	unsigned int uintTestValues[TEST_POINTS] = { 0xFFFFFFFF, 0, 13478, 41378932, 341789 };
	signed int expectedValue = 0;
	for (int i = 0; i < TEST_POINTS; i++)
	{
		memcpy(&expectedValue, &uintTestValues[i], sizeof(signed int));
		saveFile->setValue(PCPMPlayer1Angle, uintTestValues[i]);
		EXPECT_EQ(expectedValue, saveFile->getValue<signed int>(PCPMPlayer1Angle));
	}

	// Setting as float, reading as sint
	float floatTestValues[TEST_POINTS] = { 0.0f, -235897.2347f, 2222.223f, -1.1f };
	for (int i = 0; i < TEST_POINTS; i++)
	{
		memcpy(&expectedValue, &floatTestValues[i], sizeof(signed int));
		saveFile->setValue(GAMEMapNumString, floatTestValues[i]);
		EXPECT_EQ(expectedValue, saveFile->getValue<signed int>(GAMEMapNumString));
	}

	// Setting as boolean, reading as sint
	saveFile->setValue(WTHRReroll, true);
	EXPECT_EQ((signed int)0x1, saveFile->getValue<signed int>(WTHRReroll));

	saveFile->setValue(WTHRReroll, false);
	EXPECT_EQ((signed int)0x0, saveFile->getValue<signed int>(WTHRReroll));

	// Setting as string, reading as sint
	std::string stringTestValues[4] = { "free", "beef", "0000", "1234" };
	signed int sintTestValues3[4] = { 0x66726565, 0x62656566, 0x30303030, 0x31323334 };
	for (int i = 0; i < 4; i++)
	{
		saveFile->setValue(TIMEDayTime, stringTestValues[i]);
		EXPECT_EQ(sintTestValues3[i], saveFile->getValue<unsigned int>(TIMEDayTime));
	}

	delete(saveFile);
}

TEST(Save, booleans)
{
	SaveFile* saveFile = new SaveFile();

	// Setting as boolean, reading as boolean
	saveFile->setValue(THUMSaveTimeDay, true);
	EXPECT_EQ(true, saveFile->getValue<bool>(THUMSaveTimeDay));

	saveFile->setValue(THUMSaveTimeDay, false);
	EXPECT_EQ(false, saveFile->getValue<bool>(THUMSaveTimeDay));

	// Setting as uint, reading as boolean
	unsigned int uintTestValues[TEST_POINTS] = { 0, 1, 3, 4, 5 };
	bool expectedValue = 0;
	for (int i = 0; i < TEST_POINTS; i++)
	{
		expectedValue = uintTestValues[i];
		saveFile->setValue(THUMSaveTimeYear, uintTestValues[i]);
		EXPECT_EQ(expectedValue, saveFile->getValue<bool>(THUMSaveTimeYear));
	}

	// Setting as sint, reading as boolean
	signed int sintTestValues[TEST_POINTS] = { -2, -1, 0, 1, 2 };
	for (int i = 0; i < TEST_POINTS; i++)
	{
		expectedValue = sintTestValues[i];
		saveFile->setValue(WTHRBackgroundWeather, sintTestValues[i]);
		EXPECT_EQ(expectedValue, saveFile->getValue<bool>(WTHRBackgroundWeather));
	}

	// Setting as float, reading as boolean
	float floatTestValues[TEST_POINTS] = { 0.0f, 1.1f, -48139.342f, -1.1f, 13578923.13589f };
	for (int i = 0; i < TEST_POINTS; i++)
	{
		expectedValue = floatTestValues[i];
		saveFile->setValue(GAMEAlvisLevel, floatTestValues[i]);
		EXPECT_EQ(expectedValue, saveFile->getValue<bool>(GAMEAlvisLevel));
	}

	// Setting as string, reading as boolean
	std::string stringTestValues[TEST_POINTS] = { "", "hello world!", "0", "123", "string" };
	bool expectedValues[] = { false, true, true, true, true };
	for (int i = 0; i < TEST_POINTS; i++)
	{
		saveFile->setValue(GAMEAlvisLevel, floatTestValues[i]);
		EXPECT_EQ(expectedValues[i], saveFile->getValue<bool>(GAMEAlvisLevel));
	}

	delete(saveFile);
}

TEST(Save, strings)
{
	SaveFile* saveFile = new SaveFile();

	// Setting as string, reading as string
	std::string stringTestValues[TEST_POINTS] = { "", "hello, world!", "          ", "adhsiufghdasiufbgas", "shulk :3" };
	for (int i = 0; i < TEST_POINTS; i++)
	{
		saveFile->setValue(THUMNameString, stringTestValues[i]);
		std::string temp = saveFile->getValue<std::string>(THUMNameString);
		for (int a = 0, b = 0;; a++, b++)
		{
			if (stringTestValues[i][a] == 0 && temp[b] == 0) break;
			else if (stringTestValues[i][a] == 0 || temp[b] == 0) FAIL();

			if (stringTestValues[i][a] != temp[b]) FAIL();
		}
	}

	// Setting as uint, reading as string
	unsigned int uintTestValues[TEST_POINTS] = { 0x0, 0x7E7E7E7E, 0x23456779, 46, 12345 };
	std::string expectedValues[TEST_POINTS] = { "", "~~~~", "#Egy", ".", "09"};
	for (int i = 0; i < TEST_POINTS; i++)
	{
		saveFile->setValue(THUMNameString, uintTestValues[i]);
		std::string result = saveFile->getValue<std::string>(THUMNameString);
		for (int a = 0, b = 0;; a++, b++)
		{
			if (expectedValues[i][a] == 0 && result[b] == 0) break;
			else if (expectedValues[i][a] == 0 || result[b] == 0) FAIL();

			if (expectedValues[i][a] != result[b]) FAIL();
		}
	}

	delete(saveFile);
}

TEST(Save, arrays)
{
	SaveFile* saveFile = new SaveFile();

    // Set index to not null to load static values
    saveFile->setArrayIndexNull(false, ITEMWeaponArray, 6);

    // Set all array values in an element
    saveFile->setArrayValue(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_ID1, 2);
    saveFile->setArrayValue(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_ID2, 12);
    saveFile->setArrayValue(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_InventorySlot, 0xFF);
    saveFile->setArrayValue(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem1ID, -1);
    saveFile->setArrayValue(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem2ID, -2);
    saveFile->setArrayValue(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem3ID, -3);
    saveFile->setArrayValue(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem4ID, -4);
    saveFile->setArrayValue(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem1Index, true);
    saveFile->setArrayValue(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem2Index, false);
    saveFile->setArrayValue(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem3Index, 0x22);
    saveFile->setArrayValue(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem4Index, 0x24);
    saveFile->setArrayValue(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_NumGemSlots, 0x14);

    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_ID1) != 2) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static1) != 2) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_ID2) != 12) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static2) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static3) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_InventorySlot) != 0xFF) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static4) != 1) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static5) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem1ID) != -1) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem2ID) != -2) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem3ID) != -3) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem4ID) != -4) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem1Index) != 1) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem2Index) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem3Index) != 0x22) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem4Index) != 0x24) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_NumGemSlots) != 0x14) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static6) != 6) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static7) != 0) FAIL();

    // Set element to null
    saveFile->setArrayIndexNull(true, ITEMWeaponArray, 6);

    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_ID1) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static1) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_ID2) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static2) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static3) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_InventorySlot) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static4) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static5) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem1ID) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem2ID) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem3ID) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem4ID) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem1Index) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem2Index) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem3Index) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem4Index) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_NumGemSlots) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static6) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static7) != 0) FAIL();

    // Set element to not null
    saveFile->setArrayIndexNull(false, ITEMWeaponArray, 6);

    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_ID1) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static1) != 2) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_ID2) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static2) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static3) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_InventorySlot) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static4) != 1) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static5) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem1ID) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem2ID) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem3ID) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem4ID) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem1Index) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem2Index) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem3Index) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Gem4Index) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_NumGemSlots) != 0) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static6) != 6) FAIL();
    if (saveFile->getArrayValue<unsigned int>(ITEMWeaponArray, 6, ITEMWeaponArray::ITEMWeapon_Static7) != 0) FAIL();

    delete(saveFile);
}
