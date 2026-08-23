#include "global.h"
#include "pokemon_storage_system.h"
#include "test/test.h"

TEST("Pokemon Storage clears a stale deferred palette destination before enabling VBlank")
{
    EXPECT(PokemonStorageSystem_TestClearsStalePaletteSwapDestination());
}
