

#include <flags.h>

.thumb
.align 2

.global custom_can_use_item_check
custom_can_use_item_check:
	ldrh r0, flag_num
	ldr r1, =FlagGet
	bl bx_r1
	cmp r0, #0
	beq	not_items_allowed
	
	ldr r0, =vanilla_can_use_item_check
	mov pc, r0

not_items_allowed:
	ldr r0, =case_no_items_in_battle
	mov pc, r0

bx_r1:
	bx r1

.align 2
flag_num:
	.2byte FLAG_SYS_BAG_GET
.pool

