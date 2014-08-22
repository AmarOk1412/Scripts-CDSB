#!/usr/bin/python
# -*- coding: latin-1 -*-
import math, random
from PIL import Image

w, h = 1600, 1200

image = Image.new("RGB", (w, h))
pix = image.load()

gris = (29,29,29)
bleu = (26, 124, 136)
#<idth, height, radius
pos = (800, 600, 1200)

for x in range(w):
    for y in range(h):
        if math.sqrt(math.pow((pos[0]-x), 2) + math.pow((pos[1]-y), 2)) <= pos[2]/2:
            pix[x,y] = (abs(int(26-15*(math.sqrt(math.pow((pos[0]-x), 2) + math.pow((pos[1]-y), 2))/(pos[2]/2)))), abs(int(124-90*(math.sqrt(math.pow((pos[0]-x), 2) + math.pow((pos[1]-y), 2))/(pos[2]/2)))), abs(int(136-100*(math.sqrt(math.pow((pos[0]-x), 2) + math.pow((pos[1]-y), 2))/(pos[2]/2)))))

image.save("out.png")


