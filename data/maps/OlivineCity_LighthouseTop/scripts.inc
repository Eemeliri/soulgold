OlivineCity_LighthouseTop_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_LighthouseTop_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

OlivineCity_LighthouseTop_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	goto_if_unset FLAG_HIDE_ZAPDOS, OlivineCity_LighthouseTop_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
	setweather WEATHER_NONE
	return

OlivineCity_LighthouseTop_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
	setweather WEATHER_RAIN_THUNDERSTORM
	return


Lighthousetop_Zapdos::
	lock
	faceplayer
	legendaryencounter SPECIES_ZAPDOS, 50, LOCALID_LIGHTHOUSE_ZAPDOS, FLAG_HIDE_ZAPDOS
	release
	end


Lighthouse_Engineer::
	lock
	faceplayer
	msgbox Lighthouse_Engineer_Text_0
	release
	end


Lighthouse_Engineer_Text_0:
	.string "Some Pokémon broke the ladder to the\n"
	.string "top floor recently.\p"
	.string "I'm trying to fix it, but it\n"
	.string "will take some time.$"
