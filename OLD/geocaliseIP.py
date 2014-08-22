#!/usr/bin/python
# -*- coding: utf-8 -*-
import urllib, sys, re, BeautifulSoup
from xml.dom import minidom

def geoIp(ip):
    codeSrc = ''
    codeSrc = urllib.urlopen('https://apps.db.ripe.net/whois/grs-search.xml?query-string='+ip+'&source=ripe-grs&source=afrinic-grs&source=apnic-grs&source=arin-grs&source=lacnic-grs&source=jpirr-grs&source=radb-grs').read()

    xmlFile = open('test.xml', 'w')
    xmlFile.write(codeSrc)
    xmlFile.close()

    xmldoc = minidom.parse('test.xml')
    localisation = xmldoc.getElementsByTagName('attribute')
    print localisation[2].attributes['value'].value.encode('utf-8','ignore')

geoIp(sys.argv[1])

