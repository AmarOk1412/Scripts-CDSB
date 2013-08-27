# -*-coding: utf-8 -*
import random, os
from PIL import Image

def recalcTable(tab, width, height):
    '''Algorithm'''
    new = [[0 for x in xrange(width)] for x in xrange(height)] #Represent each pix of the picture
    for x in range(width):
        for y in range(height):
            livingCell = 0
            #type of cell
            m = 0
            f = 0
            for pixX, pixY in ((x - 1, y - 1), (x, y - 1), (x + 1, y - 1),
                               (x - 1, y),                 (x + 1, y),
                               (x - 1, y + 1), (x, y + 1), (x + 1, y + 1)):
                #If the cell got a neighbour
                if -1 < pixX < width and -1 < pixY < height and tab[pixX][pixY] > 0:
                    livingCell += 1
                    if tab[pixX][pixY] is 1:
                        f += 1
                    else:
                        m += 1
            #Create the pix
            if livingCell == 3 and f > 1 and m > 1:
                new[x][y] = m if m > f else f
            elif livingCell < 2 or livingCell > 3:
                new[x][y] = 0
            else:
                new[x][y] = tab[x][y]
    return new
######################################################################################
step = 0
w = 100
h = 100

Matrix = [[0 for x in xrange(w)] for x in xrange(h)]
#TODO: got a beautiful matrix
for x in range(w):
    for y in range(h):
        Matrix[x][y] = random.randint(0,2)

while step <= 100:
	image = Image.new("RGB", (w, h))
	pix = image.load()

        #Draw the picture
	for x in range(w):
	    for y in range(h):
		if Matrix[x][y] is 0:
		    pix[x,y] = (0,0,0)#Dead
                elif Matrix[x][y] is 1:
		    pix[x,y] = (245,55,220)#Male
		else:
		    pix[x,y] = (45,88,207)#Female
        #Save it
	image.save(str(step).rjust(3, '0') + ".png")
	Matrix = recalcTable(Matrix, w, h)
	step += 1
#Create the Video
os.system('ffmpeg -f image2 -r 1 -i img%3d.png -c:v libx264 -r 30 out.mp4')

