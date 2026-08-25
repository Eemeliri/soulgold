.set LOCALID_INDIGOJUNCTION_POLICEMAN, 1
.set LOCALID_INDIGOJUNCTION_JANINE, 4

ReceptionGate_MapScripts::
	.byte 0

ReceptionGate_EventScript_Janine::
    lock
    faceplayer
    msgbox ReceptionGate_Text_Janine, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_ROUTE22_JANINE
    removeobject LOCALID_INDIGOJUNCTION_JANINE
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_JANINE
    release
    end

ReceptionGate_Text_Janine:
    .string "Jaine: I'm on the way to my dad's\n"
    .string "house to give him his lunch.\p"
    .string "The Elite Four has no time to rest\n"
    .string "day or night. It's such hard work,\l"
    .string "you know?\p"
    .string "If you're ready for another battle,\n"
    .string "I'll be at the Dojo later.$"


ReceptionGate_EventScript_Officer::
    lock
    faceplayer
    goto_if_set FLAG_IS_CHAMPION, ReceptionGate_EventScript_OfficerCleared
    goto_if_unset FLAG_BADGE08_GET, ReceptionGate_EventScript_OfficerNotEnough
    goto_if_set FLAG_LEGENDARY_STORY_CAP, ReceptionGate_EventScript_OfficerCleared
    call ReceptionGate_EventScript_ShowStoryGuidance
    closemessage
    release
    end

ReceptionGate_EventScript_OfficerNotEnough::
    msgbox VictoryRoadGate_Text_NotEnoughBadges, MSGBOX_DEFAULT
    closemessage
    release
    end

ReceptionGate_EventScript_OfficerCleared::
    msgbox VictoryRoadGate_Text_EightBadges, MSGBOX_DEFAULT
    closemessage
    release
    end

ReceptionGate_Trigger::
    lock
    playse SE_PIN
    applymovement LOCALID_INDIGOJUNCTION_POLICEMAN, Common_Movement_ExclamationMark
    delay 20
    goto_if_unset FLAG_BADGE08_GET, ReceptionGate_EventScript_NotEnough
    goto_if_unset FLAG_LEGENDARY_STORY_CAP, ReceptionGate_EventScript_StoryBlocked
    msgbox VictoryRoadGate_Text_EightBadges, MSGBOX_DEFAULT
    closemessage
    setvar VAR_ROUTE27_STATE, 1
    release
    end

ReceptionGate_EventScript_StoryBlocked::
    call ReceptionGate_EventScript_ShowStoryGuidance
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
    waitmovement 0
    release
    end 

ReceptionGate_EventScript_NotEnough::
    msgbox VictoryRoadGate_Text_NotEnoughBadges, MSGBOX_DEFAULT
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
    waitmovement 0
    release
    end

ReceptionGate_EventScript_ShowStoryGuidance::
    goto_if_ge VAR_ECRUTEAK_CITY_THEATER, 7, ReceptionGate_EventScript_ShowLegendaryGuidance
    goto_if_ge VAR_NEWBARKTOWN_LABSTATE, 9, ReceptionGate_EventScript_ShowLegendaryGuidance
    goto_if_ge VAR_ECRUTEAK_CITY_THEATER, 4, ReceptionGate_EventScript_ShowKimonoGuidance
    goto_if_ge VAR_NEWBARKTOWN_LABSTATE, 8, ReceptionGate_EventScript_ShowKimonoGuidance
    msgbox VictoryRoadGate_Text_VisitElm, MSGBOX_DEFAULT
    return

ReceptionGate_EventScript_ShowKimonoGuidance::
    msgbox VictoryRoadGate_Text_VisitKimonoGirls, MSGBOX_DEFAULT
    return

ReceptionGate_EventScript_ShowLegendaryGuidance::
    goto_if_eq VAR_LUGIA_OR_HOOH, 1, ReceptionGate_EventScript_ShowWhirlIslandsGuidance
    goto ReceptionGate_EventScript_ShowTinTowerGuidance

ReceptionGate_EventScript_ShowWhirlIslandsGuidance::
    msgbox VictoryRoadGate_Text_VisitWhirlIslands, MSGBOX_DEFAULT
    return

ReceptionGate_EventScript_ShowTinTowerGuidance::
    msgbox VictoryRoadGate_Text_VisitTinTower, MSGBOX_DEFAULT
    return

ReceptionGate_EventScript_SilverGuard::
    msgbox VictoryRoadGate_Text_LeftBlackBelt, MSGBOX_NPC
    end
ReceptionGate_EventScript_KantoGuard::
    msgbox VictoryRoadGate_Text_RightBlackBelt, MSGBOX_NPC
    end

VictoryRoadGate_Text_VisitElm:
    .string "You're {PLAYER}, right?\p"
    .string "Prof. Elm has been trying to\n"
    .string "reach you.\p"
    .string "Go see him at his Lab in\n"
    .string "New Bark Town!$"

VictoryRoadGate_Text_VisitKimonoGirls:
    .string "One of the Kimono Girls asked me\n"
    .string "to relay a message.\p"
    .string "They're waiting for you at the\n"
    .string "Ecruteak Dance Theater.$"

VictoryRoadGate_Text_VisitWhirlIslands:
    .string "The Kimono Girls traced the\n"
    .string "Legendary Pokémon to the\l"
    .string "Whirl Islands.\p"
    .string "Head there before challenging the\n"
    .string "Pokémon League.$"

VictoryRoadGate_Text_VisitTinTower:
    .string "The Kimono Girls traced the\n"
    .string "Legendary Pokémon to the\l"
    .string "Tin Tower.\p"
    .string "Head there before challenging the\n"
    .string "Pokémon League.$"

VictoryRoadGate_Text_NotEnoughBadges:
    .string "You don't have all the Gym Badges\n"
    .string "of Johto.\p"
    .string "I'm sorry, but I can't let you go\n"
    .string "through.$"

VictoryRoadGate_Text_EightBadges:
    .string "Oh! The eight Badges of Johto!\p"
    .string "Please, go right on through!$"

VictoryRoadGate_Text_LeftBlackBelt:
    .string "This way leads to Mt.Silver.\p"
    .string "You'll see scary-strong Pokémon out\n"
    .string "there.$"

VictoryRoadGate_Text_RightBlackBelt:
    .string "Off to the Pokémon League, are you?\p"
    .string "The Elite Four are so strong it's\n"
    .string "scary, and they're ready for you!$"
