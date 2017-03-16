#define _CRT_SECURE_NO_WARNINGS

#include "compressor.h"
#include "decompressor.h"

int main()
{
	FILE * fin = fopen("in.txt","r");
	FILE * fout = fopen("out.txt", "w");
	if (!fin || !fout)
		printf("No such file in directory or couldn't create output file");

	char type;
	fscanf(fin, "%c\n", &type);
	if (type)
		switch (type) {
		case 'd': 
			decompress(fin, fout);
			break;
		case 'c':
			compress(fin, fout);
			break;
		default:
			fprintf(fin, "Wrong input. d or c was expected to be the first symbol");
			break;
	}
	return 0;
}