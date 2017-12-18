
#include <global.h>
#include <script.h>
#include <pokemon.h>
#include <pokedex.h>
#include <event_data.h>


static struct Pokemon* GetMonToModify(u8 mon_num)
{
	if (mon_num < PARTY_SIZE) {
		return &gPlayerParty[mon_num];
	} else {
		return &gEnemyParty[mon_num - PARTY_SIZE];
	}
}

// getmondata MON_NUM FIELD VAR1_NUM VAR2_NUM
bool8 ScrCmd_GetMonData(struct ScriptContext *ctx)
{
	struct Pokemon *mon = GetMonToModify(ScriptReadByte(ctx));
	u32 data = GetMonData(mon, ScriptReadByte(ctx), 0);
	
	VarSet(ScriptReadHalfword(ctx), (u16) data);
	VarSet(ScriptReadHalfword(ctx), (u16) (data >> 16));
	return false;
}

#define MOD_25_EQUALS_24 0x4f00
#define MOD_25_AND_24_EQUALS_0 0x4b00
#define MOD_24_EQUALS_16 0x1900

void SetMonNature(struct Pokemon *mon, u8 nature)
{
	u32 personality, oldMod24;
	u8 originalNature, firstByte;
	
	personality = GetMonData(mon, MON_DATA_PERSONALITY, 0);
	
	firstByte = (u8) personality;
	// The first byte contains data from the gender and ability
	originalNature = __umodsi3(firstByte, 25);

	// Lot's of numeric "hacks" to prevent the change in the order of the pokemon's subtructures
	// whilst modifiying the nature
	oldMod24 = __umodsi3(personality, 24);
	
	personality = firstByte + MOD_25_EQUALS_24 * (50 - nature + originalNature) + Random() * MOD_25_AND_24_EQUALS_0;
	while (oldMod24 != __umodsi3(personality, 24)) {
		personality += MOD_24_EQUALS_16;
	}

	
	// Setting the new personality correctly...
	DecryptBoxMon(&mon->box);
	SetMonData(mon, MON_DATA_PERSONALITY, &personality);

	mon->box.checksum = CalculateBoxMonChecksum(&mon->box);
	EncryptBoxMon(&mon->box);

	CalculateMonStats(mon);	
}



enum {
	SET_MON_DATA_MODE_READ_CONSTANT,
	SET_MON_DATA_MODE_READ_VARS,
	SET_MON_DATA_MODE_READ_CONST_PTR,
};

#define MON_DATA_NATURE 0xFF

//setmondata MODE MON_NUM FIELD DATA/VAR_NUMS
bool8 SrcCmd_SetMonData(struct ScriptContext *ctx)
{
	u32 data;
	u32 *data_ptr; 
	u8 mode = ScriptReadByte(ctx);
	u8 monNum = ScriptReadByte(ctx);
	u8 field = ScriptReadByte(ctx);
	switch (mode) {
		case SET_MON_DATA_MODE_READ_CONSTANT:
			data = ScriptReadWord(ctx);
			data_ptr = &data;
			break;
		case SET_MON_DATA_MODE_READ_VARS:
			data = VarGet(ScriptReadHalfword(ctx)) | (VarGet(ScriptReadHalfword(ctx)) << 16);
			data_ptr = &data;
			break;
		case SET_MON_DATA_MODE_READ_CONST_PTR:
			data_ptr = (u32 *) ScriptReadWord(ctx);
			break;
		default:
			return false;
	}

	struct Pokemon *mon = GetMonToModify(monNum);
	if (field == MON_DATA_NATURE) {
		 SetMonNature(mon, (u8) data);
	} else {
		SetMonData(mon, field, data_ptr);
	}
	CalculateMonStats(mon);
	return false;
}

bool8 ScrCmd_CreateMon(struct ScriptContext *ctx)
{
	struct Pokemon *mon = GetMonToModify(ScriptReadByte(ctx));
	u16 species = VarGet(ScriptReadHalfword(ctx));
	u8 level = ScriptReadByte(ctx);
	u8 fixedIV = ScriptReadByte(ctx);
	u8 hasFixedPersonality = ScriptReadByte(ctx);
	u32 fixedPersonality = ScriptReadWord(ctx);
	u8 otIdType = ScriptReadByte(ctx);
	u32 fixedOtId = ScriptReadWord(ctx);

	CreateMon(mon, species, level, fixedIV, hasFixedPersonality, fixedPersonality, otIdType, fixedOtId);
	return false;
}


enum {
	BUFFERED_MON_ACTION_GIVE,
	BUFFERED_MON_ACTION_TRADE,
};

static u8 GiveMonAsItIs(struct Pokemon *mon)
{
	u8 sentToPc;

	if (gPlayerPartyCount < 6) {
		CopyMon(&gPlayerParty[gPlayerPartyCount], mon, sizeof(*mon));
		gPlayerPartyCount++;
		sentToPc = 0;
	} else {
		sentToPc = SendMonToPC(mon);
	}

	if (sentToPc == 0 || sentToPc == 1) {
		u16 nationalDexNum = SpeciesToNationalPokedexNum(GetMonData(mon, MON_DATA_SPECIES, 0));
		GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
		GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
	}

	return sentToPc;
}

// bufferedmondoaction ACTION
bool8 ScrCmd_BufferedMonDoAction(struct ScriptContext *ctx)
{
	u8 action = ScriptReadByte(ctx);
	u8 met_location;
	struct Pokemon *mon = &gEnemyParty[0];

	switch (action) {
		case BUFFERED_MON_ACTION_GIVE:
			gSpecialVar_Result = GiveMonAsItIs(mon);
			break;
		case BUFFERED_MON_ACTION_TRADE:
			met_location = 0xFF;
			gSpecialVar_0x8005 = 0;
			SetMonData(mon, MON_DATA_MET_LOCATION, &met_location);
			Special_TradeEnemyMon();
			ScriptContext1_Stop();
			return true;	
	}

	return false;
}



// varrandom VAR_NUM
bool8 SrcCmd_VarRandom(struct ScriptContext *ctx)
{
	u16 *ptr = GetVarPointer(ScriptReadHalfword(ctx));
	*ptr = (u16) __umodsi3(Random(), *ptr + 1);
	return false;
}


