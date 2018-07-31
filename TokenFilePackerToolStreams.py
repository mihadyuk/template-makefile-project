#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import gzip
import shutil
import os
import struct
import hashlib
#import platform

def GenerateArray(tokenFileStream, arrayName, arraySizeName, outputFile):
    
        #create array size variable
        outputFile.write('extern const size_t %s = %s;\n\n' % 
        (arraySizeName, len(tokenFileStream)))
        
        #create array header
        outputFile.write('extern const uint8_t %s[%s] = { \n' % 
        (arrayName, arraySizeName))
        #outputFile.write('const char %s[] = { \n' % 
        #(arrayName))
        
        #fill the array with file data
        i = 0
        while i < len(tokenFileStream):
            outputFile.write('    ')
            col = 16		
            while col > 0 and i < len(tokenFileStream):
                outputFile.write('0x%.2X,' % tokenFileStream[i])
                col = col - 1
                i = i + 1
            outputFile.write('\n')    
            
        #write enlosing bracket instead of last comma
        #outputFile.seek(-3, os.SEEK_CUR)
        outputFile.write('};\n')

def GenerateHashArray(tokenFileStream, arrayName, arraySizeName, outputFile):
    
        #create array size variable
        outputFile.write('extern const size_t %s = %s;\n\n' % 
        (arraySizeName, len(tokenFileStream)))
        
        #create array header
        outputFile.write('extern const uint8_t %s[%s] = { \n' % 
        (arrayName, arraySizeName))
        #outputFile.write('const char %s[] = { \n' % 
        #(arrayName))
        
        #fill the array with file data
        i = 0
        while i < len(tokenFileStream):
            outputFile.write('    ')
            col = 16		
            while col > 0 and i < len(tokenFileStream):
                outputFile.write('\'%c\',' % tokenFileStream[i])
                col = col - 1
                i = i + 1
            outputFile.write('\n')    
            
        #write enlosing bracket instead of last comma
        #outputFile.seek(-3, os.SEEK_CUR)
        outputFile.write('};\n')
		
   
#https://www.pythoncentral.io/hashing-files-with-python/
def GenerateHash(fileName, blockSize=4096):
    #calculate sha1 hash
    hasher = hashlib.sha1()
    with open(fileName, 'rb') as f:
        buffer = f.read(blockSize)
        while len(buffer) > 0:
            hasher.update(buffer)
            buffer = f.read(blockSize)
    
    #save hash to file
    return hasher.hexdigest()
        
    
'''
usage: 
TokenFilePacker.py /path/to/token/file /path/to/generated c++ file

'''

tokenFile               = sys.argv[1]
#compressedTokenFile     = ("%s.%s" % (tokenFile, "gzip")) 
#compressedTokenFileHash = ("%s.%s" % (compressedTokenFile, "sha1"))
outputGeneratedFile     = sys.argv[2]

#sys.stderr.write(tokenFile)
#sys.stderr.write('debug \r\n')
#exit(1)

#pack token file
#https://docs.python.org/2/library/gzip.html
#with open(tokenFile, 'rb') as f_in, \
#gzip.open(compressedTokenFile, 'wb') as f_out:
#    shutil.copyfileobj(f_in, f_out)
def compressFile(tokenFile):
	with open(tokenFile, 'rb') as f_in, \
	open('test.gz', 'wb') as f_out:
		buffer = gzip.compress(f_in.read())
		f_out.write(buffer)
		return buffer

#generate c++ source file with built-in token file as array 
with open(outputGeneratedFile, 'w') as f:
    #write copyright
    f.write('/******************************************************************************\n')
    f.write('******************************************************************************/\n')
    f.write('#include \"tokenFile.h\"\n\n')

    #generate table with zipped token file and it's size
    GenerateArray(compressFile(tokenFile), 'tokenFile', 'tokenFileSize', f)
      
    #calculate hash for uncompressed token file and save to file
    GenerateHash(tokenFile)
    
    #create array from hash file
    f.write('\n\n')
    GenerateHashArray(GenerateHash(tokenFile), 'tokenFileHash', 'tokenFileHashSize', f)
    
#remove unneeded compressed token file and it's hash file 
#os.remove(compressedTokenFile)
#os.remove(compressedTokenFileHash)        