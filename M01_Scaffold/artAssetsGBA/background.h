
//{{BLOCK(background)

//======================================================================
//
//	background, 512x256@4, 
//	+ palette 256 entries, not compressed
//	+ 249 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 512 + 7968 + 4096 = 12576
//
//	Time-stamp: 2024-11-24, 14:18:42
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKGROUND_H
#define GRIT_BACKGROUND_H

#define backgroundTilesLen 7968
extern const unsigned short backgroundTiles[3984];

#define backgroundMapLen 4096
extern const unsigned short backgroundMap[2048];

#define backgroundPalLen 512
extern const unsigned short backgroundPal[256];

#endif // GRIT_BACKGROUND_H

//}}BLOCK(background)
