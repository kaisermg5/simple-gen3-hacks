	.gba
	.thumb
	.open input_game,output_game, 0x08000000

	.org 0x08f00000
	.importobj relocatable_obj
	
	.include "patches/all.s"
	.close
