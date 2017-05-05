#include <stdio.h>
#include <stdlib.h>
int main(int args, char** argv){ 
  FILE *pFile;
  int n, i, total, charCount[12][26];
  char c;
  for (n = 0; n < 12; ++n)
  for (i = 0; i < 26; ++i)
    charCount[n][i] = 0;

  pFile = fopen(argv[1], "rb");

  if (!pFile) {
    fputs("File error", stderr);
    exit(1);
  }

  total = 0;
  do {
    c = fgetc(pFile);
    if (c >='A' && c <= 'Z')
      charCount[total++%12][c-'A']++;
  } while (c != EOF);
  fclose(pFile);

 for (n = 0; n < 12; n++) {
  printf("%i:\n",n);
  for (i = 0; i < 10; ++i)
    printf("%c\t",97 + i);
  printf("\n");
  for (i = 0; i < 10; ++i)
    printf("%i\t",charCount[n][i]);
  printf("\n\n");
  for (i = 10; i < 20; ++i)
    printf("%c\t",97 + i);
  printf("\n");
  for (i = 10; i < 20; ++i)
    printf("%i\t",charCount[n][i]);
  printf("\n\n");
  for (i = 20; i < 26; ++i)
    printf("%c\t",97 + i);
  printf("\n");
  for (i = 20; i < 26; ++i)
    printf("%i\t",charCount[n][i]);
  printf("\n\n");

}
  return 0;
  
}
