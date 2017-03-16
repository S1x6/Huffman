#define _CRT_SECURE_NO_WARNINGS
#include "compressor.h"

void compress(FILE * fin, FILE * fout)
{
	char ** table = malloc(256 * sizeof(char*));
	int isRead, i = 0;
	char * code = calloc(1, 1), isByte, leftBits = 0;
	unsigned char ch = 0;
	int * frequency_table = analyzeText(fin);
	Tree * tree = makeTree(fin, frequency_table);
	fillTable(table);
	makeCodeTable(tree, code, table);
	leftBits = 8 - (countTreeBits(tree) + countBits(frequency_table, table) ) % 8;
	writeByte(fout, leftBits);
	for (; i < leftBits; i++)
		bitWriter(fout, 0);
	encodeTree(tree, fout);
	fseek(fin, 3, SEEK_SET);
	do {
		isRead = (int) fread(&ch, 1, 1, fin);
		if (isRead)
		{
			i = 0;
			for (; i < strlen(table[ch]); i++) {
				isByte = bitWriter(fout, table[ch][i] - '0');
			}
		}
	} while (isRead);
}

int countTreeBits(Tree * tree)
{
	int num = 0;
	if (tree->left) {
		num += 1;
		num += countTreeBits(tree->left);
		num += countTreeBits(tree->right);
		return num % 8;
	}
	else
	{
		num += 1;
		return num % 8;
	}
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

char countBits(int * f, char ** c)
{
	int i = 0;
	char res = 0;
	for (; i < 256; i++) {
		if (!f[i])
			continue;
		res = (res + (f[i] * strlen(c[i])) % 8 ) % 8;
	}
	return res;
}

void fillTable(char ** t)
{
	int i = 0;
	for (; i < 256; i++) {
		t[i] = calloc(256, sizeof(char));
	}
}

Tree * makeTree(FILE * fin, int * table)
{
	int i = 0;
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