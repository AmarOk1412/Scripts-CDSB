#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>

using namespace std;

vector<string> split(string str, string delimiter)
{
    vector<string> toReturn;
    string word;

    for(int i = 0; i < str.length(); ++i)
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

int main(int argc, char** argv)
{
    ifstream f("testScript");
    std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    //cout << str << endl;

    string delimiter = " &\"'{([-|`_\\)]=}+$£ø*%!§:/;.,?<>\n";

    vector<string> splitStr = split(str, delimiter);

    for(int i = 0; i < splitStr.size(); ++i)
        cout << splitStr[i] << endl;

    //Word to map

    return 0;
}
