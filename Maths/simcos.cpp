#include <string>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

double normVect(vector<int> vec)
{
    double norm = 0;
    for(int i = 0; i < vec.size(); ++i)
    {
        norm += vec[i]*vec[i];
    }
    return sqrt(norm);
}

double scalarProduct(vector<int> vec1, vector<int> vec2)
{
    if(vec1.size() != vec2.size())
        throw string("Vectors must be the same length");
    
    double product = 0;
    for(int i = 0; i < vec1.size(); ++i)
    {
        product += vec1[i] * vec2[i];
    }
    return product;
}

double cosineSimilarity(vector<int> vec1, vector<int> vec2)
{       
    if(vec1.size() == 0 && vec2.size() == 0)
        throw string("Vectors length must be > 0");
    
    return scalarProduct(vec1, vec2) / (normVect(vec1) * normVect(vec2));
}

int main(int argc, char** argv)
{
    try
    {
        vector<int> v1;

        vector<int> v2;

        cout << "Cosine similarity : " << cosineSimilarity(v1, v2) << endl;
    }
    catch(string const& err)
    {
        cout << err << endl;   
    }
    
    try
    {
        vector<int> v1;
        v1.push_back(1);
        v1.push_back(2);

        vector<int> v2;       
        v2.push_back(4);
        v2.push_back(5);
        v2.push_back(6);

        cout << "Cosine similarity : " << cosineSimilarity(v1, v2) << endl;   
    }
    catch(string const& err)
    {
        cout << err << endl;   
    }
    
    try
    {
        vector<int> v1;
        v1.push_back(1);
        v1.push_back(2);
        v1.push_back(3);

        vector<int> v2;       
        v2.push_back(4);
        v2.push_back(5);
        v2.push_back(6);

        cout << "Cosine similarity : " << cosineSimilarity(v1, v2) << endl;   
    }
    catch(string const& err)
    {
        cout << err << endl;   
    }
    
    return 0;
}