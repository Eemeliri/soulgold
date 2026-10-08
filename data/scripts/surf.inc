EventScript_UseSurf::
	checkfieldmove FIELD_MOVE_SURF
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_EndUseSurf
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	lockall
	goto_if_set FLAG_FAST_HMS, EventScript_StartSurf
	msgbox gText_WantToUseSurf, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_ReleaseUseSurf
	msgbox gText_PlayerUsedSurf, MSGBOX_DEFAULT
EventScript_StartSurf:
	dofieldeffect FLDEFF_USE_SURF
	waitfieldeffect FLDEFF_USE_SURF
	goto EventScript_EndUseSurf

EventScript_SurfAWave::
	goto_if_set FLAG_FAST_HMS, EventScript_StartSurf
	msgbox gText_PlayerUsedSurf, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_SURF
	waitfieldeffect FLDEFF_USE_SURF
	goto EventScript_EndUseSurf

EventScript_ReleaseUseSurf::
	releaseall

EventScript_EndUseSurf::
	releaseall
	end
