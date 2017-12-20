
#include <global.h>
#include <flags.h>

// Menu actions
enum
{
    MENU_ACTION_POKEDEX,
    MENU_ACTION_POKEMON,
    MENU_ACTION_BAG,
#ifdef BPEE
    MENU_ACTION_POKENAV,
#endif
    MENU_ACTION_PLAYER,
    MENU_ACTION_SAVE,
    MENU_ACTION_OPTION,
    MENU_ACTION_EXIT,
    MENU_ACTION_RETIRE_SAFARI,
    MENU_ACTION_PLAYER_LINK,
#ifdef BPEE
    MENU_ACTION_REST_FRONTIER,
    MENU_ACTION_RETIRE_FRONTIER,
    MENU_ACTION_PYRAMID_BAG
#endif
};


extern u8 FlagGet(u16 flag_num);
extern void AddStartMenuAction(u8 action);

void Custom_BuildStartMenuActions_Normal(void)
{
	if (FlagGet(FLAG_SYS_POKEDEX_GET)) {
		AddStartMenuAction(MENU_ACTION_POKEDEX);
	}
	if (FlagGet(FLAG_SYS_POKEMON_GET)) {
		AddStartMenuAction(MENU_ACTION_POKEMON);
	}
	if (FlagGet(FLAG_SYS_BAG_GET)) {
		AddStartMenuAction(MENU_ACTION_BAG);
	}
#ifdef BPEE
	if (FlagGet(FLAG_SYS_POKENAV_GET)) {
		AddStartMenuAction(MENU_ACTION_POKENAV);
	}
#endif

	for (int action = MENU_ACTION_PLAYER; action <= MENU_ACTION_EXIT; action++) {	// AddStartMenuAction(MENU_ACTION_PLAYER);
		AddStartMenuAction(action);													// AddStartMenuAction(MENU_ACTION_SAVE);
	}																				// AddStartMenuAction(MENU_ACTION_OPTION);
																					// AddStartMenuAction(MENU_ACTION_EXIT);
}






