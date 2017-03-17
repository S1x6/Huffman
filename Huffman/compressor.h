#ifndef _COMPRESSOR_H
#define _COMPRESSOR_H

#include <stdio.h>
#include "queue.h"
#include <string.h>

void compress(FILE * fin, FILE * fout);
Tree * makeTree(int * table);						//формирует дерево Хаффмана на основе таблицы частот
int * analyzeText(FILE * fin);									//формирует таблицу частот
int encodeTree(Tree * tree, FILE * fout);						//кодирует дерево в файл, возвращает 0 если дерево записно не целым числом бит, и 1 если целым
void writeByte(FILE * fout, unsigned char byte);				//выписывает байт с помощью bitWriter(...)
int bitWriter(FILE * fout, unsigned char bit);					//сохраняет биты, пока не накопится байт, после чего выписывает его. Возвращает 0 если байт не был выписан, и 1 если был
unsigned char writeLeftBits(FILE * fout);								//дописыает 0 до конца байта, возвращает количество дописанных бит
void makeCodeTable(Tree * tree, char * code, char ** table);	//формирует таблицу кодов на основе дерева
void fillTable(unsigned char ** t);										//заполняет таблицу пустыми строками
unsigned char countBits(int * f, char ** c);								//считает количество бит на запись исходного файла
int countTreeBits(Tree * tree);						//считает количество бит на запись дерева
#endif