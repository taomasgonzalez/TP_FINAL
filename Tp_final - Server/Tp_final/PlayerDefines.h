#pragma once

#define WALKING_PICS	(10)				// cantidad de imagenes del personaje caminando
#define JUMPING_PICS	(1)
#define ATTACKING_PICS	(10)
#define IDLE_PICS		(10)
#define FALLING_PICS	(1)
#define PUSHING_PICS	(10)
#define DYING_PICS		(10)

#define MOVE_RATIO	(0.25)							// segundos que tarda el personaje en recorrer un bloque
#define VELOCITY_X (BLOCK_SIZE/(FPS*MOVE_RATIO))	// pixeles que va a recorrer el personaje por cada frame de refresco
#define MOVE_RATIO_PUSHED	(1.0)
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

#define FILE_TOM_WALKING	("JK_P_Gun__Run_00")			// nombre generico de los archivos .png de tom caminando
#define FILE_TOM_JUMPING	("JK_P_Gun__Jump_00")
#define FILE_TOM_IDLE		("JK_P_Gun__Idle_00")
#define FILE_TOM_ATTACKING	("JK_P_Gun__Attack_00")
#define FILE_TOM_FALLING	("JK_P_Gun__Jump_00")
#define FILE_TOM_PUSHING	("JK_P_Gun__Hurt_00")
#define FILE_TOM_DYING		("JK_P__Die_00")

#define FILE_NICK_WALKING	("E_E_Gun__Run_000_00")			// nombre generico de los archivos png de tom caminando
#define FILE_NICK_JUMPING	("E_E_Gun__Jump_00")
#define FILE_NICK_IDLE		("E_E_Gun__Idle_00")
#define FILE_NICK_ATTACKING	("E_E_Gun__Attack_00")
#define FILE_NICK_FALLING	("E_E_Gun__Jump_00")
#define FILE_NICK_PUSHING	("E_E_Gun__Hurt_00")
#define FILE_NICK_DYING		("E_E__Die_00")