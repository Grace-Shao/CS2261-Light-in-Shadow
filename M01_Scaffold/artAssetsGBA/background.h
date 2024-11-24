
//{{BLOCK(background)

//======================================================================
//
//	background, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 73 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 2336 + 2048 = 4896
//
//	Time-stamp: 2024-10-26, 23:18:25
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKGROUND_H
#define GRIT_BACKGROUND_H

#define backgroundTilesLen 2336
extern const unsigned short backgroundTiles[1168];

#define backgroundMapLen 2048
extern const unsigned short backgroundMap[1024];

#define backgroundPalLen 512
extern const unsigned short backgroundPal[256];

#endif // GRIT_BACKGROUND_H

//}}BLOCK(background)
