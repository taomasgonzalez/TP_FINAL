#pragma once

#define DEBUG


#define _WIN32_WINNT 0x0501
//
//#define DISPLAY_H 1500
//#define DISPLAY_W 1600
#define BLOCK_SIZE (50)		// pixeles en X e Y que tiene un bloque de pantalla
#define SCREEN_H (16*BLOCK_SIZE)
#define SCREEN_W (12*BLOCK_SIZE)
#define DISPLAY_H SCREEN_W
#define DISPLAY_W SCREEN_H
#define FPS (60.0)

#define WQTY 2 //Cantidad de worms

#define MSJ_BIENVENIDA "BIENVENIDOS AL SIMULADOR \nSE ESTA SIMULANDO UN SERVIDOR \nUSE EL TECLADO PARA ENVIAR EVENTOS Y VEA EN LA PANTALLA LOS CAMBIOS DE ESTADOS\nTODA TECLA QUE NO SEA UNA PRESELECCIONADA SE CONSIDERARA UN EVENTO GARBAGE \n"
#define LISTA_EVENTOS "LA LISTA DE EVENTOS ES: \n B = MOVE_RECIEVED \n C = MOVE SENT \n D = ACK \n E = TIME_OUT \n F = TIME_OUT 2 \n G = QUIT \n H = ERROR \n J = RESET \n K = I_AM_READY \n M = INVALID_ACK_CODE \n N = END_COMMUNICATION \n O = VALID_ACK_CODE \n I = GARBAGE"
#define ESTADO "| EL ESTADO ES = %s"
#define EVENT_ANT "| EL EVENTO ANTERIOR ES = %s"
#define EVENT_ACT "| EVENTO ACTUAL = %s"
#define LAST_ACTION_EXCECUTED "| INFO : %s"

#define ESPERANDOEVENTO "Esperando evento..."

#define PROCESANDOSTR "PROCESANDO... \n"

#define FILA 15
#define COLUMNA 30

#define Initiating_stateSTR "Initiating"

#define Waiting_for_ClientOK_stateSTR "Waiting_for_ClientOK"

#define Finishing_configurationSTR "Finishing_configuration"

#define Looping_stateSTR "Looping"

#define Waiting_to_send_ACK_stateSTR "Waiting_to_send_ACK"

#define Waiting_for_ACK_stateSTR "Waiting_for_ACK"

#define Resending_MOVESTR "Resending_MOVE"

#define Analyzing_ACKSTR "Analyzing_ACK"

#define Sending_ERRORSTR "Sending_ERROR"

#define MAX_NUMBER_OF_MONSTERS 256
#define MAX_NUMBER_OF_PLAYERS 2

struct Position {

	unsigned int fil;
	unsigned int col;
};

std::string event_string[] =  //Events that are usde by the internal function of the program 
{
	"END_OF_TABLE",

	//ACK:
	"ACK",


	//LOCAL_QUIT:Evento de allegro de quit, tiene que ser enviado por networking al otro usuario
	"LOCAL_QUIT",

	//EXTERN_QUIT:Evento de networking de quit
	"EXTERN_QUIT",

	//LOCAL_ACTION: Evento generado por allegro pero no ejecutado por la maquina,falta analizar
	"MOVE",

	//EXTERN_ACTION   Es un MOVE/ATTACK del servidor que llega por networking siendo cliente
	"ATTACK",

	//ACTION_REQUEST   //action request generado por el cliente que no fue chequeado
	"ACTION_REQUEST",

	//ERROR: Evento de software cuando se produce un error interno, diversos origenes
	"ERROR1",

	//NAME_IS: 
	"NAME_IS",

	//NAME:
	"NAME",

	//MAP_IS:
	"MAP_IS",

	//ENEMY_ACTION: El servidor crea una enemy action
	"ENEMY_ACTION",

	//ENEMYS_LOADED: Recibi todos los enemy  action como para poder empezar el juego
	"ENEMYS_LOADED",

	//GAME_START:
	"GAME_START",

	//WE_WON
	"WE_WON",

	//PLAY_AGAIN
	"PLAY_AGAIN",

	//FINISHED_LEVEL
	"FINISHED_LEVEL",

	//GAME_OVER
	"GAME_OVER",

	//START_COMMUNICATION: Evento de software generado cuando se inicilizo todo correctamente, el servidor esta listo para inicilizar
	"START_COMMUNICATION",

	"NO_EVENT",

	//graphic events
	"FPS_TICKED",
	"APPEARED",
	"DISAPPEARED",
	"FINISHED_DRAWING",
	"CHANGE_LEVEL",

	//character events
	"JUMPED",
	"JUMPED_FORWARD",
	"WALKED",
	"ATTACKED",
	"FELL",
	"PUSHED",
	"FINISHED_MOVEMENT",
	"KEEP_MOVING",
	"FINISHED_ATTACK",
	"DIED",

	//player events
	"REVIVED",

	//enemy and proyectiles events
	"GOT_HIT",
	"GOT_SMASHED",

	//enemy events
	"FROZE",
	"UNFROZE",
	"PARTIALLY_UNFROZE",
	"BOUNCE",
	"ROLLING",
	"CHARGING",
	"FINISHED_GRAPH_STEP",
	//RESET
	"RESET"


};

