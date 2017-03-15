#ifndef _COMPRESSOR_H
#define _COMPRESSOR_H

#include <stdio.h>
#include "queue.h"

void compress(FILE * fin, FILE * fout);
Tree * makeTree(FILE * fin);
int * analyzeText(FILE * fin);
void encodeTree(Tree * tree, FILE * fout);
void writeByte(FILE * fout, unsigned char byte);
void bitWriter(FILE * fout, unsigned char bit);

#endif