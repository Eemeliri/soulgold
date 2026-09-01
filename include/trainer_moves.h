#ifndef GUARD_TRAINER_MOVES_H
#define GUARD_TRAINER_MOVES_H

#include "data.h"

struct Pokemon;

bool32 TrainerMonHasExplicitMoves(const struct TrainerMon *partyEntry);
bool32 IsAutomaticTrainerMoveSuitableForSingles(enum Move move);
bool32 IsTrainerMoveStab(enum Move move, u16 species, u8 level);
void BuildTrainerMonMoves(enum Move outMoves[MAX_MON_MOVES],
                          const struct TrainerMon *partyEntry,
                          u16 actualSpecies,
                          u8 actualLevel,
                          enum TrainerBattleType battleType,
                          enum DifficultyLevel activeDifficulty);
void AssignTrainerMonMoves(struct Pokemon *mon,
                           const struct TrainerMon *partyEntry,
                           enum TrainerBattleType battleType,
                           enum DifficultyLevel activeDifficulty);

#endif // GUARD_TRAINER_MOVES_H
