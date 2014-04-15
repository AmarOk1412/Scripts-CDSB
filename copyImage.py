#-----------------------------------------------------------------
#| 7 bits posx | 7 bits posy | 8 red | 8 green | 8 blue | 5 size |
#-----------------------------------------------------------------
import random
import cv2

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
    for i in range(0,400):
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
    posy = int(gene[8:14], 2)
    red = int(gene[14:22], 2)
    green = int(gene[23:30], 2)
    blue = int(gene[31:39], 2)
    size = int(gene[40:45], 2)
    if size > 100:
        size = 10
    if posx > 100:
        posx = 10
    if posy > 100:
        posy = 10
    return [posx, posy, red, green, blue, size]

#TODO : test
def drawRect(image, posx, posy, red, green, blue, size):
    cv2.rectangle(image, [posx, posy], [posx + len(image)*size/100, posy + len(image[0])*size/100], [red, green, blue])
    return image

#TODO Prendre la distance px, ajouter le tout, diviser par le nombre de px. 
def evaluateImage(image, base):
    nbPx = len(base)*len(base[0])
    #...
    return 0

dadGen = createGenome()
print(translateGene(dadGen[0][0]))
#motherGen = createGenome()
#print(dadGen == motherGen)
#sonGen = crossGenome(dadGen, motherGen)
#print(dadGen == sonGen)
#print(sonGen == motherGen)
#Pendant la lecture du gene, voir si il est correct.
