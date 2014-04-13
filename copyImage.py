#-----------------------------------------------------------------
#| 5 bits posx | 5 bits posy | 8 red | 8 green | 8 blue | 5 size |
#-----------------------------------------------------------------
import random

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
        posToMutate = random.randint(0, len(gen)-1)
        gene[posToMutate] = 1 if gene[posToMutate] is '0' else 0
    return gene

def createGenome():
    population = []
    for i in range(0,400):
        population.append((generateGene(), 0))
    return population

#Pendant la lecture du gene, voir si il est correct.
