#pragma once

#define MOVE_RATIO_PURPLE (0.3)												// segundos que demora cada monstruo en pasar de bloque
#define VEL_PURPLE (BLOCK_SIZE/(FPS*MOVE_RATIO_PURPLE))						// pixeles que recorreran por refresco de pantalla
#define MOVE_RATIO_FATTY (0.3)
#define VEL_FATTY (BLOCK_SIZE/(FPS*MOVE_RATIO_FATTY))
#define MOVE_RATIO_CRAZY (0.2)
#define VEL_CRAZY (BLOCK_SIZE/(FPS*MOVE_RATIO_CRAZY))

#define WALKING_PICS_PURPLE 10
#define WALKING_PICS_FATTY 20
#define WALKING_PICS_CRAZY 20
#define JUMPING_PICS_PURPLE 20
#define JUMPING_PICS_FATTY 20
#define JUMPING_PICS_CRAZY 20
#define ATTACKING_PICS_PURPLE NULL
#define ATTACKING_PICS_FATTY 20
#define ATTACKING_PICS_CRAZY NULL
#define TRAPPED_PICS_PURPLE NULL
#define TRAPPED_PICS_FATTY	NULL
#define TRAPPED_PICS_CRAZY	NULL
#define IDLE_PICS_PURPLE	NULL
#define IDLE_PICS_FATTY		NULL
#define IDLE_PICS_CRAZY		NULL
#define FALLING_PICS_PURPLE	NULL
#define FALLING_PICS_FATTY	NULL
#define FALLING_PICS_CRAZY	NULL
#define DYING_PICS_PURPLE	NULL
#define DYING_PICS_FATTY	NULL
#define DYING_PICS_CRAZY	NULL


#define FOLDER_ENEMY	("enemies")
#define FOLDER_PURPLE	("PURPLE")
#define FOLDER_FATTY	("FATTY")
#define FOLDER_CRAZY	("CRAZY")

#define FOLDER_WALKING	("WALKING")		
#define FOLDER_JUMPING	("JUMPING")
#define FOLDER_IDLE		("IDLE")
#define FOLDER_TRAPPED	("TRAPPED")
#define FOLDER_ATTACKING	("ATTACKING")
#define FOLDER_FALLING		("FALLING")
#define FOLDER_DYING		("DYING")

#define FILE_PURPLE_WALKING	("Sonic Running-F")
#define FILE_PURPLE_JUMPING	("Super Mario Running-F")
#define FILE_PURPLE_ATTACKING	("Explosion 2-F")
#define FILE_PURPLE_TRAPPED	("Explosion 1-F")
#define FILE_PURPLE_IDLE	("tomIdle-F")
#define FILE_PURPLE_FALLING	("homerdance-F")
#define FILE_PURPLE_DYING	("")

#define FILE_FATTY_WALKING	("fattyWalk")
#define FILE_FATTY_JUMPING	("fattyJump")
#define FILE_FATTY_ATTACKING	("fattyAttack")
#define FILE_FATTY_TRAPPED	("fattyTrapped")
#define FILE_FATTY_IDLE		("fattyIdle")
#define FILE_FATTY_FALLING	("fattyFall")
#define FILE_FATTY_DYING	("fattyDie")

#define FILE_CRAZY_WALKING	("crazyWalk")
#define FILE_CRAZY_JUMPING	("carzyJump")
#define FILE_CRAZY_ATTACKING	("crazyAttack")
#define FILE_CRAZY_TRAPPED	("crazyTrap")
#define FILE_CRAZY_IDLE		("crazyIdle")
#define FILE_CRAZY_FALLING	("crazyFall")
#define FILE_CRAZY_DYING	("crazyDie")
