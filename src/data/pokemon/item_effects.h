const u8 gItemEffect_Potion[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
    [6] = 20, // Amount of HP to recover
};

const u8 gItemEffect_Antidote[ITEM_EFFECT_COUNT] = {
    [3] = ITEM3_POISON,
};

const u8 gItemEffect_BurnHeal[ITEM_EFFECT_COUNT] = {
    [3] = ITEM3_BURN,
};

const u8 gItemEffect_IceHeal[ITEM_EFFECT_COUNT] = {
    [3] = ITEM3_FREEZE,
};

const u8 gItemEffect_Awakening[ITEM_EFFECT_COUNT] = {
    [3] = ITEM3_SLEEP,
};

const u8 gItemEffect_ParalyzeHeal[ITEM_EFFECT_COUNT] = {
    [3] = ITEM3_PARALYSIS,
};

const u8 gItemEffect_FullRestore[ITEM_EFFECT_COUNT] = {
    [3] = ITEM3_STATUS_ALL,
    [4] = ITEM4_HEAL_HP,
    [6] = ITEM6_HEAL_HP_FULL,
};

const u8 gItemEffect_MaxPotion[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
    [6] = ITEM6_HEAL_HP_FULL,
};

const u8 gItemEffect_HyperPotion[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
    [6] = I_HEALTH_RECOVERY >= GEN_7 ? 120 : 200, // Amount of HP to recover
};

const u8 gItemEffect_SuperPotion[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
    [6] = I_HEALTH_RECOVERY >= GEN_7 ? 60 : 50, // Amount of HP to recover
};

const u8 gItemEffect_FullHeal[ITEM_EFFECT_COUNT] = {
    [3] = ITEM3_STATUS_ALL,
};

const u8 gItemEffect_Revive[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_REVIVE | ITEM4_HEAL_HP,
    [6] = ITEM6_HEAL_HP_HALF,
};

const u8 gItemEffect_MaxRevive[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_REVIVE | ITEM4_HEAL_HP,
    [6] = ITEM6_HEAL_HP_FULL,
};

const u8 gItemEffect_FreshWater[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
    [6] = I_HEALTH_RECOVERY >= GEN_7 ? 30 : 50, // Amount of HP to recover
};

const u8 gItemEffect_SodaPop[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
    [6] = I_HEALTH_RECOVERY >= GEN_7 ? 50 : 60, // Amount of HP to recover
};

const u8 gItemEffect_Lemonade[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
    [6] = I_HEALTH_RECOVERY >= GEN_7 ? 70 : 80, // Amount of HP to recover
};

const u8 gItemEffect_MoomooMilk[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
    [6] = 100, // Amount of HP to recover
};

const u8 gItemEffect_EnergyPowder[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
    [5] = ITEM5_FRIENDSHIP_ALL,
    [6] = I_HEALTH_RECOVERY >= GEN_7 ? 60 : 50, // Amount of HP to recover
    [7] = -5, // Friendship change, low
    [8] = -5, // Friendship change, mid
    [9] = -10, // Friendship change, high
};

const u8 gItemEffect_EnergyRoot[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
    [5] = ITEM5_FRIENDSHIP_ALL,
    [6] = I_HEALTH_RECOVERY >= GEN_7 ? 120 : 200, // Amount of HP to recover
    [7] = -10, // Friendship change, low
    [8] = -10, // Friendship change, mid
    [9] = -15, // Friendship change, high
};

const u8 gItemEffect_HealPowder[ITEM_EFFECT_COUNT] = {
    [3] = ITEM3_STATUS_ALL,
    [5] = ITEM5_FRIENDSHIP_ALL,
    [6] = -5,  // Friendship change, low
    [7] = -5,  // Friendship change, mid
    [8] = -10, // Friendship change, high
};

const u8 gItemEffect_RevivalHerb[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_REVIVE | ITEM4_HEAL_HP,
    [5] = ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_HEAL_HP_FULL,
    [7] = -15, // Friendship change, low
    [8] = -15, // Friendship change, mid
    [9] = -20, // Friendship change, high
};

const u8 gItemEffect_Remedy[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
    [5] = ITEM5_FRIENDSHIP_ALL,
    [6] = 20, // Amount of HP to recover
    [7] = -5, // Friendship change, low
    [8] = -5, // Friendship change, mid
    [9] = -10, // Friendship change, high
};

const u8 gItemEffect_FineRemedy[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
    [5] = ITEM5_FRIENDSHIP_ALL,
    [6] = I_HEALTH_RECOVERY >= GEN_7 ? 60 : 50, // Amount of HP to recover
    [7] = -10, // Friendship change, low
    [8] = -10, // Friendship change, mid
    [9] = -15, // Friendship change, high
};

const u8 gItemEffect_SuperbRemedy[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
    [5] = ITEM5_FRIENDSHIP_ALL,
    [6] = I_HEALTH_RECOVERY >= GEN_7 ? 120 : 200, // Amount of HP to recover
    [7] = -15, // Friendship change, low
    [8] = -15, // Friendship change, mid
    [9] = -20, // Friendship change, high
};

const u8 gItemEffect_Ether[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_PP_ONE | ITEM4_HEAL_PP,
    [6] = 10,
};

const u8 gItemEffect_MaxEther[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_PP_ONE | ITEM4_HEAL_PP,
    [6] = ITEM6_HEAL_PP_FULL,
};

const u8 gItemEffect_Elixir[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_PP,
    [6] = 10, // Amount of PP to recover
};

const u8 gItemEffect_MaxElixir[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_PP,
    [6] = ITEM6_HEAL_PP_FULL,
};

const u8 gItemEffect_YellowFlute[ITEM_EFFECT_COUNT] = {
    [3] = ITEM3_CONFUSION,
};

const u8 gItemEffect_RedFlute[ITEM_EFFECT_COUNT] = {
    [0] = ITEM0_INFATUATION,
};

const u8 gItemEffect_SacredAsh[ITEM_EFFECT_COUNT] = {
    [0] = ITEM0_SACRED_ASH,
    [4] = ITEM4_REVIVE | ITEM4_HEAL_HP,
    [6] = ITEM6_HEAL_HP_FULL,
};

#define VITAMIN_FRIENDSHIP_CHANGE(i)             \
    [(i) + 0] = 5, /* Friendship change, low */  \
    [(i) + 1] = 3, /* Friendship change, mid */  \
    [(i) + 2] = 2  /* Friendship change, high */

const u8 gItemEffect_HPUp[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_EV_HP,
    [5] = ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_ADD_EV,
    VITAMIN_FRIENDSHIP_CHANGE(7),
    [10] = ITEM10_IS_VITAMIN,
};

const u8 gItemEffect_HPUpEX[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_EV_HP,
    [5] = ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_MAX_EV,
};

const u8 gItemEffect_Protein[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_EV_ATK,
    [5] = ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_ADD_EV,
    VITAMIN_FRIENDSHIP_CHANGE(7),
    [10] = ITEM10_IS_VITAMIN,
};

const u8 gItemEffect_ProteinEX[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_EV_ATK,
    [5] = ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_MAX_EV,
};

const u8 gItemEffect_Iron[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_DEF | ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_ADD_EV,
    VITAMIN_FRIENDSHIP_CHANGE(7),
    [10] = ITEM10_IS_VITAMIN,
};

const u8 gItemEffect_IronEX[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_DEF | ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_MAX_EV,
};

const u8 gItemEffect_Carbos[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_SPEED | ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_ADD_EV,
    VITAMIN_FRIENDSHIP_CHANGE(7),
    [10] = ITEM10_IS_VITAMIN,
};

const u8 gItemEffect_CarbosEX[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_SPEED | ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_MAX_EV,
};

const u8 gItemEffect_Calcium[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_SPATK | ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_ADD_EV,
    VITAMIN_FRIENDSHIP_CHANGE(7),
    [10] = ITEM10_IS_VITAMIN,
};

const u8 gItemEffect_CalciumEX[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_SPATK | ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_MAX_EV,
};

const u8 gItemEffect_Zinc[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_SPDEF | ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_ADD_EV,
    VITAMIN_FRIENDSHIP_CHANGE(7),
    [10] = ITEM10_IS_VITAMIN,
};

const u8 gItemEffect_ZincEX[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_SPDEF | ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_MAX_EV,
};

const u8 gItemEffect_ReduceHpIV[ITEM_EFFECT_COUNT] = {
    [9] = ITEM9_REDUCE_IV_HP,
    [10] = ITEM10_REDUCE_IV,
};

const u8 gItemEffect_ReduceAtkIV[ITEM_EFFECT_COUNT] = {
    [9] = ITEM9_REDUCE_IV_ATK,
    [10] = ITEM10_REDUCE_IV,
};

const u8 gItemEffect_ReduceDefIV[ITEM_EFFECT_COUNT] = {
    [9] = ITEM9_REDUCE_IV_DEF,
    [10] = ITEM10_REDUCE_IV,
};

const u8 gItemEffect_ReduceSpeedIV[ITEM_EFFECT_COUNT] = {
    [9] = ITEM9_REDUCE_IV_SPEED,
    [10] = ITEM10_REDUCE_IV,
};

const u8 gItemEffect_ReduceSpAtkIV[ITEM_EFFECT_COUNT] = {
    [9] = ITEM9_REDUCE_IV_SPATK,
    [10] = ITEM10_REDUCE_IV,
};

const u8 gItemEffect_ReduceSpDefIV[ITEM_EFFECT_COUNT] = {
    [9] = ITEM9_REDUCE_IV_SPDEF,
    [10] = ITEM10_REDUCE_IV,
};

#define FEATHER_FRIENDSHIP_CHANGE(i)             \
    [(i) + 0] = 3, /* Friendship change, low */  \
    [(i) + 1] = 2, /* Friendship change, mid */  \
    [(i) + 2] = 1  /* Friendship change, high */

const u8 gItemEffect_HpFeather[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_FRIENDSHIP_ALL,
    FEATHER_FRIENDSHIP_CHANGE(6),
    [10] = ITEM10_IV_HP,
};

const u8 gItemEffect_AtkFeather[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_FRIENDSHIP_ALL,
    FEATHER_FRIENDSHIP_CHANGE(6),
    [10] = ITEM10_IV_ATK,
};

const u8 gItemEffect_DefFeather[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_FRIENDSHIP_ALL,
    FEATHER_FRIENDSHIP_CHANGE(6),
    [10] = ITEM10_IV_DEF,
};

const u8 gItemEffect_SpeedFeather[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_FRIENDSHIP_ALL,
    FEATHER_FRIENDSHIP_CHANGE(6),
    [10] = ITEM10_IV_SPEED,
};

const u8 gItemEffect_SpatkFeather[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_FRIENDSHIP_ALL,
    FEATHER_FRIENDSHIP_CHANGE(6),
    [10] = ITEM10_IV_SPATK,
};

const u8 gItemEffect_SpdefFeather[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_FRIENDSHIP_ALL,
    FEATHER_FRIENDSHIP_CHANGE(6),
    [10] = ITEM10_IV_SPDEF,
};

const u8 gItemEffect_HpMochi[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_EV_HP,
    [6] = ITEM6_ADD_EV,
    [10] = 0,
};

const u8 gItemEffect_AtkMochi[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_EV_ATK,
    [6] = ITEM6_ADD_EV,
    [10] = 0,
};

const u8 gItemEffect_DefMochi[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_DEF,
    [6] = ITEM6_ADD_EV,
    [10] = 0,
};

const u8 gItemEffect_SpeedMochi[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_SPEED,
    [6] = ITEM6_ADD_EV,
    [10] = 0,
};

const u8 gItemEffect_SpatkMochi[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_SPATK,
    [6] = ITEM6_ADD_EV,
    [10] = 0,
};

const u8 gItemEffect_SpdefMochi[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_SPDEF,
    [6] = ITEM6_ADD_EV,
    [10] = 0,
};

const u8 gItemEffect_ResetMochi[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_EV_HP | ITEM4_EV_ATK,
    [5] = ITEM5_EV_DEF | ITEM5_EV_SPEED | ITEM5_EV_SPATK | ITEM5_EV_SPDEF,
    [6] = ITEM6_RESET_EV,
    [10] = 0,
};

const u8 gItemEffect_RareCandy[ITEM_EFFECT_COUNT] = {
    [3] = ITEM3_LEVEL_UP,
    [4] = ITEM4_REVIVE | ITEM4_HEAL_HP,
    [5] = ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_HEAL_HP_LVL_UP,
    VITAMIN_FRIENDSHIP_CHANGE(7),
};

const u8 gItemEffect_PPUp[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_PP_UP,
    [5] = ITEM5_FRIENDSHIP_ALL,
    VITAMIN_FRIENDSHIP_CHANGE(6),
};

const u8 gItemEffect_PPMax[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_PP_MAX | ITEM5_FRIENDSHIP_ALL,
    VITAMIN_FRIENDSHIP_CHANGE(6),
};

const u8 gItemEffect_GuardSpec[ITEM_EFFECT_COUNT] = {
    [3] = ITEM3_GUARD_SPEC,
};

// The first item effect value for the stat boost items
// only uses the least significant bit of its full mask.
// The full constant is commented next to it

const u8 gItemEffect_DireHit[ITEM_EFFECT_COUNT] = {
    [0] = 1 << 5, // ITEM0_DIRE_HIT
};

const u8 gItemEffect_XAttack[ITEM_EFFECT_COUNT] = {
    [1] = ITEM1_X_ATTACK,
};

const u8 gItemEffect_XDefense[ITEM_EFFECT_COUNT] = {
    [1] = ITEM1_X_DEFENSE,
};

const u8 gItemEffect_XSpeed[ITEM_EFFECT_COUNT] = {
    [1] = ITEM1_X_SPEED,
};

const u8 gItemEffect_XAccuracy[ITEM_EFFECT_COUNT] = {
    [1] = ITEM1_X_ACCURACY,
};

const u8 gItemEffect_XSpecialAttack[ITEM_EFFECT_COUNT] = {
    [1] = ITEM1_X_SPATK,
};

const u8 gItemEffect_XSpecialDefense[ITEM_EFFECT_COUNT] = {
    [1] = ITEM1_X_SPDEF,
};

const u8 gItemEffect_EvoItem[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_EVO_STONE,
};

const u8 gItemEffect_LeppaBerry[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_PP_ONE | ITEM4_HEAL_PP,
    [6] = 10, // Amount of PP to recover
};

const u8 gItemEffect_OranBerry[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
    [6] = 10, // Amount of HP to recover
};

const u8 gItemEffect_PersimBerry[ITEM_EFFECT_COUNT] = {
    [3] = ITEM3_CONFUSION,
};

const u8 gItemEffect_SitrusBerry[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_HEAL_HP,
#if I_SITRUS_BERRY_HEAL >= GEN_4
    [6] = ITEM6_HEAL_HP_QUARTER,
#else
    [6] = 30, // Amount of HP to recover
#endif
};

#define EV_BERRY_FRIENDSHIP_CHANGE          \
    [7] = 10, /* Friendship change, low */  \
    [8] = 5,  /* Friendship change, mid */  \
    [9] = 2   /* Friendship change, high */

const u8 gItemEffect_PomegBerry[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_EV_HP,
    [5] = ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_SUBTRACT_EV,
    EV_BERRY_FRIENDSHIP_CHANGE,
};

const u8 gItemEffect_KelpsyBerry[ITEM_EFFECT_COUNT] = {
    [4] = ITEM4_EV_ATK,
    [5] = ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_SUBTRACT_EV,
    EV_BERRY_FRIENDSHIP_CHANGE,
};

const u8 gItemEffect_QualotBerry[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_DEF | ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_SUBTRACT_EV,
    EV_BERRY_FRIENDSHIP_CHANGE,
};

const u8 gItemEffect_HondewBerry[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_SPATK | ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_SUBTRACT_EV,
    EV_BERRY_FRIENDSHIP_CHANGE,
};

const u8 gItemEffect_GrepaBerry[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_SPDEF | ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_SUBTRACT_EV,
    EV_BERRY_FRIENDSHIP_CHANGE,
};

const u8 gItemEffect_TamatoBerry[ITEM_EFFECT_COUNT] = {
    [5] = ITEM5_EV_SPEED | ITEM5_FRIENDSHIP_ALL,
    [6] = ITEM6_SUBTRACT_EV,
    EV_BERRY_FRIENDSHIP_CHANGE,
};
