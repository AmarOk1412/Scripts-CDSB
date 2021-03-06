#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <map>
#include <cmath>
#include <tuple>
#include <algorithm>
#include <regex>

typedef std::map<std::string, int> MapStrInt;
typedef std::map<std::string, std::vector<int>> Index;

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

int levenshteinDistance(std::string s1, std::string s2)
{
	int d[s1.length()+1][s2.length()+1];
  int i, j, c;

  for(i = 0; i <= s1.length(); ++i)
		d[i][0] = i;

  for(j = 0; j <= s2.length(); ++j)
		d[0][j] = j;

  for(i = 1; i <= s1.length(); ++i)
		for(j = 1; j <= s2.length(); ++j)
			d[i][j] = std::min(std::min(d[i-1][j]+1, d[i][j-1]+1), d[i-1][j-1]+(s1[i] == s2[j] ? 0 : 1));

	return d[s1.length()][s2.length()];
}

bool isVowel(char c)
{
	std::vector<char> vowels = {'a', 'â', 'à', 'ë', 'e', 'é', 'ê', 'è', 'i', 'ï', 'î', 'o', 'ô', 'u', 'û', 'ù', 'y'};
	return std::find(vowels.begin(), vowels.end(), c) != vowels.end();
}

std::string optUpperCase(std::string word)
{
	std::string toReturn = word;
	
	for(auto i = 0; i < word.length(); ++i)
	{
		if(word[i] == 'u' || word[i] == 'i')
		{
			if(i > 0 && isVowel(word[i-1]))
			{
				toReturn[i] = std::toupper(word[i]);
				break;
			}
			if(i < word.length()-1 && isVowel(word[i-1]))
			{
				toReturn[i] = std::toupper(word[i]);
				break;
			}
		}
		
		if(i > 0 && word[i] == 'u' && word[i-1] == 'q')
		{
			toReturn[i] = std::toupper(word[i]);
			break;
		}
		
		if(word[i] == 'y')
		{
			if(i > 0 && isVowel(word[i-1]))
			{
				toReturn[i] = std::toupper(word[i]);
				break;
			}
			if(i < word.length()-1 && isVowel(word[i+1]))
			{
				toReturn[i] = std::toupper(word[i]);
				break;
			}
		}
	}
			
	return toReturn;
}

//BUG
std::string getR1(std::string word)
{
	
	auto posR1 = -1;
	std::string toReturn = "";
	
	for(auto i = 0; i < word.length(); ++i)
	{		
		if(i > 0 && !isVowel(word[i]) && isVowel(word[i-1]))
		{
			posR1 = i+1;
			break;
		}
	}
	
	if(posR1 != -1)
		for(; posR1 < word.length(); ++posR1)
			toReturn += word[posR1];
			
	return toReturn;
}

std::string getR2(std::string word)
{
	std::string toTreat = getR1(word);
	std::string toReturn = "";
	
	auto posR2 = -1;
	for(auto i = 0; i < toTreat.length(); ++i)
	{		
		if(i > 0 && !isVowel(word[i]) && isVowel(word[i-1]))
		{
			posR2 = i+1;
			break;
		}
	}
	
	if(posR2 != -1)
		for(; posR2 < toTreat.length(); ++posR2)
			toReturn += toTreat[posR2];
	
	return toReturn;
}

std::string getRV(std::string word)
{
	auto posR1 = -1;
	std::string toReturn = "";
	std::vector<std::string> except = {"par", "col", "tap"};
	
	if(word.length() > 3 && isVowel(word[0]) && isVowel(word[1]))
		for(auto i = 3; i < word.length(); ++i)
			toReturn += word[i];
	else if(std::find(except.begin(), except.end(), word.substr(0,3)) != except.end())
		for(auto i = 3; i < word.length(); ++i)
			toReturn += word[i];
	else
	{
		auto i = 1;
		auto vowel = false;
		while(i < word.length())
		{
			if(vowel)
				toReturn += word[i];
			if(isVowel(word[i]))
				vowel = true;
			++i;
		}
	}
	
	return toReturn;
}

//std::string removeSuffix(std::string word)
//{
//	std::tr1::cmatch res;
//	std::tr1::regex rx("(ance|iqUe|isme|able|iste|eux|ances|iqUes|ismes|ables|istes)$");
//	std::tr1::regex_search(word.c_str(), res, rx);
//	std::cout << res << std::endl;
//	return "";
//}

std::string stemFRWord(std::string word)
{
	std::string toStem = word;
	
	std::transform(toStem.begin(), toStem.end(), toStem.begin(), ::tolower);
	
	return toStem;
}

int main(int argc, char** argv)
{
		std::vector<std::tuple<std::string, int, int>> Documents;
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
    
    std::cout << "optUpperCase : jouer " << optUpperCase("jouer") << std::endl;
    std::cout << "optUpperCase : ennuie " << optUpperCase("ennuie") << std::endl;
    std::cout << "optUpperCase : yeux " << optUpperCase("yeux") << std::endl;
    std::cout << "optUpperCase : quand " << optUpperCase("quand") << std::endl;
    
    std::cout << "RV : aimer " << getRV("aimer") << std::endl;
    std::cout << "RV : adorer " << getRV("adorer") << std::endl;
    std::cout << "RV : voler " << getRV("voler") << std::endl;
    std::cout << "RV : tapis " << getRV("tapis") << std::endl;
    
    std::cout << "R2 : quand " << getR2("quand") << std::endl;
    std::cout << "R1 : fameusement " << getR1("fameusement") << std::endl;
    std::cout << "R2 : fameusement " << getR2("fameusement") << std::endl;

    return 0;
}
