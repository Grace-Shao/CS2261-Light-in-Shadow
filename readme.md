## How to play the game
- GOAL: escape from all the monsters and make it outside
- press START to go to the next screen or pause/unpause the game
- use WASD or up down left right, to point your flashlight and freeze monsters (limited batterylife!).
    - monsters will come in all directions!!!
- use B and A to move left and right
- collect certain keys to unlock different doors (press R shoulder to use the key, if it doesn't work, wrong key)
    - different doors lead to different floors!!


## What is finished about the game so far
- The flashlight functionality (had to do some big brain thinking here)
- enemies randomly choose a part of the screen to lurk out, will randomly attack player (30% chance of attacking)
- player can collect keys
- every 5 clicks of the flashlight decreases the flashlight ui bar until u run out (have ~35 clicks in total)
- flashlight follows player
- when flashlight collides with enemy, it "freezes the enemy"
- going through a door leads you to the next lvl or a prev lvl
- enemy eyes show even in the darkness and flickers (how cool is that!!)
- keys can unlock doors and collected keys are displayed in the ui
- large bg, all levels are done but the art in each lvl is questionable lol
- parallax title screen
- audio (theme and button clicks)
- tilemodification in lvl1 and 2 (can see cracks in the walls forming) (see vfx.c)
- palette modification in lvl 2 (can see cracks and other black stuff flashing red, also forest bg flashes red) (see vfx.c)
- instructions done
- 2 animated sprites (player and monster)

## Cheat
- Toggling L shoulder and R shoulder will reveal the entire bg (no need for flashlight anymore)
- ^not shown in demo

## Bugs
- The background does wrap around on the left and right sides, 
- but hopefully this makes a trippy visual effect and the player will learn they cannot walk over