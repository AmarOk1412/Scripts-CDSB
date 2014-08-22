#!/usr/bin/python3
# -*- coding: utf-8 -*-
import sys, time, math

t0 = time.time()

cell = lambda n: math.pow(2, bin(n).count('1'))
i = 0
while i < int(sys.argv[1]):
    print(cell(i))
    i += 1

print("%.10f seconds" % (time.time() - t0))
