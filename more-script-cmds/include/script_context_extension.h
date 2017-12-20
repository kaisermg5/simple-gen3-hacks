#ifndef SCRIPT_CONTEX_EXTENSION_H

#define SCRIPT_CONTEX_EXTENSION_H

struct ScriptContextExtension {
	u16 tagToUse;
	u8 spriteIds[16];
	u16 spritesLoadedFlags;
	u8 windowIds[8];
	u16 textTilesCount;
};

static inline void SetScriptConTextExtension(struct ScriptContext *ctx, struct ScriptContextExtension *ctxExt)
{
	ctx->data[3] = ctxExt;
}

static inline struct ScriptContextExtension * GetScriptConTextExtension(struct ScriptContext *ctx)
{
	return (struct ScriptContextExtension *) ctx->data[3];
}

void UpdateSpriteLoaded(struct ScriptContextExtension *ctxExt, u8 index);
void UnloadSprite(struct ScriptContextExtension *ctxExt, u8 index);



extern u8 * const sScriptStringVars[];

#endif
