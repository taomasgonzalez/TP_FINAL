#pragma once

#define MOVE_RATIO_PURPLE (0.3)												// segundos que demora cada monstruo en pasar de bloque
#define VEL_PURPLE (BLOCK_SIZE/(FPS*MOVE_RATIO_PURPLE))						// pixeles que recorreran por refresco de pantalla
#define MOVE_RATIO_FATTY (0.3)
#define VEL_FATTY (BLOCK_SIZE/(FPS*MOVE_RATIO_FATTY))
#define MOVE_RATIO_CRAZY (0.2)
#define VEL_CRAZY (BLOCK_SIZE/(FPS*MOVE_RATIO_CRAZY))

#define WALKING_PICS_PURPLE 8
#define WALKING_PICS_FATTY 8
#define WALKING_PICS_CRAZY 8
#define JUMPING_PICS_PURPLE 8
#define JUMPING_PICS_FATTY 1
#define JUMPING_PICS_CRAZY 1
#define ATTACKING_PICS_PURPLE 8
#define ATTACKING_PICS_FATTY 8
#define ATTACKING_PICS_CRAZY 8
#define TRAPPED_1_PICS_PURPLE 1
#define TRAPPED_1_PICS_FATTY	1
#define TRAPPED_1_PICS_CRAZY	1
#define TRAPPED_2_PICS_PURPLE 1
#define TRAPPED_2_PICS_FATTY	1
#define TRAPPED_2_PICS_CRAZY	1
#define TRAPPED_3_PICS_PURPLE 1
#define TRAPPED_3_PICS_FATTY	1
#define TRAPPED_3_PICS_CRAZY	1
#define IDLE_PICS_PURPLE	10
#define IDLE_PICS_FATTY		8
#define IDLE_PICS_CRAZY		8
#define FALLING_PICS_PURPLE	8
#define FALLING_PICS_FATTY	1
#define FALLING_PICS_CRAZY	1
#define DYING_PICS_PURPLE	8
#define DYING_PICS_FATTY	8
#define DYING_PICS_CRAZY	8


#define FOLDER_ENEMY	("enemies")
#define FOLDER_PURPLE	("PURPLE")
#define FOLDER_FATTY	("FATTY")
#define FOLDER_CRAZY	("CRAZY")

#define FOLDER_WALKING	("WALKING")		
#define FOLDER_JUMPING	("JUMPING")
#define FOLDER_IDLE		("IDLE")
#define FOLDER_TRAPPED_1	("TRAPPED_1")
#define FOLDER_TRAPPED_2	("TRAPPED_2")
#define FOLDER_TRAPPED_3	("TRAPPED_3")
#define FOLDER_ATTACKING	("ATTACKING")
#define FOLDER_FALLING		("FALLING")
#define FOLDER_DYING		("DYING")

#define FILE_PURPLE_WALKING	("__Bandit02_Walk_00")
#define FILE_PURPLE_JUMPING	("__Bandit02_JumpUP_00")
#define FILE_PURPLE_ATTACKING	("__Bandit02_Attack_00")
#define FILE_PURPLE_TRAPPED_1	("__Bandit02_Hurt_00")
#define FILE_PURPLE_TRAPPED_2	("__Bandit02_Hurt_00")
#define FILE_PURPLE_TRAPPED_3	("__Bandit02_Hurt_00")
#define FILE_PURPLE_IDLE	("__Bandit02_Idle_00")
#define FILE_PURPLE_FALLING	("__Bandit02_FallDown_00")
#define FILE_PURPLE_DYING	("__Bandit02_Die_00")

#define FILE_FATTY_WALKING	("2D_GOBLIN__Run_00")
#define FILE_FATTY_JUMPING	("2D_GOBLIN__Jump_Up_00")
#define FILE_FATTY_ATTACKING	("2D_GOBLIN__Attack_00")
#define FILE_FATTY_TRAPPED_1	("2D_GOBLIN__Hurt_00")
#define FILE_FATTY_TRAPPED_2	("2D_GOBLIN__Hurt_00")
#define FILE_FATTY_TRAPPED_3	("2D_GOBLIN__Hurt_00")
#define FILE_FATTY_IDLE		("2D_GOBLIN__Idle_Blinking_00")
#define FILE_FATTY_FALLING	("2D_GOBLIN__Fall_Down_00")
#define FILE_FATTY_DYING	("2D_GOBLIN__Die_00")

#define FILE_CRAZY_WALKING	("2D_SM02_Run_00")
#define FILE_CRAZY_JUMPING	("2D_SM02_JumpUp_00")
#define FILE_CRAZY_ATTACKING	("2D_SM02_Attack_00")
#define FILE_CRAZY_TRAPPED_1	("2D_SM02_Hurt_00")
#define FILE_CRAZY_TRAPPED_2	("2D_SM02_Hurt_00")
#define FILE_CRAZY_TRAPPED_3	("2D_SM02_Hurt_00")
#define FILE_CRAZY_IDLE		("2D_SM02_Idle_00")
#define FILE_CRAZY_FALLING	("2D_SM02_FallDown_00")
#define FILE_CRAZY_DYING	("2D_SM02_Die_00")



//											MACROS PARA LA BOLA


#define MOVE_RATIO	(0.3)											// segundos que le tarda al proyectil recorrer un casillero
#define VEL_X_INBALL	(BLOCK_SIZE/(FPS*MOVE_RATIO))
#define MOVE_RATIO_PUSHED	(1.0)
#define VEL_PUSHED_INBALL	(BLOCK_SIZE/(FPS*MOVE_RATIO_PUSHED))
#define TIME_TRAPPED	(3.0)										// segundos con el enemigo atrapado PARCIALMENTE en nieve
#define TICKS_TRAPPED	(TIME_TRAPPED*FPS)							// ticks con el enemigo atrapado PARCIALMENTE en la nieve

#define IDLE_PICS_BALL	1
#define MOVING_PICS_BALL	16											// cantidad de imagenes de cada una para saber repetir el ciclo
#define PUSHING_PICS_BALL	16
#define FALLING_PICS_BALL	16
#define DESTRUCTION_PICS_BALL	18

#define FOLDER_BALL	("ball")

#define FOLDER_IDLE_BALL			("IDLE")
#define FOLDER_PUSHING_BALL		("PUSHING")
#define FOLDER_MOVING_BALL		("MOVING")
#define FOLDER_FALLING_BALL		("FALLING")
#define FOLDER_DESTRUCTION_BALL		("DESTRUCTION")

#define FILE_IDLE_BALL			("tile00")
#define FILE_MOVING_BALL			("tile00")
#define FILE_PUSHING_BALL		("tile00")
#define FILE_FALLING_BALL		("tile00")
#define FILE_DESTRUCTION_BALL	("Blue Ring Explosion")