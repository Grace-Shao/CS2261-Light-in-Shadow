
//{{BLOCK(winScreen)

//======================================================================
//
//	winScreen, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 204 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 6528 + 2048 = 9088
//
//	Time-stamp: 2024-12-06, 16:17:24
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_WINSCREEN_H
#define GRIT_WINSCREEN_H

#define winScreenTilesLen 6528
extern const unsigned short winScreenTiles[3264];

#define winScreenMapLen 2048
extern const unsigned short winScreenMap[1024];

#define winScreenPalLen 512
extern const unsigned short winScreenPal[256];

#endif // GRIT_WINSCREEN_H

//}}BLOCK(winScreen)
