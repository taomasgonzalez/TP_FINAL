#include <stdio.h>
#include <stdlib.h>
#include "parseCmdLine.h"

int parseCmdLine(int argc, char *argv[], pCallback infoAnalysis, void *userData) {

	int stringNumber = 0;		//numero de string de los parametros recibidos por linea de comando
	int errorParser = 0;		//numero de opciones y parametros recibidos en caso de que NO haya error, numero menor a cero en caso de error
	int nextStringNumber = stringNumber + 1; 		//string proximo al que esta en la posicion stringNumber.
	for (stringNumber = 1; (stringNumber < argc) && (errorParser >= 0); stringNumber++) {
		nextStringNumber = stringNumber + 1;
		if (argv[stringNumber][0] == '-') {
			//primer caracter del dato ingresado que no es el nombre del programa (por eso empieza en 1 el for). Me fijo si corresponde a una opciòn

			if (argv[stringNumber][1] == '\0')		//me fijo el segundo caracter del dato ingresado. Si es el terminador, entonces no hay key para la opciòn				
				errorParser = NO_KEY_ERROR;

			else if (nextStringNumber == argc)		//me fijo si llegue a la ùltima palabra y por lo tanto me falta un valor para la opciòn		
				errorParser = NO_VALUE_ERROR;

			else if (!(*infoAnalysis)(&argv[stringNumber][1], argv[nextStringNumber], userData))  	//envio sin el guiòn!!!	
				errorParser = PROCESSING_ERROR;
			
			stringNumber++;			//me avanzo una para saltear al valor que ya tomè									

		}

		else {
			if (!(*infoAnalysis)(NULL, argv[stringNumber], userData))	//chequeo si hubo error al procesar el parametro.				
				errorParser = PARAMETERS_ERROR;
		}



		if (errorParser >= 0)
			errorParser++;				//aumento el contador en caso de que no haya habido error, independientemente de si recibi un parametro o una opciòn.

	}

	return errorParser;
}