#!/usr/bin/python3
# -*- coding: utf-8 -*-
import sys, time, math

t0 = time.time()

def cell(coup):
        print coup
	cellList = list()
	i = 0

	while i < coup:
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

	return cellList.count(1)


n = int(sys.argv[1])

#On regarde si on a une puissance de 2
if n & (n-1) == 0:
     print 'cell(' + str(n) + ') : ' + str(n)
else:
#Sinon, on enleve la puissance de deux en dessous
     print 'cell(' + str(n) + ') : ' + str(cell(n - math.pow(2, len(bin(n)) - 3)))


print("%.10f seconds" % (time.time() - t0))
