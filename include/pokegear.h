#ifndef GUARD_POKEGEAR_H
#define GUARD_POKEGEAR_H

enum PokegearApp
{
    POKEGEAR_APP_MAP,
    POKEGEAR_APP_DEXNAV,
    POKEGEAR_APP_TROPHIES,
    POKEGEAR_APP_RADIO,
    POKEGEAR_APP_COUNT,
};

void CB2_InitPokegear(void);
void CB2_ReturnToPokegear(void);
bool32 IsPokegearAppUnlocked(enum PokegearApp app);
void OpenPokegearApp(enum PokegearApp app, MainCallback callback);

#endif // GUARD_POKEGEAR_H
