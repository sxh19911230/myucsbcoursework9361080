#include <stdio.h>
#include <stdlib.h>
int main(int args, char** argv){ 
  FILE *pFile;
  int i, rotateNum, charCount[26];
  char c;

  if (args != 3) {
    printf("usage: %s <file> <rotate #>", argv[0]);
    exit(0);
  }

  rotateNum = atoi(argv[2]);
  for (i = 0; i < 26; ++i)
    charCount[i] = 0;

  pFile = fopen(argv[1], "rb");

  if (!pFile) {
    fputs("File error", stderr);
    exit(1);
  }

  c = fgetc(pFile);
  do {
    if (c >= 'a' && c <='z'){
      putchar((c - 'a' + rotateNum) % 26 + 'a'); 
    } else if (c >='A' && c <='Z') {
      putchar((c - 'A' + rotateNum) % 26 + 'A');
    } else putchar(c);
    c = fgetc(pFile);
  } while (c != EOF);
  fclose(pFile);

  return 0;
  
}
