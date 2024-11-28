
//{{BLOCK(lightDown)

//======================================================================
//
//	lightDown, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 14 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 448 + 2048 = 3008
//
//	Time-stamp: 2024-11-27, 21:44:27
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LIGHTDOWN_H
#define GRIT_LIGHTDOWN_H

#define lightDownTilesLen 448
extern const unsigned short lightDownTiles[224];

#define lightDownMapLen 2048
extern const unsigned short lightDownMap[1024];

#define lightDownPalLen 512
extern const unsigned short lightDownPal[256];

#endif // GRIT_LIGHTDOWN_H

//}}BLOCK(lightDown)
