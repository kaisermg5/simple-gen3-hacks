
#include <global.h>
#include <script.h>
#include <sprite.h>
#include <malloc.h>
#include <decompress.h>
#include <script_context_extension.h>
#include <event_data.h>

extern struct CompressedSpriteSheet gMonFrontPicTable[];
extern struct CompressedSpritePalette gMonPaletteTable[];


static void InitOamData(struct OamData *oam, u8 size, s16 x, s16 y, u8 priority)
{
	oam->y = y;
	oam->affineMode = 0;
	oam->objMode = 0;
	oam->mosaic = 0;
	oam->bpp = 0;
	oam->shape = 0;
	oam->x = x;
	oam->matrixNum = 0;
	oam->size = size;
	oam->tileNum = 0;
	oam->priority = priority;
}

static struct SpriteTemplate *AllocNewTemplate(struct OamData *oam, u16 tileTag, u16 palTag)
{
	struct SpriteTemplate *template =(struct SpriteTemplate *) AllocZeroed(sizeof(*template));
	template->tileTag = tileTag;
	template->paletteTag = palTag;
	template->oam = oam;
    template->anims = gDummySpriteAnimTable;
    template->images = 0;
    template->affineAnims = gDummySpriteAffineAnimTable;
    template->callback = SpriteCallbackDummy;
	return template;
}


// loadsprite INDEX SIZE IMG_PTR PAL_PTR X Y PRIORITY
bool8 SrcCmd_LoadSprite(struct ScriptContext *ctx)
{
	struct ScriptContextExtension *ctxExt = GetScriptConTextExtension(ctx);
	
	u8 index = ScriptReadByte(ctx);
	u8 size = ScriptReadByte(ctx);
	const u8 *imgPtr = (const u8 *) ScriptReadWord(ctx);
	const u16 *palPtr = (const u16 *) ScriptReadWord(ctx);
	s16 x = (s16) ScriptReadHalfword(ctx);
	s16 y = (s16) ScriptReadHalfword(ctx);
	u8 priority = ScriptReadByte(ctx);

	struct CompressedSpriteSheet spriteSheet = {
		.data = imgPtr,
		.size = 32 * (1 << (2 * size)), 
		.tag = ctxExt->tagToUse
	};

	struct SpritePalette paletteSheet = {
		.data = palPtr,
		.tag = ctxExt->tagToUse
	};

	struct OamData oam;
	InitOamData(&oam, size, x, y, priority);

	struct SpriteTemplate *template = AllocNewTemplate(&oam, ctxExt->tagToUse, ctxExt->tagToUse);

	LoadCompressedObjectPic(&spriteSheet);
	LoadSpritePalette(&paletteSheet);
	
	UpdateSpriteLoaded(ctxExt, index);
	ctxExt->spriteIds[index] = CreateSprite(template, x, y, priority);
	ctxExt->tagToUse++;

	return FALSE;
}

enum {
	SPRITE_TYPE_FRONT,
};


bool8 SrcCmd_LoadMonSprite(struct ScriptContext *ctx)
{
	struct ScriptContextExtension *ctxExt = GetScriptConTextExtension(ctx);
	struct OamData oam;
	

	struct SpriteTemplate *template;
	
	u8 index = ScriptReadByte(ctx);
	u8 spriteType = ScriptReadByte(ctx);
	u16 species = VarGet(ScriptReadHalfword(ctx));
	s16 x = (s16) VarGet(ScriptReadHalfword(ctx));
	s16 y = (s16) VarGet(ScriptReadHalfword(ctx));
	u8 priority = ScriptReadByte(ctx);
	if (spriteType == SPRITE_TYPE_FRONT) {
		InitOamData(&oam, 3, x, y, priority);
		template = AllocNewTemplate(&oam, gMonFrontPicTable[species].tag, gMonPaletteTable[species].tag);

		LoadCompressedObjectPic(&gMonFrontPicTable[species]);
		LoadCompressedObjectPalette(&gMonPaletteTable[species]);
	} else { return FALSE; }
	
	UpdateSpriteLoaded(ctxExt, index);
	ctxExt->spriteIds[index] = CreateSprite(template, x, y, priority);

	return FALSE;
}

// unloadsprite INDEX
bool8 SrcCmd_UnloadSprite(struct ScriptContext *ctx)
{
	struct ScriptContextExtension *ctxExt = GetScriptConTextExtension(ctx);
	u8 index = ScriptReadByte(ctx);
	UnloadSprite(ctxExt, index);
	return FALSE;
}
