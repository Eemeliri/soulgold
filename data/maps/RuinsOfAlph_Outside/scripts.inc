
RuinsOfAlph_Outside_MapScripts::
	.byte 0

RuinsOfAlph_Outside_EventScript_Quagsire::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_QUAGSIRE, CRY_MODE_NORMAL
	msgbox RuinsOfAlph_Outside_Text_Quagsire, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RuinsOfAlph_Outside_Text_Quagsire:
	.string "Quagsire: Quag Quag$"

RuinsOfAlph_Outside_EventScript_Stan::
	trainerbattle_single TRAINER_STAN, RuinsOfAlph_Outside_Text_SuperNerdStan_Seen, RuinsOfAlph_Outside_Text_SuperNerdStan_Beaten
	msgbox RuinsOfAlph_Outside_Text_SuperNerdStan_After, MSGBOX_AUTOCLOSE
	end

RuinsOfAlph_Outside_EventScript_Nathan::
	trainerbattle_single TRAINER_NATHAN, RuinsOfAlph_Outside_Text_PsychicNathan_Seen, RuinsOfAlph_Outside_Text_PsychicNathan_Beaten
	msgbox RuinsOfAlph_Outside_Text_PsychicNathan_After, MSGBOX_AUTOCLOSE
	end

RuinsOfAlph_Outside_EventScript_Youngster1::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Youngster1, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Youngster2::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Youngster2, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Fisher1::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Fisher1, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Fisher2::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Fisher2, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Sign1::
	lock
	msgbox RuinsOfAlph_Outside_Text_MainSign, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Sign2::
	lock
	msgbox RuinsOfAlph_Outside_Text_ResearchSign, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Sign3::
	lock
	msgbox RuinsOfAlph_Outside_Text_MysteryChamberSign, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_Outside_Text_Scientist:
	.string "Hm? That's a Pokédex, isn't it?\n"
	.string "May I see it?\p"
	.string "There are so many kinds of\n"
	.string "Pokémon.\p"
	.string "Hm? What's this?\p"
	.string "What is this Pokémon?\p"
	.string "It looks like the strange\n"
	.string "writing on the walls of the\p"
	.string "Ruins.\p"
	.string "If those drawings are really\n"
	.string "Pokémon, there should be many\n"
	.string "more.\p"
	.string "I know! Let me upgrade your\n"
	.string "Pokédex. Follow me.$"

RuinsOfAlph_Outside_Text_SuperNerdStan_Seen:
	.string "What do you want? I'm studying--\n"
	.string "don't disturb me!$"

RuinsOfAlph_Outside_Text_SuperNerdStan_Beaten:
	.string "Sorry…\n"
	.string "I'm frustrated by our lack of\p"
	.string "real understanding…$"

RuinsOfAlph_Outside_Text_SuperNerdStan_After:
	.string "The Ruins are from about 1500\n"
	.string "years ago.\p"
	.string "Nobody knows who built them.\p"
	.string "It's also not known if the Pokémon\n"
	.string "statues have any meaning.\p"
	.string "It's all one big mystery…$"

RuinsOfAlph_Outside_Text_PsychicNathan_Seen:
	.string "Hmmm… This is a strange place.$"

RuinsOfAlph_Outside_Text_PsychicNathan_Beaten:
	.string "…$"

RuinsOfAlph_Outside_Text_PsychicNathan_After:
	.string "I like thinking here.$"

RuinsOfAlph_Outside_Text_MysteryChamberSign:
	.string "Mystery Stone Panel Chamber$"

RuinsOfAlph_Outside_Text_MainSign:
	.string "Ruins Of Alph\n"
	.string "Visitors Welcome$"

RuinsOfAlph_Outside_Text_ResearchSign:
	.string "Ruins Of Alph Research Center\p"
	.string "The Authority On The\n"
	.string "Ruins Of Alph$"

RuinsOfAlph_Outside_Text_Fisher1:
	.string "While exploring the Ruins, we\n"
	.string "suddenly noticed an odd presence.\p"
	.string "We all got scared and ran away.\n"
	.string "You should be careful too.$"

RuinsOfAlph_Outside_Text_Fisher2:
	.string "The Ruins hide a huge secret!\p"
	.string "…I think…$"

RuinsOfAlph_Outside_Text_Youngster1:
	.string "There are many kinds of Unown, so\n"
	.string "we use them for our secret codes.$"

RuinsOfAlph_Outside_Text_Youngster2:
	.string "A… H… E… A… D… Hmm…\p"
	.string "What?\p"
	.string "I'm decoding this message!$"

RuinsofAlph_Scientist::
	msgbox RuinsofAlph_Scientist_Text_0, MSGBOX_NPC
	return


CameronCamera::
	lock
	faceplayer
	msgbox CameronCamera_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq CameronCamera_1
	msgbox CameronCamera_Text_2
	release
	end

CameronCamera_1:
	msgbox CameronCamera_Text_1
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CAMERON
	removeobject VAR_LAST_TALKED
	special ShowPartyPhotoLineup
	delay 60
	fadescreenswapbuffers FADE_FROM_BLACK
	waitbuttonpress
	fadescreenswapbuffers FADE_TO_BLACK
	delay 30
	special HidePartyPhotoLineup
	delay 30
	setflag FLAG_CAMERON_PHOTO1
	special Achievement_CheckAll
	clearflag FLAG_HIDE_CAMERON
	addobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end


CameronCamera2::
	lock
	faceplayer
	msgbox CameronCamera_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq CameronCamera2_1
	msgbox CameronCamera_Text_2
	release
	end

CameronCamera2_1:
	msgbox CameronCamera_Text_1
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CAMERON
	removeobject VAR_LAST_TALKED
	special ShowPartyPhotoLineup
	delay 60
	fadescreenswapbuffers FADE_FROM_BLACK
	waitbuttonpress
	fadescreenswapbuffers FADE_TO_BLACK
	delay 30
	special HidePartyPhotoLineup
	delay 30
	setflag FLAG_CAMERON_PHOTO2
	special Achievement_CheckAll
	clearflag FLAG_HIDE_CAMERON
	addobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end


CameronCamera3::
	lock
	faceplayer
	msgbox CameronCamera_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq CameronCamera3_1
	msgbox CameronCamera_Text_2
	release
	end

CameronCamera3_1:
	msgbox CameronCamera_Text_1
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CAMERON
	removeobject VAR_LAST_TALKED
	special ShowPartyPhotoLineup
	delay 60
	fadescreenswapbuffers FADE_FROM_BLACK
	waitbuttonpress
	fadescreenswapbuffers FADE_TO_BLACK
	delay 30
	special HidePartyPhotoLineup
	delay 30
	setflag FLAG_CAMERON_PHOTO3
	special Achievement_CheckAll
	clearflag FLAG_HIDE_CAMERON
	addobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end


CameronCamera4::
	lock
	faceplayer
	msgbox CameronCamera_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq CameronCamera4_1
	msgbox CameronCamera_Text_2
	release
	end

CameronCamera4_1:
	msgbox CameronCamera_Text_1
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CAMERON
	removeobject VAR_LAST_TALKED
	special ShowPartyPhotoLineup
	delay 60
	fadescreenswapbuffers FADE_FROM_BLACK
	waitbuttonpress
	fadescreenswapbuffers FADE_TO_BLACK
	delay 30
	special HidePartyPhotoLineup
	delay 30
	setflag FLAG_CAMERON_PHOTO4
	special Achievement_CheckAll
	clearflag FLAG_HIDE_CAMERON
	addobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end


CameronCamera5::
	lock
	faceplayer
	msgbox CameronCamera_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq CameronCamera5_1
	msgbox CameronCamera_Text_2
	release
	end

CameronCamera5_1:
	msgbox CameronCamera_Text_1
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CAMERON
	removeobject VAR_LAST_TALKED
	special ShowPartyPhotoLineup
	delay 60
	fadescreenswapbuffers FADE_FROM_BLACK
	waitbuttonpress
	fadescreenswapbuffers FADE_TO_BLACK
	delay 30
	special HidePartyPhotoLineup
	delay 30
	setflag FLAG_CAMERON_PHOTO5
	special Achievement_CheckAll
	clearflag FLAG_HIDE_CAMERON
	addobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end


RuinsofAlph_Scientist_Text_0:
	.string "Sometimes fossils can be found while\n"
	.string "breaking rocks in here.$"

CameronCamera_Text_0:
	.string "Hello, \n"
	.string "just when you least expect it! \p"
	.string "I am Cameron the Photographer. \p"
	.string "You look so photogenic! \n"
	.string "Why not have a picture taken?$"

CameronCamera_Text_1:
	.string "All right, then! Get yourselves ready!$"

CameronCamera_Text_2:
	.string "Aren't you a shy one?$"
