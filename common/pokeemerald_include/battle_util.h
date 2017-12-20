#ifndef GUARD_BATTLE_UTIL_H
#define GUARD_BATTLE_UTIL_H

#define MOVE_LIMITATION_ZEROMOVE                (1 << 0)
#define MOVE_LIMITATION_PP                      (1 << 1)
#define MOVE_LIMITATION_DISABLED                (1 << 2)
#define MOVE_LIMITATION_TORMENTED               (1 << 3)
#define MOVE_LIMITATION_TAUNT                   (1 << 4)
#define MOVE_LIMITATION_IMPRISION               (1 << 5)

#define ABILITYEFFECT_ON_SWITCHIN               0x0
#define ABILITYEFFECT_ENDTURN                   0x1
#define ABILITYEFFECT_MOVES_BLOCK               0x2
#define ABILITYEFFECT_ABSORBING                 0x3
#define ABILITYEFFECT_CONTACT                   0x4
#define ABILITYEFFECT_IMMUNITY                  0x5
#define ABILITYEFFECT_FORECAST                  0x6
#define ABILITYEFFECT_SYNCHRONIZE               0x7
#define ABILITYEFFECT_ATK_SYNCHRONIZE           0x8
#define ABILITYEFFECT_INTIMIDATE1               0x9
#define ABILITYEFFECT_INTIMIDATE2               0xA
#define ABILITYEFFECT_TRACE                     0xB
#define ABILITYEFFECT_CHECK_OTHER_SIDE          0xC
#define ABILITYEFFECT_CHECK_BANK_SIDE           0xD
#define ABILITYEFFECT_FIELD_SPORT               0xE
#define ABILITYEFFECT_CHECK_FIELD_EXCEPT_BANK   0xF
#define ABILITYEFFECT_COUNT_OTHER_SIDE          0x10
#define ABILITYEFFECT_COUNT_BANK_SIDE           0x11
#define ABILITYEFFECT_COUNT_ON_FIELD            0x12
#define ABILITYEFFECT_CHECK_ON_FIELD            0x13
#define ABILITYEFFECT_SWITCH_IN_WEATHER         0xFF

#define ITEMEFFECT_ON_SWITCH_IN                 0x0

#define WEATHER_HAS_EFFECT ((!AbilityBattleEffects(ABILITYEFFECT_CHECK_ON_FIELD, 0, ABILITY_CLOUD_NINE, 0, 0) && !AbilityBattleEffects(ABILITYEFFECT_CHECK_ON_FIELD, 0, ABILITY_AIR_LOCK, 0, 0)))
#define WEATHER_HAS_EFFECT2 ((!AbilityBattleEffects(ABILITYEFFECT_FIELD_SPORT, 0, ABILITY_CLOUD_NINE, 0, 0) && !AbilityBattleEffects(ABILITYEFFECT_FIELD_SPORT, 0, ABILITY_AIR_LOCK, 0, 0)))

#define BS_GET_TARGET                   0
#define BS_GET_ATTACKER                 1
#define BS_GET_EFFECT_BANK              2
#define BS_GET_SCRIPTING_BANK           10
#define BS_GET_PLAYER1                  11
#define BS_GET_OPPONENT1                12
#define BS_GET_PLAYER2                  13
#define BS_GET_OPPONENT2                14

u8 GetBattleBank(u8 caseId);
void PressurePPLose(u8 bankDef, u8 bankAtk, u16 move);
void PressurePPLoseOnUsingPerishSong(u8 bankAtk);
void PressurePPLoseOnUsingImprision(u8 bankAtk);
void MarkAllBufferBanksForExecution(void); // unused
void MarkBufferBankForExecution(u8 bank);
void sub_803F850(u8 arg0);
void CancelMultiTurnMoves(u8 bank);
bool8 WasUnableToUseMove(u8 bank);
void PrepareStringBattle(u16 stringId, u8 bank);
void ResetSentPokesToOpponentValue(void);
void sub_803F9EC(u8 bank);
void sub_803FA70(u8 bank);
void BattleScriptPush(const u8* bsPtr);
void BattleScriptPushCursor(void);
void BattleScriptPop(void);
u8 TrySetCantSelectMoveBattleScript(void);
u8 CheckMoveLimitations(u8 bank, u8 unusableMoves, u8 check);
bool8 AreAllMovesUnusable(void);
u8 GetImprisonedMovesCount(u8 bank, u16 move);
u8 UpdateTurnCounters(void);
u8 TurnBasedEffects(void);
bool8 HandleWishPerishSongOnTurnEnd(void);
bool8 HandleFaintedMonActions(void);
void TryClearRageStatuses(void);
u8 AtkCanceller_UnableToUseMove(void);
bool8 sub_80423F4(u8 bank, u8 r1, u8 r2);
u8 CastformDataTypeChange(u8 bank);
u8 AbilityBattleEffects(u8 caseID, u8 bank, u8 ability, u8 special, u16 moveArg);
void BattleScriptExecute(const u8* BS_ptr);
void BattleScriptPushCursorAndCallback(const u8* BS_ptr);
u8 ItemBattleEffects(u8 caseID, u8 bank, bool8 moveTurn);
void ClearFuryCutterDestinyBondGrudge(u8 bank);
void HandleAction_RunBattleScript(void);
u8 GetMoveTarget(u16 move, u8 useMoveTarget);
u8 IsMonDisobedient(void);

#endif // GUARD_BATTLE_UTIL_H
