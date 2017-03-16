#include "decompressor.h"

void decompress(FILE * fin, FILE * fout)
{
	Tree * tree = NULL;
	int i = 0;
	char bit;
	char placeholderNumber;
	if (!fread(&placeholderNumber, 1, 1, fin))
		return;
	for (; i < placeholderNumber; i++) {
		readBit(&bit, fin);
	}
	tree = readTree(fin, tree);
	while (!feof(fin))
	{
		decode(tree, fin, fout);
	}
}

void decode(Tree * tree,FILE * fin, FILE * fout)
{
	char bit;
	Tree * tmp = tree;
	if (tmp->left == NULL)
		fwrite(&(tmp->key), 1, 1, fout);

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
	char bit;
	char byte;
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

char readBit(char * bit, FILE * fin)
{
	static char byte;
	static char currentBit = 0;

	if (currentBit == 0)
		fread(&byte, sizeof(char), 1, fin);
	*bit = (byte & (1 << (7 - currentBit))) > 0;
	currentBit++;
	if (currentBit == 8) {
		currentBit = 0;
	}
	return !feof(fin);
}

char readByte(FILE * fin)
{
	char res = 0, bit;
	int i = 0;
	for (; i < 8; i++) {
		readBit(&bit, fin);
		res |= bit << (7 - i);
	}
	return res;
}
