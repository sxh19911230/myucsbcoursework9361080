#!/usr/bin/python2
# CS177 -- padding oracle attacks This code is (unfortunately) meant
# to be run with Python 2.7.10 on the CSIL cluster
# machines. Unfortunately, cryptography libraries are not available
# for Python3 at present, it would seem.
from __future__ import print_function
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

    #My Exception Class
    class UnableToDecipher(Exception):
      pass

    #Help Function: rescusively decipher the last block of the text
    def rescusiveDecipherOneBlockText(theLastNthByte, knownText, ciphertext):
      if theLastNthByte == 17: return knownText
      cb = bytearray(ciphertext)
      decipherByte = cb[-16-theLastNthByte]
      for i in range(theLastNthByte - 1): cb[-17-i] = cb[-17-i] ^ ord(knownText[-1-i]) ^ theLastNthByte
      for guessByte in range(256):
        cb[-16-theLastNthByte] =  decipherByte ^ guessByte ^ theLastNthByte;
        if (PadOracle(str(cb))):
          try: return rescusiveDecipherOneBlockText(theLastNthByte+1,chr(guessByte) + knownText, ciphertext)
          except UnableToDecipher: pass
      else: raise UnableToDecipher()

    #Help Function: rescusively print all blocks
    def rescusivePrintText(ciphertext):
      if len(ciphertext) > 16:
        rescusivePrintText(ciphertext[:-16])
        print(rescusiveDecipherOneBlockText(1,"",ciphertext[-32:]), end="")

    #Help Function: do similiar as rescusivePrintText but remove the padding at the end
    def printText(ciphertext):
      if len(ciphertext) > 16:
        rescusivePrintText(ciphertext[:-16])
        lastText = rescusiveDecipherOneBlockText(1,"",ciphertext[-32:])
        print(lastText[:-ord(lastText[-1])], end="")

    #Print!
    printText(ctext)

    # end completing here, leave rest unchanged.
else:
    print("You need to specify a file!")
