
#include <global.h>
#include <script.h>
#include <sprite.h>


struct ScriptContextExtension {
	u16 tagToUse;
	u8 spriteIds[16];
	u16 spritesLoadedFlags;
};

static void UnloadSprite(struct ScriptContextExtension *ctxExt, u8 index);

static inline void SetScriptConTextExtension(struct ScriptContext *ctx, struct ScriptContextExtension *ctxExt)
{
	ctx->data[3] = ctxExt;
}

static inline struct ScriptContextExtension * GetScriptConTextExtension(struct ScriptContext *ctx)
{
	return (struct ScriptContextExtension *) ctx->data[3];
}

static u32 IsSpriteLoaded(struct ScriptContextExtension *ctxExt, u32 index)
{
	return ctxExt->spritesLoadedFlags & (1 << index);
}

bool8 SrcCmd_ExtendScripts(struct ScriptContext *ctx)
{
	struct ScriptContextExtension *ctxExt = (struct ScriptContextExtension *) AllocZeroed(sizeof(*ctxExt));
	SetScriptConTextExtension(ctx, ctxExt);
	ctxExt->tagToUse = 0xd1a5;
	return false;
}

bool8 SrcCmd_DistendScripts(struct ScriptContext *ctx)
{
	struct ScriptContextExtension *ctxExt = GetScriptConTextExtension(ctx);
	for (int i = 0; i < 16; i++) {
		if (IsSpriteLoaded(ctxExt, i)) {
			UnloadSprite(ctxExt, i);
		}
	}
	Free(ctxExt);
	return false;
}


static void UnloadSprite(struct ScriptContextExtension *ctxExt, u8 index) {
	u8 realIndex = ctxExt->spriteIds[index];
	struct SpriteTemplate *template = (struct SpriteTemplate *) gSprites[realIndex].template;
	DestroySpriteAndFreeResources(&gSprites[realIndex]);
	Free(template);
	ctxExt->spritesLoadedFlags &= ~(1 << index);
}

// loadsprite INDEX SIZE IMG_PTR PAL_PTR X Y PRIORITY
bool8 SrcCmd_LoadSprite(struct ScriptContext *ctx)
{
	struct ScriptContextExtension *ctxExt = GetScriptConTextExtension(ctx);
	
	u8 index = ScriptReadByte(ctx);
	u8 size = ScriptReadByte(ctx);

	struct CompressedSpriteSheet spriteSheet = {
		.data = (const u8 *) ScriptReadWord(ctx),
		.size = 32 * (1 << (2 * size)), 
		.tag = ctxExt->tagToUse
	};

	struct SpritePalette paletteSheet = {
		.data = (const u16 *) ScriptReadWord(ctx),
		.tag = ctxExt->tagToUse
	};

	s16 x = (s16) ScriptReadHalfword(ctx);
	s16 y = (s16) ScriptReadHalfword(ctx);
	u8 priority = ScriptReadByte(ctx);
	struct OamData oam = {
		.y = y,
		.affineMode = 0,
		.objMode = 0,
		.mosaic = 0,
		.bpp = 0,
		.shape = 0,
		.x = x,
		.matrixNum = 0,
		.size = size,
		.tileNum = 0,
		.priority = priority,
	};
	

	struct SpriteTemplate *template = (struct SpriteTemplate *) AllocZeroed(sizeof(*template));
	template->tileTag = ctxExt->tagToUse;
	template->paletteTag = ctxExt->tagToUse;
	template->oam = &oam;
    template->anims = gDummySpriteAnimTable;
    template->images = 0;
    template->affineAnims = gDummySpriteAffineAnimTable;
    template->callback = SpriteCallbackDummy;

	LoadCompressedObjectPic(&spriteSheet);
	LoadSpritePalette(&paletteSheet);
	
	if (IsSpriteLoaded(ctxExt, index)) {
		UnloadSprite(ctxExt, index);
	}
	ctxExt->spriteIds[index] = CreateSprite(template, x, y, priority);
	ctxExt->spritesLoadedFlags |= 1 << index;
	ctxExt->tagToUse++;

	return false;
}

// unloadsprite INDEX
bool8 SrcCmd_UnloadSprite(struct ScriptContext *ctx)
{
	struct ScriptContextExtension *ctxExt = GetScriptConTextExtension(ctx);
	u8 index = ScriptReadByte(ctx);
	UnloadSprite(ctxExt, index);
	return false;
}


