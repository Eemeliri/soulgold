#ifndef GUARD_SCRIPT_POKEMON_UTIL_H
#define GUARD_SCRIPT_POKEMON_UTIL_H

struct ScriptContext;

u32 ScriptGiveMon(u16 species, u8 level, enum Item item);
u8 ScriptGiveEgg(u16 species);
void CreateScriptedWildMon(u16 species, u8 level, enum Item item, u16 item2);
void CreateShinyScriptedMon(u16 species, u8 level, u16 item);
u32 GenerateShinyPersonalityForOtId(u32 otId);
void CreateScriptedDoubleWildMon(u16 species, u8 level, enum Item item, u16 item2, u16 species2, u8 level2, enum Item item3, u16 item4);
void ScriptSetMonMoveSlot(u8 monIndex, enum Move move, u8 slot);
void SetEnemyEventMonMoves(enum Move move1, enum Move move2, enum Move move3, enum Move move4);
void ScriptSetEnemyEventMonMoves(struct ScriptContext *ctx);
void ReducePlayerPartyToSelectedMons(void);
void HealPlayerParty(void);
void Script_GetChosenMonOffensiveEVs(void);
void Script_GetChosenMonDefensiveEVs(void);
void Script_GetChosenMonOffensiveIVs(void);
void Script_GetChosenMonDefensiveIVs(void);
void CreateScriptedWildMon2(u16, u8, u16, u8, u16, u16, u16, u16, bool8);

#endif // GUARD_SCRIPT_POKEMON_UTIL_H
