#ifndef _COMPRESSOR_H
#define _COMPRESSOR_H

#include <stdio.h>
#include "queue.h"
#include <string.h>

void compress(FILE * fin, FILE * fout);
Tree * makeTree(FILE * fin);									//формирует дерево ’аффмана на основе таблицы частот
int * analyzeText(FILE * fin);									//формирует таблицу частот
int encodeTree(Tree * tree, FILE * fout);						//кодирует дерево в файл, возвращает 0 если дерево записно не целым числом бит, и 1 если целым
void writeByte(FILE * fout, unsigned char byte);				//выписывает байт с помощью bitWriter(...)
int bitWriter(FILE * fout, unsigned char bit);					//сохран€ет биты, пока не накопитс€ байт, после чего выписывает его. ¬озвращает 0 если байт не был выписан, и 1 если был
void writeLeftBits(FILE * fout);								//дописыает 0 до конца байта
void makeCodeTable(Tree * tree, char * code, char ** table);	//формирует таблицу кодов на основе дерева
void fillTable(char ** t);
#endif