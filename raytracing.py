 #!/usr/bin/python
 # -*- coding: latin-1 -*-
import math
from PIL import Image

def sub(v1, v2): return [x-y for x,y in zip(v1, v2)]
def dot(v1, v2): return sum([x*y for x,y in zip(v1, v2)])
def norm(v): return [x/math.sqrt(dot(v,v)) for x in v]

def trace_sphere(r, s, tmin, color):
    sr = sub(s[0], r[0])
    dsr = dot(sr, r[1])

    d = dsr*dsr - dot(sr,sr) + s[1]
    if d < 0: return
    d = math.sqrt(d)

    t1 = dsr + d
    if t1 < 0: return

    t2 = dsr - d
    if t2 > tmin[0]: return

    if t2 < 0:
        tmin[0] = t1
    else:
        tmin[0] = t2
    color[:] = [s[2]]

def trace_ray(ray, spheres):
    color = [(0, 0, 0)]
    tmin = [100000]
    for s in spheres:
        trace_sphere(ray, s, tmin, color)
	print color[0]
    return color[0]

red = (255,0,0)
blue = (0,0,255)
spheres = ( ((0,0,10), 10.0, red), ((0,-5,50), 20.0, blue) )

w, h = 200, 200

image = Image.new("RGB", (w, h))
pix = image.load()

for x in range(w):
    for y in range(h):
        ray = ( (0,0,0), norm(((x-w/2.0)/w, (y-h/2.0)/w, 1)) )
        pix[x,y] = trace_ray(ray, spheres)

image.save("out.png")
