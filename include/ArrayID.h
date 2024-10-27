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
    ITEMWeapon_Gem1ID,
    ITEMWeapon_Gem2ID,
    ITEMWeapon_Gem3ID,
    ITEMWeapon_Gem4ID,
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
