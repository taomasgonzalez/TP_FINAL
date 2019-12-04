#pragma once
#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parseCmdLine.h"
#include <iostream>
#include <string>



/******************
*    TYPEDEF´S    *
******************/

typedef int(*pCallback) (char * key, char * value, void * userdata);

int parseCallback(char *key, char *value, void *userData);
