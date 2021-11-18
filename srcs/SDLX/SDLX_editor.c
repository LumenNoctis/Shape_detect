# include "SDLX.h"
# include "SDLX_editor.h"
# include "SDLX_UI.h"

# define INIT_FILE_CT 1
# define INIT_TEXT_CT 2
# define INIT_ELEM_CT 5

static SDLX_Display display;

static SDLX_Editor_TextureFile *tfiles;
static SDLX_Editor_Texture *textures;
static SDLX_Editor_Elem *elems;
static SDLX_GUIElem	GUI_AddFile;
static SDLX_GUIElem	GUI_AddElem;
static SDLX_GUIElem	GUI_AddTexture;
static SDLX_Sprite	S_AddFile;
static SDLX_Sprite	S_AddElem;
static SDLX_Sprite	S_AddTexture;

static int	nfiles;
static int	ntex;
static int	nsprites;
static int	maxfiles;
static int	maxtex;
static int	maxsprites;



//From command line for now...
int SDLX_EditorAddTextureFile(char *name, char *path)
{
	if (nfiles >= maxfiles)
	{
		maxfiles *= 2;
		tfiles = SDL_realloc(tfiles, sizeof(SDLX_Editor_TextureFile) * nfiles);
	}
	tfiles[nfiles].tex = SDLX_LoadTexture(path, &display);
	tfiles[nfiles].name = name;
	tfiles[nfiles].path = path;
	nfiles++;

	return 0;
}

int SDLX_Editor_ButtonFile(SDLX_GUIElem *elem)
{
	SDL_Log("File Pressed");
}
int SDLX_Editor_ButtonElem(SDLX_GUIElem *elem)
{
	SDL_Log("Elem Pressed");
}
int SDLX_Editor_ButtonTexture(SDLX_GUIElem *elem)
{
	SDL_Log("Texture pressed");
}

int SDLX_EditorCutTexture(SDLX_Editor_TextureFile *texF, SDL_Rect *src, char *name);

// int SDLX_EditorSwap_ElemTex(SDLX_Editor_Elem *elem, int dir)
// {
// 	elem.
// }

int SDLX_EditorSave(char *path);
int SDLX_EditorLoad(char *path);
int SDLX_EditorGenerate(char *path);

int SDLX_EditorRun(void)
{
	SDLX_Input input;

	input = SDLX_InputGet();
	return 0;

}

void SDLX_EditorInit()
{
	SDL_Texture *EditorTex;

	display.background = NULL;
	display.window = SDL_CreateWindow(
				"SDLX Editor",
				, y,
				w, h,
				flags
	);
	display.renderer = SDL_CreateRenderer(display.window, -1, 0);
	EditorTex = SDLX_LoadTexture("includes/SDLX/editorAssets/buttons.png", display);
	tfiles		= SDL_calloc(INIT_FILE_CT , sizeof(SDLX_Editor_TextureFile));
	textures	= SDL_calloc(INIT_TEXT_CT , sizeof(SDLX_Editor_Texture));
	elems 		= SDL_calloc(INIT_ELEM_CT , sizeof(SDLX_Editor_Texture));

	SDLX_SpriteCreate(&S_AddFile, EditorTex, &(SDL_Rect){0, 0, 32, 32}, &(SDL_Rect){100, 100, 64, 64});

	SDLX_GUIElem_Create(&GUI_AddFile, &S_AddFile, "File",
		SDLX_DefaultGUISelect, SDLX_NullGUIFunc, SDLX_NullGUIFunc,SDLX_NullGUIFunc, SDLX_Editor_ButtonFile);
	// SDLX_GUIElem_Create(&GUI_AddTexture, &S_AddTexture, "Texture",
	// 	SDLX_DefaultGUISelect, SDLX_NullGUIFunc, SDLX_NullGUIFunc, SDLX_NullGUIFunc, SDLX_Editor_ButtonTexture);
	// SDLX_GUIElem_Create(&GUI_AddElem, &S_AddElem, "Elem",
	// 	SDLX_DefaultGUISelect, SDLX_NullGUIFunc, SDLX_NullGUIFunc, SDLX_NullGUIFunc, SDLX_Editor_ButtonElem);

	GUI_AddFile.active = SDLX_TRUE;
}
