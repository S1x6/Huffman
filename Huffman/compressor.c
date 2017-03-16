#define _CRT_SECURE_NO_WARNINGS
#include "compressor.h"

void compress(FILE * fin, FILE * fout)
{
	char ** table = malloc(256 * sizeof(char*));
	Tree * tree = makeTree(fin);
	int isRead, i = 0;
	char * code = calloc(1, 1), ch = 0, isByte, leftBits = 0;
	writeByte(fout, 0); //резевируем первый байт в файле для числа дописанных бит
	encodeTree(tree, fout);
	fillTable(table);
	makeCodeTable(tree, code, table);
	fseek(fin, 3, SEEK_SET);
	do {
		isRead = fread(&ch, 1, 1, fin);
		if (isRead)
		{
			i = 0;
			for (; i < strlen(table[ch]); i++) {
				isByte = bitWriter(fout, table[ch][i] - '0');
			}
		}
	} while (isRead);
	if (!isByte)
		leftBits = writeLeftBits(fout);
	fseek(fout, 0, SEEK_SET);
	fwrite(&leftBits, 1, 1, fout); //количество дописанных бит
}

void makeCodeTable(Tree * tree, char * code, char ** table)
{
	if (tree->left)	{
		makeCodeTable(tree->left, strcat(code, "0"), table);
		code[strlen(code) - 1] = 0;
		makeCodeTable(tree->right, strcat(code, "1"),table);
		code[strlen(code) - 1] = 0;
	}
	else
	{
		strcpy(table[tree->key], code);
	}
}

void fillTable(char ** t)
{
	int i = 0;
	for (; i < 256; i++) {
		t[i] = calloc(256, sizeof(char));
	}
}

Tree * makeTree(FILE * fin)
{
	int i = 0;
	int * table = analyzeText(fin);
	Queue * q = malloc(sizeof(q));
	q->head = NULL;
	q->tail = NULL;
	for (; i < 256; i++) {
		if (!table[i])
			continue;
		Tree * tree = (Tree *)malloc(sizeof(Tree));
		tree->key = i;
		tree->left = NULL;
		tree->right = NULL;
		tree->weight = table[i];
		enqueue(q, tree);
	}
	while (q->head != q->tail)
	{
		Tree * a = dequeue(q);
		Tree * b = dequeue(q);
		Tree * new_tree = (Tree *)malloc(sizeof(Tree));
		new_tree->left = a;
		new_tree->right = b;
		new_tree->weight = a->weight + b->weight;
		enqueue(q, new_tree);
	}
	return q->head->value;

}

int * analyzeText(FILE * fin)
{
	unsigned char tmp, read;
	int * table = (int *)calloc(256, sizeof(int));
	do
	{
		read =(char)fread(&tmp, sizeof(char), 1, fin);
		if (!read)
			break;
		table[tmp] += 1;
	} while (1);
	return table;
}

int bitWriter(FILE * fout, unsigned char bit) 
{
	static char currentBit = 0;
	static unsigned char byte = 0;

	byte |= bit << (7 - currentBit);
	currentBit++;
	if (currentBit == 8) {
		currentBit = 0;
		fwrite(&byte, sizeof(char), 1, fout);
		byte = 0;
		return 1;
	}
	return 0;
}

int encodeTree(Tree * tree, FILE * fout)
{
	char ret;
	if (tree->left) {
		ret = bitWriter(fout, 1);
		encodeTree(tree->left, fout);
		//ret = bitWriter(fout, 1);
		encodeTree(tree->right, fout);
		return ret;
	}
	else
	{
		ret = bitWriter(fout, 0);
		writeByte(fout, tree->key);
		return ret;
	}
}

void writeByte(FILE * fout, unsigned char byte)
{
	char i = 0;
	for (; i < 8; i++) {
		bitWriter(fout, (byte & (1 << (7 - i))) != 0 );
	}
}

char writeLeftBits(FILE * fout)
{
	char res = 0;
	while (!bitWriter(fout, 0))
	{
		res++;
	}
	return res + 1;
}