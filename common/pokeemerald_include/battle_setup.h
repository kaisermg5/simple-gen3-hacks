#ifndef GUARD_BATTLE_SETUP_H
#define GUARD_BATTLE_SETUP_H

enum
{
    TRAINER_BATTLE_NORMAL,
    TRAINER_BATTLE_CONTINUE_SCRIPT_NO_MUSIC,
    TRAINER_BATTLE_CONTINUE_SCRIPT,
    TRAINER_BATTLE_NORMAL_NO_INTRO_TEXT,
    TRAINER_BATTLE_DOUBLE,
    TRAINER_BATTLE_REMATCH,
    TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE,
    TRAINER_BATTLE_REMATCH_DOUBLE,
    TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE_NO_MUSIC,
    TRAINER_BATTLE_9,
    TRAINER_BATTLE_SET_TRAINER_A,
    TRAINER_BATTLE_SET_TRAINER_B,
    TRAINER_BATTLE_12,
};

#define REMATCHES_COUNT 5
#define REMATCH_TABLE_ENTRIES 78
#define REMATCH_WALLY_ENTRY 64
#define REMATCH_ELITE_FOUR_ENTRIES 73

struct RematchTrainer
{
    u16 trainerIds[REMATCHES_COUNT];
    u16 mapGroup;
    u16 mapNum;
};

extern const struct RematchTrainer gRematchTable[REMATCH_TABLE_ENTRIES];

extern u16 gTrainerBattleOpponent_A;
extern u16 gTrainerBattleOpponent_B;
extern u16 gPartnerTrainerId;

void BattleSetup_StartWildBattle(void);
void BattleSetup_StartBattlePikeWildBattle(void);
void BattleSetup_StartRoamerBattle(void);
void StartWallyTutorialBattle(void);
void BattleSetup_StartScriptedWildBattle(void);
void BattleSetup_StartLatiBattle(void);
void BattleSetup_StartLegendaryBattle(void);
void StartGroudonKyogreBattle(void);
void StartRegiBattle(void);
u8 BattleSetup_GetTerrainId(void);
u8 sub_80B100C(s32 arg0);
void ChooseStarter(void);
void ResetTrainerOpponentIds(void);
void SetMapVarsToTrainer(void);
const u8 *BattleSetup_ConfigureTrainerBattle(const u8 *data);
void ConfigureAndSetUpOneTrainerBattle(u8 trainerMapObjId, const u8 *trainerScript);
void ConfigureTwoTrainersBattle(u8 trainerMapObjId, const u8 *trainerScript);
void SetUpTwoTrainersBattle(void);
bool32 GetTrainerFlagFromScriptPointer(const u8 *data);
void sub_80B16D8(void);
u8 GetTrainerBattleMode(void);
bool8 GetTrainerFlag(void);
bool8 HasTrainerBeenFought(u16 trainerId);
void SetTrainerFlag(u16 trainerId);
void ClearTrainerFlag(u16 trainerId);
void BattleSetup_StartTrainerBattle(void);
void BattleSetup_StartRematchBattle(void);
void ShowTrainerIntroSpeech(void);
const u8 *BattleSetup_GetScriptAddrAfterBattle(void);
const u8 *BattleSetup_GetTrainerPostBattleScript(void);
void ShowTrainerCantBattleSpeech(void);
void SetUpTrainerEncounterMusic(void);
const u8 *GetTrainerALoseText(void);
const u8 *GetTrainerBLoseText(void);
const u8 *GetTrainerWonSpeech(void);
void UpdateRematchIfDefeated(s32 rematchTableId);
void IncrementRematchStepCounter(void);
void TryUpdateRandomTrainerRematches(u16 mapGroup, u16 mapNum);
bool32 DoesSomeoneWantRematchIn(u16 mapGroup, u16 mapNum);
bool32 IsRematchTrainerIn(u16 mapGroup, u16 mapNum);
u16 GetLastBeatenRematchTrainerId(u16 trainerId);
bool8 ShouldTryRematchBattle(void);
bool8 IsTrainerReadyForRematch(void);
void ShouldTryGetTrainerScript(void);
u16 CountBattledRematchTeams(u16 trainerId);

#endif // GUARD_BATTLE_SETUP_H
