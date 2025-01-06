#pragma once

enum ITEMWeaponArray
{
    ITEMWeapon_ID1,
    ITEMWeapon_Static1, // 2
    ITEMWeapon_ID2,
    ITEMWeapon_Static2, // 0
    ITEMWeapon_Static3, // 0
    ITEMWeapon_InventorySlot,
    ITEMWeapon_Static4, // 1
    ITEMWeapon_Static5, // 0

    ITEMWeapon_Gem1Unk1,
    ITEMWeapon_Gem1Value,
    ITEMWeapon_Gem1Rank,
    ITEMWeapon_Gem1Unk2,
    ITEMWeapon_Gem1ID2,
    ITEMWeapon_Gem1Static1, // 2
    ITEMWeapon_Gem1Static2, // 0

    ITEMWeapon_Gem2Unk1,
    ITEMWeapon_Gem2Value,
    ITEMWeapon_Gem2Rank,
    ITEMWeapon_Gem2Unk2,
    ITEMWeapon_Gem2ID2,
    ITEMWeapon_Gem2Static1, // 2
    ITEMWeapon_Gem2Static2, // 0

    ITEMWeapon_Gem3Unk1,
    ITEMWeapon_Gem3Value,
    ITEMWeapon_Gem3Rank,
    ITEMWeapon_Gem3Unk2,
    ITEMWeapon_Gem3ID2,
    ITEMWeapon_Gem3Static1, // 2
    ITEMWeapon_Gem3Static2, // 0

    ITEMWeapon_Gem4Unk1,
    ITEMWeapon_Gem4Value,
    ITEMWeapon_Gem4Rank,
    ITEMWeapon_Gem4Unk2,
    ITEMWeapon_Gem4ID2,
    ITEMWeapon_Gem4Static1, // 2
    ITEMWeapon_Gem4Static2, // 0

    ITEMWeapon_Gem1Index,
    ITEMWeapon_Gem2Index,
    ITEMWeapon_Gem3Index,
    ITEMWeapon_Gem4Index,
    ITEMWeapon_NumGemSlots,
    ITEMWeapon_Static6, // 6
    ITEMWeapon_Static7 // 0
};

enum ITEMGemArray
{
    ITEMGem_Static1, // 0xEA33
    ITEMGem_ID1,
    ITEMGem_Unk1,
    ITEMGem_Static2, // 0
    ITEMGem_InventorySlot,
    ITEMGem_Static3, // 1
    ITEMGem_Static4, // 0/3
    ITEMGem_Unk2,
    ITEMGem_Value,
    ITEMGem_Rank,
    ITEMGem_Unk3,
    ITEMGem_ID2,
    ITEMGem_Static5, // 2
    ITEMGem_Static6 // 0
};

enum MINEArray
{
    MINE_Cooldown,
    MINE_NumHarvests,
    MINE_MineID,
    MINE_MapID,
};

enum TBOXArray
{
    TBOX_ZeroObject,
    TBOX_PositionX,
    TBOX_PositionY,
    TBOX_PositionZ,
    TBOX_Angle,
    TBOX_Rank,
    TBOX_DropTable,
    TBOX_MapID
};
