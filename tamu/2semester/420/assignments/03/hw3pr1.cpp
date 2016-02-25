#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Cryptomathic 
{
    // The following strings represent the cryptomathic problem
    //
    //   term1
    // + term2
    // _______
    //     sum
    //
    string term1;
    string term2;
    string sum;
    

    // Represents the global domain for each variable, i.e this is responsible for
    // keeping track of numbers that haven't been used yet. Useful for checking 
    // that all letters have different values assigned
    //
    vector<unsigned int> global_domain;


    // assignments[i] = C iif we assigned value i to letter C
    //
    vector<char> assignments;


    // Vector with all the different letters
    //
    vector<char> letters;


    // Default Constructor
    //
    Cryptomathic (string string1, string string2, string string3)
    {
        term1 = string1;
        term2 = string2;
        sum = string3;
    }
};

int main ()
{
    string string1;
    string string2;
    string string3;

    cin >> string1;
    cin >> string2;
    cin >> string3; 
}
