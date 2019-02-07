#pragma once

#define WALKING_PICS	(12)				// cantidad de imagenes del personaje caminando
#define JUMPING_PICS	(10)
#define ATTACKING_PICS	(3)
#define IDLE_PICS		(1)
#define FALLING_PICS	(1)
#define PUSHING_PICS	(5)
#define DYING_PICS		(5)

#define MOVE_RATIO	(0.3)							// segundos que tarda el personaje en recorrer un bloque
#define VELOCITY_X (BLOCK_SIZE/(FPS*MOVE_RATIO))	// pixeles que va a recorrer el personaje por cada frame de refresco
#define MOVE_RATIO_PUSHED	(0.5)
#define VEL_PUSHED	(BLOCK_SIZE/(FPS*MOVE_RATIO_PUSHED))

#define FOLDER_CHARA	("characters")				// carpeta donde estan contenidas todas las imagenes de los personajes
#define FOLDER_TOM		("TOM")						// carpeta para cada personaje en particular
#define FOLDER_NICK		("NICK")

#define FOLDER_WALKING	("WALKING")					// carpetas que vas a contener imagenes de una categoria
#define FOLDER_JUMPING	("JUMPING")
#define FOLDER_IDLE		("IDLE")
#define FOLDER_ATTACKING	("ATTACKING")
#define FOLDER_FALLING		("FALLING")
#define FOLDER_PUSHING		("PUSHING")
#define FOLDER_DYING		("DYING")

#define FILE_TOM_WALKING	("Super Mario Running-F")			// nombre generico de los archivos .png de tom caminando
#define FILE_TOM_JUMPING	("homerdance-F")
#define FILE_TOM_IDLE		("tomIdle-F")
#define FILE_TOM_ATTACKING	("Explosion 2-F")
#define FILE_TOM_FALLING	("Sonic Running-F")
#define FILE_TOM_PUSHING	("")
#define FILE_TOM_DYING		("")

#define FILE_NICK_WALKING	("nickWalk-F")			// nombre generico de los archivos png de tom caminando
#define FILE_NICK_JUMPING	("nickJump-F")
#define FILE_NICK_IDLE		("nickIdle-F")
#define FILE_NICK_ATTACKING	("nickAttack-F")
#define FILE_NICK_FALLING	("nickFall-F")
#define FILE_NICK_PUSHING	("nickPush-F")
#define FILE_NICK_DYING		("nickDie-F")
