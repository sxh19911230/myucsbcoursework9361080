all: dic bru sub2
dic: dictionaryAttack.c
	gcc -lcrypt dictionaryAttack.c -o dic
bru: bruteforce.c
	gcc -lcrypt bruteforce.c -o bru
sub2: subsitution2.c
	gcc -lcrypt subsitution2.c -o sub2
doDic: dic	
	./dic wordsEn.txt "\$5\$aBD123cdE\$ADH/D30llsWnrTJTKJBxvaztshXoNbX4J.hakVNp1p0"
doBru: bru
	./bru 2 STlLGmwDFuINg
doSub: sub2
	./sub2 wordsEn.txt "\$1\$aEcddE12\$9NCUhiNOvSP5QOdiRDf1Z."
clean:
	rm -f dic bru sub2
