
	insert_at equ 0x08f00000

	.gba
	.thumb
	.open input_game,output_game, 0x08000000

	.org insert_at
	.importobj relocatable_obj
	
	.include "patches/all.s"
	.close
