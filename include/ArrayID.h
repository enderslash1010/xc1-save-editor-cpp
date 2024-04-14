#pragma once

enum ITEMWeaponArray
{
	ITEMWeaponID1,
	ITEMWeaponStatic1, // 2
	ITEMWeaponID2,
	ITEMWeaponStatic2, // 0
	ITEMWeaponStatic3, // 0
	ITEMWeaponInventorySlot,
	ITEMWeaponStatic4, // 1
	ITEMWeaponStatic5, // 0
	ITEMWeaponGem1ID,
	ITEMWeaponGem2ID,
	ITEMWeaponGem3ID,
	ITEMWeaponGem4ID,
	ITEMWeaponGem1Index,
	ITEMWeaponGem2Index,
	ITEMWeaponGem3Index,
	ITEMWeaponGem4Index,
	ITEMWeaponNumGemSlots,
	ITEMWeaponStatic6, // 6
	ITEMWeaponStatic7 // 0
};

enum ITEMGemArray
{
	ITEMGemStatic1, // 0xEA33
	ITEMGemID1,
	ITEMGemUnk1,
	ITEMGemStatic2, // 0
	ITEMGemInventorySlot,
	ITEMGemStatic3, // 1
	ITEMGemStatic4, // 0/3
	ITEMGemUnk2,
	ITEMGemValue,
	ITEMGemRank,
	ITEMGemUnk3,
	ITEMGemID2,
	ITEMGemStatic5, // 2
	ITEMGemStatic6 // 0
};

enum MINEArray
{
	MINECooldown,
	MINENumHarvests,
	MINEMineID,
	MINEMapID,
};

enum TBOXElementID
{
	TBOXZeroObject,
	TBOXPositionX,
	TBOXPositionY,
	TBOXPositionZ,
	TBOXAngle,
	TBOXRank,
	TBOXDropTable,
	TBOXMapID
};
