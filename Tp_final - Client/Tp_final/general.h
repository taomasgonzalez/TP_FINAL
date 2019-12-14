#pragma once

#define DEBUG
#ifdef DEBUG

#endif // DEBUG

#define _WIN32_WINNT 0x0501

#define DISPLAY_H 1500
#define DISPLAY_W 1600
#define BLOCK_SIZE (50)		// pixeles en X e Y que tiene un bloque de pantalla
#define SCREEN_H (16*BLOCK_SIZE)
#define SCREEN_W (12*BLOCK_SIZE)

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

	int fil;
	int col;
};