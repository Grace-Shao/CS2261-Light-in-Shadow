## What is finished about the game so far
- The flashlight functionality (had to do some big brain thinking here)
- enemies randomly choose a part of the screen to lurk out, will randomly attack player (25% chance of attacking)
- player can collect keys
- every 5 clicks of the flashlight decreases the flashlight ui bar until u run out
- flashlight follows player
- when flashlight collides with enemy, it "freezes the enemy"
- going through a door leads you to the next lvl
- enemy eyes show even in the darkness and flickers (how cool is that!!)
## Fin in M3
- keys can unlock doors and be displayed in the ui
- large bg, lvl 1 is done
- parallax title screen
- audio
- tilemodification in lvl1 and 2 (can see cracks in the walls forming) (see vfx.c)
- palette modification in lvl 2 (can see cracks and other black stuff turning red) (see vfx.c)
- instructions done


## What still needs to be added
- better level design

## Any bugs you have found
- sometimes when dying, the flashlight turns from black to white

## For our sake, how to play/navigate the game in its current state (and see anything you want us to see)
- the title screen is blank, and click start to transition between start, instructions, pause/unpause, lose/win, back to start
- Button B is walk left, button A is walk right
- WASD is which direction to point the light at, point at an enemy to freeze and kill them
- Try to pick up keys and go through doors (unique keys open certain doors)