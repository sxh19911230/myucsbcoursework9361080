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
    
    ctext = ctext[0:len(ctext) - 16]
    findtext = ""
    
    def crackPad(ct, guessbyte, kt, endlen):
        tmp = ""
        for i in range(endlen - 1):
            #print endlen, i, kt
            tmp = chr(ord(ct[15 - i]) ^ ord(kt[len(kt) - i - 1]) ^ endlen) + tmp
            
        return ct[0:16-endlen] + chr(ord(ct[16 - endlen]) ^ guessbyte ^ endlen) + tmp
		
    while len(ctext) > 16:
        knownText = ""
        for i in range(1, 16):
            for j in range(256):
                print i
                tmp = crackPad(ctext[len(ctext) - 16:len(ctext)],j,knownText,i)

                if PadOracle(ctext[0:len(ctext) - 16] + tmp):
                    knownText = chr(j) + knownText
                    #print "test"
                    break
			
        findtext = knownText + findtext
        ctext = ctext[0:len(ctext) - 16]
                
                
    
        


    # end completing here, leave rest unchanged.
else:
    print("You need to specify a file!")
    

