#!/usr/bin/python
ciph = "BAQKIFBTTYVRTUBSVVIVTEPYKMIUBLAHXDLGGNASZWGVXKPUTFAOPSMALOCQXLUXWJBUWDELVLWFBZXWPKRCMLIJBZFHRREBTSESGKTZWEQCWAPSBZXDECQMKLQFBWESMQILMAPSVVHSTRMLLIMUIMLLLOLYWHKZQWOLHCSKNJPLPWPOIOPLXDGGZCPHVCELWZWGVOAPPCXYESBZMVHSTRMLLOIVMNXYHYRCPHAECUDHFYYRBUBZMOTAIBLYOPVYIYHVHDMKXICLKGGCIBWCEFBZMVHSTRMLLOIVIDPHCCFCEPMNMVMOEDXFXFEWZWYHVWSPXPVLMDEPKORRMOIFUSGMSBTPXJQKMDRALOWYFLZWIKHUWMYPBVCKTQXUSEKFMOMVWDIOMXWFTKTGVYDUSGRMYAPWQEILRNMLZKMKBJNJXSSLHMBZMHEHROXCTYBZIFWOENQYWLUSVQTAXOQNMZBGIDXYXWELDPVVWXMOINELZLZTCLFVWDSDMOMAZUHTQERGVHBAWFLDIBIKBZQFBWKWVOXCWHASUMLPRQERMLUHBKMVTERAAMWGBTTSPCSPPOQKBDXMSBXGWIQLAKHALOCCOLVLCSESCQETXBXSVVELJDXFXLIJBZUFXRIGKVEFUWTUWCLMKATQJWYVVOXFXCWYWFLHVBMTXKBZMDTZXOZCKKWDXZBUQOWQTNMOIKFPWSRRXYXJMLXKECEQNYXJQKBUKVCQHWPAALBJEDIBTABWUHMASNSYWVCTTWUHGUAYKKAKWEXYWKYJMAPJWMZOERSMIDPATKMDLSWREPVYBZXZXKVQIYIFODXKFKRLXYJMBAGMEMXRALUWAKTNIGEQMOQKAGEVRQELWAPSVCLMSBEJEAPWNALO"

l = len(ciph)
print ("length = " + str(l))
tmp = ciph
for i in range(100):
  count = 0
  tmp = tmp[1:]
  for j in range(l-i-1):
    if ciph[j] == tmp[j]:
      count=count+1
  print i, float(count)/(l-i)

  
  

