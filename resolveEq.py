#!/usr/bin/python3
# -*- coding: utf-8 -*-
import sys, time, re
from sympy.solvers import solve
from sympy import Symbol

def resolve(equation):
    '''Resolve an equation with 1 unknown var'''
    #Find the symbol
    r = re.compile(r"([A-Za-z]{0,})")
    varList = r.findall(equation)
    symbol = ''
    for a in range(0, len(varList)):
        if len(varList[a]) > 0:
            symbol = varList[a]
            break
    
    x = Symbol(symbol)
    #replace 3x -> 3*x for example
    r2 = re.compile(r'([0-9])'+symbol)
    replaceList = r2.findall(equation)
    for a in range(0, len(replaceList)):
        if len(replaceList[a]) > 0:
            equation = re.sub(r''+replaceList[a]+symbol, r''+replaceList[a]+'*'+symbol, equation)
    #rewrite the eq to solve it
    r3 = re.compile(r"(.{0,})\=(.{0,})")
    results = r3.findall(equation)
    mGauche = results[0][0]
    mDroite = results[0][1]

    return solve(mGauche + '-(' + mDroite + ')', x)

eq = sys.argv[1]
print(resolve(eq))
