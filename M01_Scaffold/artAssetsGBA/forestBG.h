
//{{BLOCK(forestBG)

//======================================================================
//
//	forestBG, 512x256@4, 
//	+ palette 256 entries, not compressed
//	+ 249 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 512 + 7968 + 4096 = 12576
//
//	Time-stamp: 2024-11-24, 14:19:55
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FORESTBG_H
#define GRIT_FORESTBG_H

#define forestBGTilesLen 7968
extern const unsigned short forestBGTiles[3984];

#define forestBGMapLen 4096
extern const unsigned short forestBGMap[2048];

#define forestBGPalLen 512
extern const unsigned short forestBGPal[256];

#endif // GRIT_FORESTBG_H

//}}BLOCK(forestBG)
