#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/* bincmp.c: compara dois arquivos binários, retornando os offsets e as diferenças. 
 *
 * (c) 2024- Renan Birck Pinheiro <renan.birck.pinheiro@gmail.com>
 *
 * USO:  bincmp  arquivo_1  arquivo_2  */

unsigned char does_file_exist(char *file_name) {
	FILE *fp;
	fp = fopen(file_name, "r");
	return(!(fp == NULL));
}

unsigned long get_file_size(char *file_name) {
	// Determina o tamanho de um arquivo.
	
	FILE *fp;
	unsigned long size;

	fp = fopen(file_name, "r");

	if(!does_file_exist(file_name)) { 
		perror("error");
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fclose(fp);

	return size;
}

int main(int argc, char *argv[]) {

	unsigned long fs1 = 0, fs2 = 1;
	unsigned long pos = 0;
	FILE *fp1, *fp2;
	char *fd1, *fd2;

	if(argc != 3) {
		printf("usage: %s file1 file2", argv[0]);
		return 0;
	}

	if(!does_file_exist(argv[1])) {
		printf("%s: %s not found.", argv[0], argv[1]);
		return 132;
	}

	if(!does_file_exist(argv[2])) {
		printf("%s: %s not found.", argv[0], argv[2]);
		return 133;
	}

	fs1 = get_file_size(argv[1]);
	fs2 = get_file_size(argv[2]);

	if(fs1 != fs2) {
		printf("%s: the two files have different sizes! They must be different.", argv[0]);
		return 1;
	} else {
		printf("%s: two files of size %ld\n", argv[0], fs1);
	}

	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");

	fd1 = malloc(sizeof(int) * fs1);
	fd2 = malloc(sizeof(int) * fs2);

	fread(fd1, fs1, 1, fp1);
	fread(fd2, fs2, 1, fp2);

	for(pos = 0; pos < fs1; pos++) {
		if(fd1[pos] != fd2[pos]) {
			printf("%lx %c != %c\n", pos, fd1[pos], fd2[pos]);
		}
	}
}
