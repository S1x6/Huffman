#include "decompressor.h"

void decompress(FILE * fin, FILE * fout)
{
	Tree * tree = NULL;
	int i = 0;
	unsigned char bit;
	unsigned char read;
	unsigned char placeholderNumber;
	if (!fread(&placeholderNumber, 1, 1, fin))
		return;
	for (; i < placeholderNumber; i++) {
		readBit(&bit, fin);
	}
	tree = readTree(fin, tree);

	if (!tree)
		return;

	while (!feof(fin))
	{
		read = 1;
		if (!tree->left)
			read = readBit(&bit, fin);
		if (read)
			decode(tree, fin, fout
			);
	}
}

void decode(Tree * tree,FILE * fin, FILE * fout)
{
	unsigned char bit;
	Tree * tmp = tree;
	if (tmp->left == NULL) {
		fwrite(&(tmp->key), 1, 1, fout);
		return;
	}

	while (readBit(&bit, fin)) {
		if (bit) {
			tmp = tmp->right;
		}
		else tmp = tmp->left;
		if (tmp->left == NULL) {
			fwrite(&(tmp->key), 1, 1, fout);
			break;
		}
	}
}

Tree * readTree(FILE * fin, Tree * tree)
{
	unsigned char bit;
	unsigned char byte;
	if (readBit(&bit, fin)) {
		tree = malloc(sizeof(Tree));
		if (bit) {
			tree->left = readTree(fin, tree->left);
			tree->right = readTree(fin, tree->right);
			return tree;
		}
		else {
			byte = readByte(fin);
			tree->key = byte;
			tree->left = NULL;
			tree->right = NULL;
			return tree;
		}
	}
	else
		return NULL;
}

unsigned char readBit(unsigned char * bit, FILE * fin)
{
	static unsigned char byte;
	static unsigned char currentBit = 0;

	if (currentBit == 0)
		fread(&byte, sizeof(char), 1, fin);
	*bit = (byte & (1 << (7 - currentBit))) > 0;
	currentBit++;
	if (currentBit == 8) {
		currentBit = 0;
	}
	return !feof(fin);
}

unsigned char readByte(FILE * fin)
{
	unsigned char res = 0, bit;
	int i = 0;
	for (; i < 8; i++) {
		readBit(&bit, fin);
		res |= bit << (7 - i);
	}
	return res;
}
