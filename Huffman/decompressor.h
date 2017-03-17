#ifndef _DECOMPRESSOR_H
#define _DECOMPRESSOR_H

#include <stdio.h>
#include "queue.h"

void decompress(FILE * fin, FILE * fout);
unsigned char readBit(unsigned char * bit, FILE * fin);
Tree * readTree(FILE * fin, Tree * tree);
unsigned char readByte(FILE * fin);
void decode(Tree * tree, FILE * fin, FILE * fout);


#endif