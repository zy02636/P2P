#ifndef STD_H
#define STD_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#endif

#ifndef COM_H
#define COM_H

#include "common.h"

#endif

#ifndef HASHER_H
#define HASHER_H

#include "hasher.h"

#endif
/*
    Splite a file into a collection of segments with defined size, MD5, file MD5
*/
void synthesisFile(char *fileName);