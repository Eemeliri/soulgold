#include "global.h"
#include "agb_flash.h"
#include "credits.h"
#include "event_data.h"
#include "hall_of_fame.h"
#include "link.h"
#include "main.h"
#include "gba/flash_internal.h"
#include "malloc.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "overworld.h"
#include "save.h"
#include "start_menu.h"
#include "task.h"
#include "trade.h"
#include "mystery_gift_menu.h"
#include "union_room_chat.h"
#include "test/test.h"
#include "constants/characters.h"
#include "constants/game_stat.h"

// If you would like to ensure save compatibility, update the values below with those for your hack. You can find these through the debug menu.
// Please note that this simple check is not 100% foolproof, but should be able to catch most unintended shifts.
#define T_SAVEBLOCK1_SIZE 15444
#define T_SAVEBLOCK2_SIZE 2864
#define T_SAVEBLOCK3_SIZE 100
#define T_POKEMONSTORAGE_SIZE 43916

TEST("SaveBlock1 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock1), T_SAVEBLOCK1_SIZE);
}

TEST("SaveBlock2 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock2), T_SAVEBLOCK2_SIZE);
}

TEST("SaveBlock3 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock3), T_SAVEBLOCK3_SIZE);
}

TEST("PokemonStorage is backwards compatible")
{
    EXPECT_EQ(sizeof(struct PokemonStorage), T_POKEMONSTORAGE_SIZE);
}

#undef T_SAVEBLOCK1_SIZE
#undef T_SAVEBLOCK2_SIZE
#undef T_SAVEBLOCK3_SIZE
#undef T_POKEMONSTORAGE_SIZE

