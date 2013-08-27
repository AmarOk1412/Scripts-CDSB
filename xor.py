#!/usr/bin/python3
import binascii, sys

def repr_bin(str, encoding):
     s = ""
     for v in str.encode(encoding):
         s += bin(v)[2:].zfill(8)
     return s

def xor(clef, toCrypte):
   retour = ''
   c=0
   while c < len(toCrypte):
       retour = retour + '0' if clef[c] == toCrypte[c] else retour + '1'
       c += 1
   return retour

def binToAscii(binaire):
    n = int(binaire, 2)
    return binascii.unhexlify('%x' % n)

Keyfile = open(sys.argv[2], 'r')
temp = Keyfile.read()
clef = repr_bin(temp, "iso-8859-1")
Keyfile.close()

filetoCrypt = open(sys.argv[1], 'r')
temp = filetoCrypt.read()
toCrypte = repr_bin(temp, "iso-8859-1")
filetoCrypt.close()

while len(clef) < len(toCrypte):
     clef = clef + clef

crypter = xor(clef, toCrypte)
fileFinal = open('finish', 'w')
fileFinal.write(str(binToAscii(crypter)))
fileFinal.close()

#fileFinal = open('retour', 'w')
#fileFinal.write(str(binToAscii(xor(clef, crypter))))
#fileFinal.close()

