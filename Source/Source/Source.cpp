#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void code() {
	FILE *fin = fopen("input.txt", "r");
	FILE *fout = fopen("output.txt", "w");
	char c = 'n', cc;
	int mas[8], mass[8], control[8], j = 0, k = 0;
	while (!feof(fin)) {
		c = fgetc(fin);
		cc = c;
		if (feof(fin)) break;
		if (c == '\n') { fprintf(fout, "\n"); continue; }
		j = 0;
		while (c > 0) {
			mass[j++] = c % 2;
			c = c / 2;
		}
		for (int ii = 0;ii < 8;ii++) {
			mas[ii] = 0;
		}
		for (int i = 0;i < j;i++) {
			mas[i + 8 - j] = mass[j - 1 - i];
		}

		for (int i = 0;i < 8;i++) control[i] = 0;
		control[0] = (mas[0] + mas[2] + mas[4] + mas[6]) % 2;
		control[1] = (mas[1] + mas[2] + mas[5] + mas[6]) % 2;
		control[2] = (mas[3] + mas[4] + mas[5] + mas[6]) % 2;
		control[3] = mas[7];
		control[4] = 0;
		control[5] = 0;
		control[6] = 0;
		control[7] = 0;

		fprintf(fout, "%c", cc);
		cc = 0;
		int step = 1;
		for (int y = 7;y >= 0;y--) {
			cc += control[y] * step;
			step *= 2;
		}
		fprintf(fout, "%c", cc);
	}

	fclose(fin);
	fclose(fout);
}

void decode() {

	FILE *fin = fopen("output.txt", "r");
	FILE *fout = fopen("Hamming.txt", "w");
	char c = 'n', cc;
	int mas[8], mass[8], hmas[8], control[8], haming[4], j = 0, k = 0;
	while (!feof(fin)) {
		c = fgetc(fin);
		if (feof(fin)) break;
		if (c == '\n') { fprintf(fout, "\n"); continue; }
		cc = fgetc(fin);
		if (feof(fin)) break;
		j = 0;
		while (c > 0) {
			mass[j++] = c % 2;
			c = c / 2;
		}
		for (int ii = 0;ii < 8;ii++) {
			mas[ii] = 0;
		}
		for (int i = 0;i < j;i++) {
			mas[i + 8 - j] = mass[j - 1 - i];
		}
	

		haming[0] = (mas[0] + mas[2] + mas[4] + mas[6]) % 2;
		haming[1] = (mas[1] + mas[2] + mas[5] + mas[6]) % 2;
		haming[2] = (mas[3] + mas[4] + mas[5] + mas[6]) % 2;
		haming[3] = mas[7];

		j = 0;
		while (cc > 0) {
			mass[j++] = cc % 2;
			cc = cc / 2;
		}
		for (int ii = 0;ii < 8;ii++) {
			hmas[ii] = 0;
		}
		for (int i = 0;i < j;i++) {
			hmas[i + 8 - j] = mass[j - 1 - i];
		}
		for (int i = 0;i < 4;i++) {
			control[i] = hmas[i];
		}


		int number = 0;
		if (haming[0] != control[0]) number += 1;
		if (haming[1] != control[1]) number += 2;
		if (haming[2] != control[2]) number += 4;
		if (haming[3] != control[3]) number += 8;

		if (number > 0) { number = (number % 8) + 1; if (mas[number - 1] == 0) mas[number - 1] = 1; else mas[number - 1] = 0; }

		c = 0;
		int step = 1;
		for (int y = 7;y >= 0;y--) {
			c += mas[y] * step;
			step *= 2;
		}
		fprintf(fout, "%c", c);
	}

	fclose(fin);
	fclose(fout);
}

int main()
{
	code();
	decode();
    return 0;
}




/*
Coding to binaries
j = 0;
while (c > 0) {
mass[j++] = c % 2;
c = c / 2;
}
for (int ii = 0;ii < 8;ii++) {
mas[ii] = 0;
}
for (int i = 0;i < j;i++) {
mas[i + 8 - j] = mass[j - 1 - i];
}


for (int y = 0;y < 8;y++) printf("%d", mas[y]);
printf(" - ");
c = 0;


Decoding from binaries
int step = 1;
for (int y = 7;y >= 0;y--) {
c += mas[y] * step;
step *= 2;
}
*/