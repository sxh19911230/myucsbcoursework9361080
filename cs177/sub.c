#include <stdio.h>
#include <stdlib.h>
int main(int args, char** argv){ 
  int i,j,n, charCount[26], max, lastMax;
  char c, *str, *fre, *engFre;
  for (i = 0; i < 26; ++i)
    charCount[i] = 0;

  str = "BOWIACOITSEGATUTELTSIASHOOWIBSPQTIADIOWHQPBOIPQOEPQJACOEPJETEPSETXESPJOECOECTJUTGJEZJDTIPLSEGGTGJCSPTGPOPQTKIOKOAJPJOEPQSPSZZFTESITCITSPTGTRWSZEOXXTSITTEHSHTGJESHITSPCJUJZXSIPTAPJEHXQTPQTIPQSPESPJOEOISELESPJOEAOCOECTJUTGSEGAOGTGJCSPTGCSEZOEHTEGWITXTSITFTPOESHITSPDSPPZTBJTZGOBPQSPXSIXTQSUTCOFTPOGTGJCSPTSKOIPJOEOBPQSPBJTZGSASBJESZITAPJEHKZSCTBOIPQOATXQOQTITHSUTPQTJIZJUTAPQSPPQSPESPJOEFJHQPZJUTJPJASZPOHTPQTIBJPPJEHSEGKIOKTIPQSPXTAQOWZGGOPQJADWPJESZSIHTIATEATXTCSEEOPGTGJCSPTXTCSEEOPCOEATCISPTXTCSEEOPQSZZOXPQJAHIOWEGPQTDISUTFTEZJUJEHSEGGTSGXQOAPIWHHZTGQTITQSUTCOEATCISPTGJPBSISDOUTOWIKOOIKOXTIPOSGGOIGTPISCPPQTXOIZGXJZZZJPPZTEOPTEOIZOEHITFTFDTIXQSPXTASLQTITDWPJPCSEETUTIBOIHTPXQSPPQTLGJGQTITJPJABOIWAPQTZJUJEHISPQTIPODTGTGJCSPTGQTITPOPQTWEBJEJAQTGXOIMXQJCQPQTLXQOBOWHQPQTITQSUTPQWABSIAOEODZLSGUSECTGJPJAISPQTIBOIWAPODTQTITGTGJCSPTGPOPQTHITSPPSAMITFSJEJEHDTBOITWAPQSPBIOFPQTATQOEOITGGTSGXTPSMTJECITSATGGTUOPJOEPOPQSPCSWATBOIXQJCQPQTLHSUTPQTZSAPBWZZFTSAWITOBGTUOPJOEPQSPXTQTITQJHQZLITAOZUTPQSPPQTATGTSGAQSZZEOPQSUTGJTGJEUSJEPQSPPQJAESPJOEWEGTIHOGAQSZZQSUTSETXDJIPQOBBITTGOFSEGPQSPHOUTIEFTEPOBPQTKTOKZTDLPQTKTOKZTBOIPQTKTOKZTAQSZZEOPKTIJAQBIOFPQTTSIPQ";

  i = 0;
  fre = (char*) malloc(27);
  do {
      charCount[str[i]-'A']++;
  } while (str[++i] != 0);

  lastMax = 999;
  n = 0;

  for (i = 0; i < 26; i++) {
    max = 0;
    for (j = 0; j < 26; j++) 
      if (charCount[j] > max && lastMax > charCount[j]) max = charCount[j];
    
    for (j = 0; j < 26; j++)
      if (max == charCount[j]) fre[n++] = j + 'A';

    if (n == 26) break;
    lastMax = max;
  }
  fre[n] = 0;
if (args == 1) {
  puts("Frequent Letter from highest to lowest:");
  puts(fre);
}
if (args == 2) {
  //args[1] should be filled with the english letter
  //starting with the highest frequency one
  //for example:
  //
  // ./sub ETAOHRNIDSLCGW____________

  i = 0;
  engFre = argv[1];

  do {
    for (j = 0; j < 26; j++)
      if (str[i] == fre[j]) {
        if (engFre[j] <= 'Z' && engFre[j] >= 'A') putchar(engFre[j] +32);
        else  putchar(engFre[j]);
        break;
      }
  } while (str[++i] != 0);
  putchar('\n');
}
  return 0;
  
}

