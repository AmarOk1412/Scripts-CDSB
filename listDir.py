#!/usr/bin/python3
# -*- coding: latin-1 -*-
import sys, os, sys, subprocess, re

def listdirectory(path): 
    '''list all files'''
    fichier=[] 
    #cf : http://docs.python.org/2/library/os.html
    for root, dirs, files in os.walk(path): 
        for i in files: 
            fichier.append(os.path.join(root, i)) 
    return fichier

fichiers = listdirectory('/home')
for f in fichiers:
    #sys.argv[1] = title
    print(sys.argv[1])
    m = re.search(sys.argv[1] + '.{0,10}(pn|jp)g', f)
    #Show images
    if m is not None:
        subprocess.call('shotwell ' + f, shell=True)
