#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
class Cryptomathic 
{
    private:

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


        // Vector with all the different letters. This vector is used to order the 
        // assignments in our search for a solution
        //
        vector<char> letters;
    

        // Store individual restrictions to letters
        //       
        map<char, vector<int> > individual_restrictions; 
 
        // Make simple inferentios to restrict domain for some letters
        //
        void restrict_domain ()
        {
            // leading letter in the result can't be zero
            individual_restrictions[sum[sum.length () - 1]].push_back (0);
        }


    public:

        // Default Constructor
        //
        Cryptomathic (string string1, string string2, string string3)
        {
            term1 = string1;
            term2 = string2;
            sum = string3;
        }


        vector<char> * solve ()
        {
            return NULL;
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

    Cryptomathic puzzle (string1, string2, string3);
    vector<char> * solution = puzzle.solve ();
}
