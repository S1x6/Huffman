#define _CRT_SECURE_NO_WARNINGS

#include "compressor.h"
#include "decompressor.h"

void copyFile(FILE * in, FILE * out);

int main()
{
	FILE * fin = fopen("in.txt", "rb");
	FILE * fout = fopen("out.txt", "wb");
	FILE * fcopy = fopen("in_copy.txt", "wb");
	if (!fin || !fout){
		printf("No such file in directory or couldn't create output file");
		return 0;
	}
	
	char type;
	fscanf(fin, "%c\n", &type);
	if (type)
		switch (type) {
		case 'd':
			decompress(fin, fout);
			break;
		case 'c':
			//copyFile(fin, fcopy);
			fseek(fin, 3, SEEK_SET);
			compress(fin, fout);
			break;
		default:
			fprintf(fin, "Wrong input. d or c was expected to be the first symbol");
			break;
	}
	return 0;
}

void copyFile(FILE * in, FILE * out)
{
	char a, c = 0;
	c = fread(&c, 1, 1, in);
	while (c){
		fwrite(&a, 1, 1, out);
		c = fread(&a, 1, 1, in);
	}
}
