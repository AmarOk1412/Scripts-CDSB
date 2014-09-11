#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <map>
#include <cmath>

typedef std::map<std::string, int> MapStrInt;

std::vector<std::string> split(std::string str, std::string delimiter)
{
    std::vector<std::string> toReturn;
    std::string word;

    for(auto i = 0; i < str.length(); ++i)
    {
        if(delimiter.find(str[i]) == -1)
            word += str[i];
        else
        {
            if(word.length() > 0)
              toReturn.push_back(word);
            word.clear();
        }

        if(i == str.length() - 1)
        {
            if(word.length() > 0)
              toReturn.push_back(word);
            word.clear();
        }
    }


    return toReturn;
}

MapStrInt vectorToMap(std::vector<std::string> const vec)
{
	MapStrInt map;
	for(auto i = 0; i < vec.size(); ++i)
	{
		if(map.find(vec[i]) != map.end())
			map[vec[i]] += 1;
		else
			map[vec[i]] = 1;
	}
	return map;
}

MapStrInt filtMap(MapStrInt map)
{
    std::ifstream filtreFileEN("en.stopwords.txt");
    std::string strFiltreEN((std::istreambuf_iterator<char>(filtreFileEN)), std::istreambuf_iterator<char>());    
    std::vector<std::string> filtre = split(strFiltreEN, "\n");
    std::ifstream filtreFileFR("fr.stopwords.txt");
    std::string strFiltreFR((std::istreambuf_iterator<char>(filtreFileFR)), std::istreambuf_iterator<char>());
    std::vector<std::string> filtreFR = split(strFiltreFR, "\n");    
    filtre.insert(filtre.end(), filtreFR.begin(), filtreFR.end());
    
    for (auto i = 0; i < filtre.size(); ++i)
    	map.erase(filtre[i]);
    	
    return map;
}

double idf(std::string word, std::vector<MapStrInt> corpus)
{
	auto present = 0;
	for(auto i = 0; i < corpus.size(); ++i)
		if(corpus[i].find(word) != corpus[i].end())
			present++;
				
	return present == 0 ? present : std::log(double(corpus.size())/double(present));
}

double tf(std::string word, MapStrInt doc)
{
	auto occWord = 0;
	auto nbWord = 0;
	for(MapStrInt::iterator it = doc.begin(); it != doc.end(); ++it)
	{
		if(it->first == word)
			occWord = it->second;
		nbWord += it->second;
	}
	
	return double(occWord)/double(nbWord);

}

double tfidf(std::string word, MapStrInt doc, std::vector<MapStrInt> corpus)
{
	return tf(word, doc)*idf(word, corpus);
}

int main(int argc, char** argv)
{
    std::string delimiter = " &\"'{([-|`_\\)]=}+$£ø*%!§:/;.,?<>\n";
    
    //File1
    std::ifstream f1("testScript");
    std::string str((std::istreambuf_iterator<char>(f1)), std::istreambuf_iterator<char>());
    std::vector<std::string> splitStr = split(str, delimiter);
    MapStrInt mapF1 = vectorToMap(splitStr);    
    mapF1 = filtMap(mapF1);
    
    //File2
    std::ifstream f2("doc2");
    std::string str2((std::istreambuf_iterator<char>(f2)), std::istreambuf_iterator<char>());
    std::vector<std::string> splitStr2 = split(str2, delimiter);
    MapStrInt mapF2 = vectorToMap(splitStr2);    
    mapF2 = filtMap(mapF2);
    
    //File3
    std::ifstream f3("doc3");
    std::string str3((std::istreambuf_iterator<char>(f3)), std::istreambuf_iterator<char>());
    std::vector<std::string> splitStr3 = split(str3, delimiter);
    MapStrInt mapF3 = vectorToMap(splitStr3);    
    mapF3 = filtMap(mapF3);
    
    //Create corpus
    std::vector<MapStrInt> corpus;
    corpus.push_back(mapF1);
    corpus.push_back(mapF2);
    corpus.push_back(mapF3);
 
    std::cout << idf("viverra", corpus) << std::endl;
    std::cout << idf("lorem", corpus) << std::endl;
    std::cout << tf("viverra", mapF1) << std::endl;
    std::cout << tf("lorem", mapF1) << std::endl;

    return 0;
}
