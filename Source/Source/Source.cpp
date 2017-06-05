#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

int StrToInt(char *ss) {
	int i = 0, ii = 0;
	char *s = ss;
	while (*s) {
		ii = i;
		if (*s == '0') { i = 10 * i + 0; }
		if (*s == '1') { i = 10 * i + 1; }
		if (*s == '2') { i = 10 * i + 2; }
		if (*s == '3') { i = 10 * i + 3; }
		if (*s == '4') { i = 10 * i + 4; }
		if (*s == '5') { i = 10 * i + 5; }
		if (*s == '6') { i = 10 * i + 6; }
		if (*s == '7') { i = 10 * i + 7; }
		if (*s == '8') { i = 10 * i + 8; }
		if (*s == '9') { i = 10 * i + 9; }
		s++;
		//if (ii > i) return -1;
	}
	return i;
}

int intLi(char s[1000]) {
	int w = 0, dot = 0;
	char chisla[11] = "0123456789";
	while (s[w]) {
		for (int i = 0;i < 10;i++) {
			if (s[w] == chisla[i]) goto yes;
			if (s[w] == '.') {
				dot++;
				if (dot == 2) return 0;
				goto yes;
			}
		}
		return 0;
	yes:
		w++;
	}
	return 1;
}

void code() {
  FILE *fin = fopen("input.txt", "r");
  FILE *fout = fopen("output.txt", "w");
  char c, cc;
  int mas[8], mass[8], word1[8], word2[8], j = 0, k = 0;
  while (!feof(fin)) {
    c = fgetc(fin);
    cc = c;
    if (feof(fin)) break;
    //if (c == '\n') { fprintf(fout, "\n"); continue; }
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

    for (int i = 0;i < 8;i++) {
      word1[i] = 0;
      word2[i] = 0;
    }

    word1[2] = mas[0];
    word1[4] = mas[1];
    word1[5] = mas[2];
    word1[6] = mas[3];
    word2[0] = mas[4];
    word2[1] = mas[5];
    word2[2] = mas[6];
    word2[3] = mas[7];
    word1[0] = (word1[2] + word1[4] + word1[6] + word2[0] + word2[2]) % 2;
    word1[1] = (word1[2] + word1[5] + word1[6] + word2[1] + word2[2]) % 2;
    word1[3] = (word1[4] + word1[5] + word1[6] + word2[3]) % 2;
    word1[7] = (word2[0] + word2[1] + word2[2] + word2[3]) % 2;

  for(int i=0;i<8;i++){
  	fprintf(fout, "%d", word1[i]);
  } 
  for(int i=0;i<8;i++){
  	fprintf(fout, "%d", word2[i]);
  }
  
  }

  fclose(fin);
  fclose(fout);
}

void decode() {
  FILE *fin = fopen("output.txt", "r");
  FILE *fout = fopen("Hamming.txt", "w");
  char c1 = 'n', c2 = 'n', cc;
  int mas[8], mass[8], hmas[8], word1[8], word2[8], haming[4], j = 0, k = 0;
  while (!feof(fin)) {
    c1 = fgetc(fin);
    if (feof(fin)) break;
    if(c1=='1') word1[0]=1; else word1[0]=0;
    for (int i = 1;i < 8;i++) {
    c1 = fgetc(fin);
    if(c1=='1') word1[i]=1; else word1[i]=0;
    }
    for (int i = 0;i < 8;i++) {
      c1 = fgetc(fin);
    if(c1=='1') word2[i]=1; else word2[i]=0;
    }
  

    haming[0] = (word1[2] + word1[4] + word1[6] + word2[0] + word2[2]) % 2;
    haming[1] = (word1[2] + word1[5] + word1[6] + word2[1] + word2[2]) % 2;
    haming[2] = (word1[4] + word1[5] + word1[6] + word2[3]) % 2;
    haming[3] = (word2[0] + word2[1] + word2[2] + word2[3]) % 2;

    int number = 0;
    if (haming[0] != word1[0]) number += 1;
    if (haming[1] != word1[1]) number += 2;
    if (haming[2] != word1[3]) number += 4;
    if (haming[3] != word1[7]) number += 8;

    number--;
    if (number > -1) {

      mas[0] = word1[2];
      mas[1] = word1[4];
      mas[2] = word1[5];
      mas[3] = word1[6];
      mas[4] = word2[0];
      mas[5] = word2[1];
      mas[6] = word2[2];
      mas[7] = word2[3];
      c1 = 0;
      int step = 1;
      for (int y = 7;y >= 0;y--) {
        c1 += mas[y] * step;
        step *= 2;
      }
    

      if (number < 8) { if (word1[number] == 0) word1[number] = 1; else word1[number] = 0; }
      else {
        number -= 8;
        if (word2[number] == 0) word2[number] = 1; else word2[number] = 0;
      }
    }

    mas[0] = word1[2];
    mas[1] = word1[4];
    mas[2] = word1[5];
    mas[3] = word1[6];
    mas[4] = word2[0];
    mas[5] = word2[1];
    mas[6] = word2[2];
    mas[7] = word2[3];

    c1 = 0;
    int step = 1;
    for (int y = 7;y >= 0;y--) {
      c1 += mas[y] * step;
      step *= 2;
    }
    fputc(c1, fout);
  }

  fclose(fin);
  fclose(fout);
}

int main()
{
	int com = -1,	 // Number of command? I don't remember
		u = -20,	 // Just needed
		kolKom = 2;	 // Count of commands
	char s[1000];
	while (1) {
		com = -1;
		u = -20;
		printf("Input command:\n");
		printf("0 - Code\n");
		printf("1 - Decode\n");
		s[0] = '\0'; gets_s(s, 999);
		u = StrToInt(s);
		while ((intLi(s) == 0) || (u == -1)) {
		repeat:;
			printf("Try again:");
			s[0] = '\0'; gets_s(s, 999);
			u = StrToInt(s);
		}
		system("cls");
		if (u > kolKom - 1) goto repeat; else
		if (u == 0) code();
		if (u == 1) decode();
		u = -1;
	}

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
