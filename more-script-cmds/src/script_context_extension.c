
#include <global.h>
#include <script.h>
#include <malloc.h>
#include <script_context_extension.h>

u8 * const sScriptStringVars[] =
{
    gStringVar1,
    gStringVar2,
    gStringVar3,
};


bool8 SrcCmd_ExtendScripts(struct ScriptContext *ctx)
{
	struct ScriptContextExtension *ctxExt = (struct ScriptContextExtension *) AllocZeroed(sizeof(*ctxExt));
	SetScriptConTextExtension(ctx, ctxExt);
	ctxExt->tagToUse = 0xd1a5;
	ctxExt->textTilesCount = 1;
	return FALSE;
}

static inline u32 IsSpriteLoaded(struct ScriptContextExtension *ctxExt, u32 index)
{
	return ctxExt->spritesLoadedFlags & (1 << index);
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
	return FALSE;
}


void UpdateSpriteLoaded(struct ScriptContextExtension *ctxExt, u8 index)
{
	if (IsSpriteLoaded(ctxExt, index)) {
		UnloadSprite(ctxExt, index);
	}
	ctxExt->spritesLoadedFlags |= 1 << index;
}


void UnloadSprite(struct ScriptContextExtension *ctxExt, u8 index) {
	u8 realIndex = ctxExt->spriteIds[index];
	struct SpriteTemplate *template = (struct SpriteTemplate *) gSprites[realIndex].template;
	DestroySpriteAndFreeResources(&gSprites[realIndex]);
	Free(template);
	ctxExt->spritesLoadedFlags &= ~(1 << index);
}









