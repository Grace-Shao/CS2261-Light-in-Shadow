
//{{BLOCK(light)

//======================================================================
//
//	light, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 45 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 1440 + 2048 = 4000
//
//	Time-stamp: 2024-11-04, 21:33:21
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LIGHT_H
#define GRIT_LIGHT_H

#define lightTilesLen 1440
extern const unsigned short lightTiles[720];

#define lightMapLen 2048
extern const unsigned short lightMap[1024];

#define lightPalLen 512
extern const unsigned short lightPal[256];

#endif // GRIT_LIGHT_H

//}}BLOCK(light)
