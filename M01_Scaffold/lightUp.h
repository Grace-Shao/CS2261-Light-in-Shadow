
//{{BLOCK(lightUp)

//======================================================================
//
//	lightUp, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 14 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 448 + 2048 = 3008
//
//	Time-stamp: 2024-11-07, 12:05:02
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LIGHTUP_H
#define GRIT_LIGHTUP_H

#define lightUpTilesLen 448
extern const unsigned short lightUpTiles[224];

#define lightUpMapLen 2048
extern const unsigned short lightUpMap[1024];

#define lightUpPalLen 512
extern const unsigned short lightUpPal[256];

#endif // GRIT_LIGHTUP_H

//}}BLOCK(lightUp)
