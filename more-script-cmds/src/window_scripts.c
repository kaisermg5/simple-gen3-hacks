

#include <global.h>
#include <script.h>
#include <malloc.h>
#include <text.h>
#include <menu.h>
#include <window.h>
#include <text_window.h>
#include <palette.h>
#include <script_context_extension.h>
#include <string_util.h>

bool8 SrcCmd_CreateWindow(struct ScriptContext *ctx)
{
	struct WindowTemplate winTemplate;
	struct ScriptContextExtension *ctxExt = GetScriptConTextExtension(ctx);

	//struct WindowTemplate *winTemplate = (struct WindowTemplate *) AllocZeroed(sizeof(*winTemplate));
	u8 index = ScriptReadByte(ctx);
	u8 x = ScriptReadByte(ctx);
    u8 y = ScriptReadByte(ctx);
    u8 width = ScriptReadByte(ctx);
    u8 height = ScriptReadByte(ctx);
	SetWindowTemplateFields(&winTemplate, 0, x, y, width, height, 0xF, ctxExt->textTilesCount);
	ctxExt->textTilesCount += width * height;
	u8 winId = AddWindow(&winTemplate);
	FillWindowPixelBuffer(winId, 0);
	PutWindowTilemap(winId);
	SetWindowBorderStyle(winId, FALSE, 0x214, 0xe);
#ifdef BPEE
	LoadPalette(sub_8098758(gSaveBlock2Ptr->optionsWindowFrameType)->pal, 0xe0, 0x20);
#endif
	ctxExt->windowIds[index] = winId;
	return FALSE;
}

//PrintTextOnWindow(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 speed, void (*callback)(struct TextSubPrinter *, u16))
bool8 SrcCmd_PrintTextOnWindow(struct ScriptContext *ctx)
{
	struct ScriptContextExtension *ctxExt = GetScriptConTextExtension(ctx);

	u8 winId = ctxExt->windowIds[ScriptReadByte(ctx)];
	const u8 *str = (const u8 *) ScriptReadWord(ctx);
	u8 x = ScriptReadByte(ctx);
	u8 y = ScriptReadByte(ctx);

	// Getting rid of the rom prefix "0x08..." 
	if ((((u32) str) << 5) < (0x3 << 5)) {
		str = sScriptStringVars[((u32) str) & 0xFF];
	} 

	StringExpandPlaceholders(gStringVar4, str);
	PrintTextOnWindow(winId, 1, gStringVar4, x * 8, y * 8, 0, NULL);
	return FALSE;
}

enum {
	WINDOW_ACTION_REMOVE,
	WINDOW_ACTION_UPDATE,
	WINDOW_ACTION_CLEAR,
};

static void clearWindowAndBorderStyle(u8 winId)
{
	ClearWindowTilemap(winId);
	sub_8198070(winId, FALSE);
}

bool8 ScrCmd_WindowDoAction(struct ScriptContext *ctx)
{
	struct ScriptContextExtension *ctxExt = GetScriptConTextExtension(ctx);

	u8 winId = ctxExt->windowIds[ScriptReadByte(ctx)];
	u8 action = ScriptReadByte(ctx);
	switch (action) {
		case WINDOW_ACTION_REMOVE:
			clearWindowAndBorderStyle(winId);
			RemoveWindow(winId);
			break;
		case WINDOW_ACTION_UPDATE:
			CopyWindowToVram(winId, 3);
			break;
		case WINDOW_ACTION_CLEAR:
			clearWindowAndBorderStyle(winId);
	}
	return FALSE;
}
