
//{{BLOCK(clouds)

//======================================================================
//
//	clouds, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 162 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 5184 + 2048 = 7744
//
//	Time-stamp: 2024-11-25, 12:46:24
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CLOUDS_H
#define GRIT_CLOUDS_H

#define cloudsTilesLen 5184
extern const unsigned short cloudsTiles[2592];

#define cloudsMapLen 2048
extern const unsigned short cloudsMap[1024];

#define cloudsPalLen 512
extern const unsigned short cloudsPal[256];

#endif // GRIT_CLOUDS_H

//}}BLOCK(clouds)
