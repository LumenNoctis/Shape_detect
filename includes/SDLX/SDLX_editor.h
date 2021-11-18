#ifndef SDLX_EDITOR_H
# define SDLX_EDITOR_H

# include "SDLX.h"

typedef struct SDLX_Editor_TextureFile// the whole file
{
	char *path;
	char *name;
	SDL_Texture *tex;
}			SDLX_Editor_TextureFile;

typedef struct SDLX_Editor_Texture //Part of a texture file
{
	SDLX_Editor_TextureFile *file;
	SDL_Rect	*src;
	SDL_Rect	_src;
}				SDLX_Editor_Texture;

// typedef struct SDLX_Editor_DisplayTexs //This to display in UI if make this editor more advanced
// {
// 	SDLX_Editor_Texture *tex;
// 	SDLX_Sprite sprite;

// }				SDLX_Editor_DisplayTexs;

typedef struct SDLX_Editor_Elem // Button to be placed on screen
{
	SDLX_Editor_Texture *tex;
	SDLX_Sprite sprite;
	char name[20];
	int texNum;
}			SDLX_Editor_Elem;

int SDLX_EditorRun(void);
void SDLX_EditorInit(void);
//From command line for now...
int SDLX_EditorAddTextureFile(char *name, char *path);
int SDLX_EditorCutTexture(SDLX_Editor_TextureFile *texF, SDL_Rect *src, char *name);
int SDLX_EditorSwap_ElemTex(SDLX_Editor_Elem *elem, int newTex);
int SDLX_EditorSave(char *path);
int SDLX_EditorLoad(char *path);
int SDLX_EditorGenerate(char *path);

#endif
