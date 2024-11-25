#ifndef DOORKEYS_H
#define DOORKEYS_H

#define KEYCOUNT 3
#define DOORCOUNT 5

void initBasicKeys();
void initBasicDoors();
void deactivateAllDoors();
void initDoorsLevel1();
void initDoorsLevel2();
void initKeysLevel1();
void initKeysLevel2();
void keyCollision();
void drawKeys();
void enterDoor();
void drawDoors();

// special key struct that inherits from sprite, w few extra capabilities
typedef struct KEY{
    SPRITE base; // Embed the SPRITE struct
    int isCollected;
} KEY;

typedef struct DOOR{
    SPRITE base; // Embed the SPRITE struct
    int level;
    struct DOOR* leadsTo;
    struct KEY* assignedKey;    
} DOOR;
// needs to be extern to not get "dereferencing pointer to incomplete type 'struct DOOR''

#endif
