GROUP NAME: twothreethree

HOW TO RUN CLIENT:
make run

OR:
make compile
java -cp .:lib/mysql-connector-java-5.1.37-bin.jar mysqlcmd [-h IP] [-u username] [-p]




HOW TO INSTALL LIBRARY:
make instlib

HOW TO ADD UDF IN SQL:
CREATE AGGREGATE FUNCTION SUM_HE RETURNS STRING SONAME 'udflibX.so';
