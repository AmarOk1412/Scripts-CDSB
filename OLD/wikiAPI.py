#!/usr/bin/python
# -*- coding: utf-8 -*-
import urllib, sys, re, BeautifulSoup
from xml.dom import minidom

params = ""
i = 1
while i < len(sys.argv):
    params += sys.argv[i] + " "
    i += 1

r = re.compile(r"(d(é|e)cris.(moi|)(|qui.es(t|)|qu.es(t|).ce.qu(.(un|une)|e.(un|une|la|le)))|bio(graphie|)(.compl(è|e)te|)(.de|.d.|.))(.{0,200})")
results = r.findall(params)

codeSrc = urllib.urlopen('http://en.wikipedia.org/w/api.php?action=query&list=search&srsearch=sebastien+?&srprop=timestamp&format=xml').read()

xmlFile = open('test.xml', 'w')
xmlFile.write(codeSrc)
xmlFile.close()

xmldoc = minidom.parse('test.xml')
itemlist = xmldoc.getElementsByTagName('p') 
print len(itemlist)
print itemlist[0].attributes['title'].value
print type(itemlist[0].attributes['title'].value.encode('ascii','ignore'))
