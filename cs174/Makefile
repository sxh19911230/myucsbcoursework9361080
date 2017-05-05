run:  compile
	java -cp .:lib/mysql-connector-java-5.1.37-bin.jar mysqlcmd -h 54.153.48.121
compile: client enc dec

client:
	javac mysqlcmd.java 
keyGen:
	cc  keyGen.c paillier.c -o keyGen -lgmp
enc:
	cc  enc.c paillier.c -o enc -lgmp
dec:
	cc  dec.c paillier.c -o dec -lgmp
instlib:
	gcc paillier.c  udflibX.c -o udflibX.so -shared -lgmp -I/usr/include/mysql -fPIC
	sudo mv udflibX.so /usr/lib/mysql/plugin/
clean:
	rm *.class enc dec *.so

test:
	./enc 1000 a
	vi a
