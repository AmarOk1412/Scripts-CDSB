#include <string>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int levenshteinDistance(string s1, string s2)
{
	int d[s1.length()+1][s2.length()+1];
  int i, j, c;

  for(i = 0; i <= s1.length(); ++i)
		d[i][0] = i;

  for(j = 0; j <= s2.length(); ++j)
		d[0][j] = j;

  for(i = 1; i <= s1.length(); ++i)
		for(j = 1; j <= s2.length(); ++j)
			d[i][j] = min(min(d[i-1][j]+1, d[i][j-1]+1), d[i-1][j-1]+(s1[i] == s2[j] ? 0 : 1));

	return d[s1.length()][s2.length()];
}

int main(int argc, char** argv)
{
	string s1 = "";
	string s2 = "back";

	cout << levenshteinDistance(s1, s2) << endl;

	return 0;
}
