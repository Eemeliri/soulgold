#ifndef GUARD_UNION_ROOM_CHAT_H
#define GUARD_UNION_ROOM_CHAT_H

void EnterUnionRoomChat(void);
void InitUnionRoomChatRegisteredTexts(void);

#if TESTING
bool8 UnionRoomChat_TestTrySave(void);
#endif

extern const u8 gCaseToggleTable[256];

#endif // GUARD_UNION_ROOM_CHAT_H
