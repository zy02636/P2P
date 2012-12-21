#ifndef STD_H
#define STD_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#endif

#ifndef WIN32_SERVER
#define WIN32_SERVER
#include <winsock2.h>
#endif//WIN32

#ifndef COM_H
#define COM_H

#include "common.h"

#endif

#define SERVER_PORT 5208 //ÕìÌý¶Ë¿Ú

void startWin32Server();