#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <map>

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
    std::ifstream filtreFile("filtre");
    std::string strFiltre((std::istreambuf_iterator<char>(filtreFile)), std::istreambuf_iterator<char>());    
    std::vector<std::string> filtre = split(strFiltre, "\n");     
    for (auto i = 0; i < filtre.size(); ++i)
    	map.erase(filtre[i]);
    	
    return map;
}

int main(int argc, char** argv)
{
    std::ifstream f("testScript");
    std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

    std::string delimiter = " &\"'{([-|`_\\)]=}+$£ø*%!§:/;.,?<>\n";

    std::vector<std::string> splitStr = split(str, delimiter);
    MapStrInt map = vectorToMap(splitStr);
    
    map = filtMap(map);
 
    for (std::map<std::string,int>::iterator it=map.begin(); it!=map.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    return 0;
}
