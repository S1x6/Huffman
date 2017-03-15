#ifndef _COMPRESSOR_H
#define _COMPRESSOR_H

#include <stdio.h>
#include "queue.h"
#include <string.h>

void compress(FILE * fin, FILE * fout);
Tree * makeTree(FILE * fin);									//��������� ������ �������� �� ������ ������� ������
int * analyzeText(FILE * fin);									//��������� ������� ������
int encodeTree(Tree * tree, FILE * fout);						//�������� ������ � ����, ���������� 0 ���� ������ ������� �� ����� ������ ���, � 1 ���� �����
void writeByte(FILE * fout, unsigned char byte);				//���������� ���� � ������� bitWriter(...)
int bitWriter(FILE * fout, unsigned char bit);					//��������� ����, ���� �� ��������� ����, ����� ���� ���������� ���. ���������� 0 ���� ���� �� ��� �������, � 1 ���� ���
void writeLeftBits(FILE * fout);								//��������� 0 �� ����� �����
void makeCodeTable(Tree * tree, char * code, char ** table);	//��������� ������� ����� �� ������ ������
void fillTable(char ** t);
#endif