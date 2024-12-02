
//{{BLOCK(forestBG)

//======================================================================
//
//	forestBG, 512x256@4, 
//	+ palette 256 entries, not compressed
//	+ 392 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 512 + 12544 + 4096 = 17152
//
//	Time-stamp: 2024-12-02, 17:57:25
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FORESTBG_H
#define GRIT_FORESTBG_H

#define forestBGTilesLen 12544
extern const unsigned short forestBGTiles[6272];

#define forestBGMapLen 4096
extern const unsigned short forestBGMap[2048];

#define forestBGPalLen 512
extern const unsigned short forestBGPal[256];

#endif // GRIT_FORESTBG_H

//}}BLOCK(forestBG)
