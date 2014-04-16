
#-----------------------------------------------------------------
#| 7 bits posx | 7 bits posy | 8 red | 8 green | 8 blue | 3 size |
#-----------------------------------------------------------------
import random
import cv, cv2
import numpy as np

def toBin(number, nCarac):
    return str(bin(number)[2:len(bin(number))]).zfill(nCarac)

def generateGene():
    posx = toBin(random.randint(0, 100), 7)
    posy = toBin(random.randint(0, 100), 7)
    red = toBin(random.randint(0, 255), 8)
    green = toBin(random.randint(0, 255), 8)
    blue = toBin(random.randint(0, 255), 8)
    size = toBin(random.randint(0, 100), 7)
    return posx + posy + red + green + blue + size

def mutateGene(gene, n):
    if random.randint(1,100) <= n:
        posToMutate = random.randint(0, len(gene)-1)
        geneToChange = list(gene)
        if geneToChange[posToMutate] is '0':
            geneToChange[posToMutate] = '1'
        else:
            geneToChange[posToMutate] = '0'
        gene = "".join(geneToChange)
    return gene

def createGenome():
    population = []
    for i in range(0,2000):
        population.append([generateGene(), 0])
    return population

def mutateGenome(genome):
    for e in genome:
        e[0] = mutateGene(e[0], 100)
    return genome

def crossGenome(dadGen, motherGen):
    sonGen = []
    for i in range(0, len(dadGen)-1):
        if random.randint(0,1) == 0:
            sonGen.append(dadGen[i])
        else:
            sonGen.append(motherGen[i])
    return sonGen

def translateGene(gene):
    posx = int(gene[:7], 2)
    posy = int(gene[7:14], 2)
    red = int(gene[14:22], 2)
    green = int(gene[22:30], 2)
    blue = int(gene[30:38], 2)
    size = int(gene[38:41], 2)
    if posx > 100:
        posx = 100
    if posy > 100:
        posy = 100
    return [posx, posy, red, green, blue, size]

def drawRect(image, posx, posy, red, green, blue, size):
    image[posx*len(image)/100:posx*len(image)/100 + len(image)*size/100, posy*len(image)/100:posy*len(image)/100 + len(image)*size/100] = [red, green, blue]
    return image

def createImageFromGenome(genome):
    image = np.zeros((800, 800, 3), np.uint8)
    cv2.imwrite('test.png', image)
    for gene, score in genome:
        translation = translateGene(gene)
        image = drawRect(image, translation[0], translation[1], translation[2], translation[3], translation[4], translation[5])
    return image

#TODO Prendre la distance px, ajouter le tout, diviser par le nombre de px. 
def evaluateImage(image, base):
    nbPx = len(base)*len(base[0])
    #...
    return 0

population = []
for i in range(0,100):
    population.append(createGenome())
for i in range(0, len(population)):
    cv2.imwrite('test'+str(i)+'.png', createImageFromGenome(population[i]))
