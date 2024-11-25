
//{{BLOCK(letters)

//======================================================================
//
//	letters, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 5 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 160 + 2048 = 2720
//
//	Time-stamp: 2024-11-24, 15:05:23
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LETTERS_H
#define GRIT_LETTERS_H

#define lettersTilesLen 160
extern const unsigned short lettersTiles[80];

#define lettersMapLen 2048
extern const unsigned short lettersMap[1024];

#define lettersPalLen 512
extern const unsigned short lettersPal[256];

#endif // GRIT_LETTERS_H

//}}BLOCK(letters)
