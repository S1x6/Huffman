#ifndef _DECOMPRESSOR_H
#define _DECOMPRESSOR_H

#include <stdio.h>
#include "queue.h"

void decompress(FILE * fin);
char readBit(char * bit, FILE * fin);
Tree * readTree(FILE * fin, Tree * tree);
char readByte(FILE * fin);


#endif