#ifndef TOUSH_H
#define TOUSH_H

#ifndef STD_H
#define STD_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

#include "filesplitter.h"
#include "filesynthesis.h"
/*
  define a file structure to store meta data, and each 
  file will have at least one segment.
*/
typedef struct File{
    int fileId;
    char fileMD5[32];
    long byteSize;
}File;

/*
  define a segment structure to store meta data.
*/
typedef struct Segment{
    int fileId;
    int segId;
    long byteSize;
    char fileMD5[32];
    char segMD5[32];
}Segment;

#endif