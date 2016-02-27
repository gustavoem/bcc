#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

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
        map<char, set<int> > individual_restrictions; 


        // Make simple inferentios to restrict domain for some letters
        //
        void restrict_domain ()
        {
            // leading letter in the result can't be zero
            individual_restrictions[sum[sum.length () - 1]].insert (0);

            // if first two are equal then first number of sum is even
            if (term1[0] == term2[0])
                for (unsigned int i = 1; i < 10; i += 2)
                    individual_restrictions[term1[0]].insert (i);

            // if sum has more digits then term1 and term2 then the leading digit of sum is one
            if (sum.length () > term1.length () && sum.length () > term2.length ())
            {
                for (unsigned int i = 2; i < 10; i++)
                    individual_restrictions[sum[sum.length () - 1]].insert (i);
                individual_restrictions[sum[sum.length () - 1]].insert (0);
            }
        }


        // Reorders variables so we have less expanded nodes
        //
        void reorder_var ()
        {
            // simple insertion sort
            for (unsigned int i = 0; i < letters.size () - 1; i++)
            {
                unsigned int min = individual_restrictions[letters[i]].size ();
                unsigned int i_min = i;
                for (unsigned int j = i + 1; j < letters.size (); j++)
                {
                    if (min > individual_restrictions[letters[j]].size ())
                    {
                        min = individual_restrictions[letters[j]].size ();
                        i_min = j;
                    }
                }

                char temp = letters[i];
                letters[i] = letters[i_min];
                letters[i_min] = temp;
            }
        }


    public:

        // Default Constructor
        //
        Cryptomathic (string string1, string string2, string string3)
        {
            term1 = string1;
            term2 = string2;
            sum = string3;

            restrict_domain ();
            // reorder_var ();
            

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
