#ifndef GUARD_BATTLE_BG_H
#define GUARD_BATTLE_BG_H

#define BATTLE_COMMAND_PAL_NUM 13
#define BATTLE_WINDOW_DARK_BG_PAL_INDEX 8
#define BATTLE_WINDOW_DARK_FG_PAL_INDEX 14
#define BATTLE_WINDOW_DARK_SHADOW_PAL_INDEX 13

struct BattleBackground
{
    const void *tileset;
    const void *tilemap;
};

struct BattleBackgroundEntry
{
    const void *tileset;
    const void *tilemap;
};

void BattleInitBgsAndWindows(void);
void InitBattleBgsVideo(void);
void LoadBattleMenuWindowGfx(void);
void LoadBattleMoveDescriptionWindowGfx(void);
void DrawMainBattleBackground(void);
void LoadBattleTextboxAndBackground(void);
void InitLinkBattleVsScreen(u8 taskId);
void DrawBattleEntryBackground(void);
bool8 LoadChosenBattleElement(u8 caseId);
void DrawTerrainTypeBattleBackground(void);
bool32 BattleEnvironmentForcesNoIntroSlide(void);

#endif // GUARD_BATTLE_BG_H
