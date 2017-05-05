#!/usr/bin/python2
# CS177 -- padding oracle attacks This code is (unfortunately) meant
# to be run with Python 2.7.10 on the CSIL cluster
# machines. Unfortunately, cryptography libraries are not available
# for Python3 at present, it would seem.
from Crypto.Cipher import AES
import binascii
import sys

def check_enc(text):
    nl = len(text)
    val = int(binascii.hexlify(text[-1]), 16)
    if val == 0 or val > 16:
        return False

    for i in range(1,val+1):
        if (int(binascii.hexlify(text[nl-i]), 16) != val):
            return False
    
    return True
                                 
def PadOracle(ciphertext):
    if len(ciphertext) % 16 != 0:
        return False
    
    tkey = 'Sixteen byte key'

    ivd = ciphertext[:AES.block_size]
    dc = AES.new(tkey, AES.MODE_CBC, ivd)
    ptext = dc.decrypt(ciphertext[AES.block_size:])

    return check_enc(ptext)


def printStr(test):
        for i in range(len(test)):
            print test[i],
        print 
# Padding-oracle attack comes here

if len(sys.argv) > 1:
    myfile = open(sys.argv[1], "r")
    ctext=myfile.read()
    myfile.close()

    # complete from here. The ciphertext is now (hopefull) stored in
    # ctext as a string. Individual symbols can be accessed as
    # int(ctext[i]). Some more hints will be given on the Piazza
    # page.
    
    if len(ctext) % 16 != 0:
      exit(0)
    
    
    findtext = ""

    #test = bytearray(ctext)
    #test[-17] = test[-17] ^ 15 ^ 1
    #print PadOracle(str(test))




        
    while len(ctext) > 16:

        knownText = ""
        for i in range(1, 17):

            cb = bytearray(ctext)

            for j in range(i - 1):
                cb[-17-j] = cb[-17-j] ^ ord(knownText[-1-j]) ^ i

            for j in range(256):
                tmp = cb[:]
                tmp[-16-i] = tmp[-16-i] ^ j ^ i;
                if (i != j and PadOracle(str(tmp))):
                    #print i, j
                    knownText = chr(j) + knownText
                    break
                    
            else:
              if PadOracle(str(cb)):
                #print i, i
                knownText = chr(i) + knownText
              else:
                print "error", i
                exit(0)
            
        findtext = knownText + findtext
        ctext = ctext[0:-16]
                
                
    findtext = findtext[:-ord(findtext[-1])]
    print findtext


    # end completing here, leave rest unchanged.
else:
    print("You need to specify a file!")
    

