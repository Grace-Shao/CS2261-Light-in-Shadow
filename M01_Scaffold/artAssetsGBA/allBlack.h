
//{{BLOCK(allBlack)

//======================================================================
//
//	allBlack, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 2 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 64 + 2048 = 2624
//
//	Time-stamp: 2024-11-25, 19:51:16
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ALLBLACK_H
#define GRIT_ALLBLACK_H

#define allBlackTilesLen 64
extern const unsigned short allBlackTiles[32];

#define allBlackMapLen 2048
extern const unsigned short allBlackMap[1024];

#define allBlackPalLen 512
extern const unsigned short allBlackPal[256];

#endif // GRIT_ALLBLACK_H

//}}BLOCK(allBlack)
