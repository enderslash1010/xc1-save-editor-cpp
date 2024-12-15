#pragma once

// Maps to Data Objects in SaveFile's dataMap
enum SaveFieldID
{
	// THUM
	THUMLevel,
	THUMPlayTimeHours,
	THUMPlayTimeMinutes,
	THUMPlayTimeSeconds,
	THUMSaveTimeDay,
	THUMSaveTimeMonth,
	THUMSaveTimeYear,
	THUMSaveTimeHour,
	THUMSaveTimeMinute,
	THUMPictureSlot1,
	THUMPictureSlot2,
	THUMPictureSlot3,
	THUMPictureSlot4,
	THUMPictureSlot5,
	THUMPictureSlot6,
	THUMPictureSlot7,
	THUMNameString,
	THUMSystemSaveFlag,
	THUMNGPlusFlag,
	THUMSaveImage,

	// FLAG
	FLAGScenarioID,

	// GAME
	GAMEMapNum,
	GAMEMapNumString,
    GAMEMapNum2,
    GAMEMapNumString2,
	GAMEPlayer1,
	GAMEPlayer2,
	GAMEPlayer3,
	GAMEPlayer4,
	GAMEPlayer5,
	GAMEPlayer6,
	GAMEPlayer7,
	GAMEShulkLevel,
	GAMEReynLevel,
	GAMEFioraLevel,
	GAMEDunbanLevel,
	GAMESharlaLevel,
	GAMERikiLevel,
	GAMEMeliaLevel,
	GAMESevenLevel,
	GAMEDicksonLevel,
	GAMEMumkharLevel,
	GAMEAlvisLevel,
	GAMEPrologueDunbanLevel,

	// TIME
	TIMEPlayTime,
	TIMEDayCount,
	TIMEDayTime,
	TIMEYearCount,

    // PCPM - Player Character Position Metadata
	PCPMPlayer1X,
	PCPMPlayer1Y,
	PCPMPlayer1Z,
	PCPMPlayer1Angle,
	PCPMPlayer2X,
	PCPMPlayer2Y,
	PCPMPlayer2Z,
	PCPMPlayer2Angle,
	PCPMPlayer3X,
	PCPMPlayer3Y,
	PCPMPlayer3Z,
	PCPMPlayer3Angle,

	// CAMD
	CAMDVerticalPosition,
	CAMDHorizontalPosition,
	CAMDDistance,

	// ITEM
	ITEMMoney,
	ITEMWeaponArray,
	ITEMGemArray,

	// WTHR
	WTHRReroll,
	WTHRMap,
    WTHRForegroundWeather,
	WTHRUnk1,
	WTHRBackgroundWeather,
	WTHRUnk2,

	// SNDS

	// MINE
	MINEArray,

	// TBOX
	TBOXBoxCount,
	TBOXArray,
	
	// OPTD
	OPTDNonInvertedYAxis,
	OPTDNonInvertedXAxis,
	OPTDYAxisSpeed,
	OPTDXAxisSpeed,
	OPTDZoomSpeed,
	OPTDPointOfView,
	OPTDAngleCorrection,
	OPTDBattleCamera,
	OPTDGamma,
	OPTDMinimapOn,
	OPTDMinimapRotate,
	OPTDJapaneseVoice,
	OPTDShowControls,
	OPTDShowArtDescriptions,
	OPTDShowBuffDebuffInfoEveryTime,
	OPTDShowEnemyIcons,
	OPTDShowBuffDefbuffIndicator,
	OPTDShowDestinationMarker,
	OPTDAutoEventScrolling,
	OPTDFastDialogueText,
	OPTDShowSubtitles,

	LAST_INDEX
};
