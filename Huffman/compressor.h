#ifndef _COMPRESSOR_H
#define _COMPRESSOR_H

#include <stdio.h>
#include "queue.h"
#include <string.h>

void compress(FILE * fin, FILE * fout);
Tree * makeTree(int * table);						//��������� ������ �������� �� ������ ������� ������
int * analyzeText(FILE * fin);									//��������� ������� ������
int encodeTree(Tree * tree, FILE * fout);						//�������� ������ � ����, ���������� 0 ���� ������ ������� �� ����� ������ ���, � 1 ���� �����
void writeByte(FILE * fout, unsigned char byte);				//���������� ���� � ������� bitWriter(...)
int bitWriter(FILE * fout, unsigned char bit);					//��������� ����, ���� �� ��������� ����, ����� ���� ���������� ���. ���������� 0 ���� ���� �� ��� �������, � 1 ���� ���
unsigned char writeLeftBits(FILE * fout);								//��������� 0 �� ����� �����, ���������� ���������� ���������� ���
void makeCodeTable(Tree * tree, char * code, char ** table);	//��������� ������� ����� �� ������ ������
void fillTable(unsigned char ** t);										//��������� ������� ������� ��������
unsigned char countBits(int * f, char ** c);								//������� ���������� ��� �� ������ ��������� �����
int countTreeBits(Tree * tree);						//������� ���������� ��� �� ������ ������
#endif