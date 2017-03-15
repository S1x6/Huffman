#include "compressor.h"

void compress(FILE * fin, FILE * fout)
{
	Tree * q = makeTree(fin);
	encodeTree(q, fout);
	
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

void bitWriter(FILE * fout, unsigned char bit) 
{
	static char currentBit = 0;
	static unsigned char byte = 0;

	byte |= bit << (7 - currentBit);
	currentBit++;
	if (currentBit == 8) {
		currentBit = 0;
		fwrite(&byte, sizeof(char), 1, fout);
		byte = 0;
	}
}

void encodeTree(Tree * tree, FILE * fout)
{
	if (tree->left) {
		bitWriter(fout, 1);
		encodeTree(tree->left, fout);
		bitWriter(fout, 1);
		encodeTree(tree->right, fout);
	}
	else
	{
		bitWriter(fout, 0);
		writeByte(fout, tree->key);
	}

	
}

void writeByte(FILE * fout, unsigned char byte)
{
	char i = 0;
	for (; i < 8; i++) {
		bitWriter(fout, byte & (1 << (7 - i)) );
	}
}