#!/usr/bin/python3
# -*- coding: utf-8 -*-
import sys, time

t0 = time.time()

cellList = list()
i = 0

while i < int(sys.argv[1]):
    cell = 0
    stop = False  
    tempList = list(cellList)
    while not stop and i is not 0:
        if cell != len(cellList) - 1:
            cellList[cell + 1] = 1 if tempList[cell] + tempList[cell + 1] is 1 else 0
        else:
            cellList.append(1)
            stop = True
        cell += 1
    if i is 0:
        cellList.append(1)
    i += 1


print('cell(' + str(bin(i)) + ') : ' + str(cellList.count(1)))


print("%.10f seconds" % (time.time() - t0))
