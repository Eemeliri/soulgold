VajraDesertEast_MapScripts::
	.byte 0


VajraDesertEast_TrainerSirocco::
	trainerbattle_single TRAINER_VAJRA_EAST_SIROCCO, VajraDesertEast_TrainerSirocco_Text_0, VajraDesertEast_TrainerSirocco_Text_1
	msgbox VajraDesertEast_TrainerSirocco_Text_2, MSGBOX_AUTOCLOSE
	end


VajraDesertEast_TrainerSol::
	trainerbattle_double TRAINER_VAJRA_EAST_SOL, VajraDesertEast_TrainerSol_Text_0, VajraDesertEast_TrainerSol_Text_1, VajraDesertEast_TrainerSol_Text_2
	msgbox VajraDesertEast_TrainerSol_Text_3, MSGBOX_AUTOCLOSE
	end


VajraDesertEast_TrainerDune::
	trainerbattle_single TRAINER_VAJRA_EAST_DUNE, VajraDesertEast_TrainerDune_Text_0, VajraDesertEast_TrainerDune_Text_1
	msgbox VajraDesertEast_TrainerDune_Text_2, MSGBOX_AUTOCLOSE
	end


VajraDesertEast_TrainerNori::
	trainerbattle_double TRAINER_VAJRA_EAST_NORI, VajraDesertEast_TrainerNori_Text_0, VajraDesertEast_TrainerNori_Text_1, VajraDesertEast_TrainerNori_Text_2
	msgbox VajraDesertEast_TrainerNori_Text_3, MSGBOX_AUTOCLOSE
	end


VajraDesertEast_TrainerAtlas::
	trainerbattle_double TRAINER_VAJRA_EAST_ATLAS, VajraDesertEast_TrainerAtlas_Text_0, VajraDesertEast_TrainerAtlas_Text_1, VajraDesertEast_TrainerAtlas_Text_2
	msgbox VajraDesertEast_TrainerAtlas_Text_3, MSGBOX_AUTOCLOSE
	end


VajraDesertEast_LadyofLake::
	msgbox VajraDesertEast_LadyofLake_Text_0, MSGBOX_NPC
	return


VajraDesertEastSign::
	msgbox VajraDesertEastSign_Text_0, MSGBOX_SIGN
	return


VajraDesertEast_TrainerSirocco_Text_0:
	.string "Let me see how tough you are!$"

VajraDesertEast_TrainerSirocco_Text_1:
	.string "Tough enough, I guess...$"

VajraDesertEast_TrainerSirocco_Text_2:
	.string "The hardest environments make the\n"
	.string "toughest trainers.\p"
	.string "I hope to become the very best\n"
	.string "someday!$"

VajraDesertEast_TrainerSol_Text_0:
	.string "Huff, huff! One more lap!$"

VajraDesertEast_TrainerSol_Text_1:
	.string "Need... water...!$"

VajraDesertEast_TrainerSol_Text_2:
	.string "Hey, you need two Pokémon ready to\n"
	.string "battle!$"

VajraDesertEast_TrainerSol_Text_3:
	.string "There's an oasis behind those palm\n"
	.string "trees, but you can't just go through\l"
	.string "them!$"

VajraDesertEast_TrainerDune_Text_0:
	.string "Riding high!$"

VajraDesertEast_TrainerDune_Text_1:
	.string "You caught me off guard...$"

VajraDesertEast_TrainerDune_Text_2:
	.string "Two Pokémon I'd never seen before\n"
	.string "flew past here. They've returned a\l"
	.string "few times.\p"
	.string "What were they, I wonder?$"

VajraDesertEast_TrainerNori_Text_0:
	.string "Are you the Trainer who beat Lance?$"

VajraDesertEast_TrainerNori_Text_1:
	.string "No way! The Champion beat me!$"

VajraDesertEast_TrainerNori_Text_2:
	.string "How does the Champion not have two\n"
	.string "Pokémon ready to battle?$"

VajraDesertEast_TrainerNori_Text_3:
	.string "Can't wait to tell all my friends about\n"
	.string "this!$"

VajraDesertEast_TrainerAtlas_Text_0:
	.string "Think you can reach the oasis?$"

VajraDesertEast_TrainerAtlas_Text_1:
	.string "Looks like you won't get lost among\n"
	.string "the trees!$"

VajraDesertEast_TrainerAtlas_Text_2:
	.string "Sorry, bud, but you need two Pokémon\n"
	.string "ready to battle.$"

VajraDesertEast_TrainerAtlas_Text_3:
	.string "This place is almost like a savanna,\n"
	.string "even though it's part of the desert!$"

VajraDesertEast_LadyofLake_Text_0:
	.string "This stream of water is crucial for the\n"
	.string "life here. I hope it never dries up.$"

VajraDesertEastSign_Text_0:
	.string "Vajra Desert East$"
