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
        vector<bool> global_domain;


        // Maps letters to values
        //
        map<char, int> assignments;


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
            individual_restrictions[term1[term1.length () - 1]].insert (0);
            individual_restrictions[term2[term2.length () - 1]].insert (0);

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
            // Simple insertion sort. We won't have many vars to sort
            //
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

        
        

        
        // Returns the value of i-th charachter of s. 
        // If i >= s.length returns 0
        // Returns -1 if characther not defined
        //
        int getValue (string s, unsigned int i)
        {
            if (i < s.length ())
                if (assignments.find (s[i]) != assignments.end ())
                    return assignments[s[i]];
                else
                    return -1;
            else
                return 0;
        }
        

        // Verifies if a character from s at index i is defined. If i >= s.length returns
        // true
        //
        bool isDefined (string s, unsigned int i)
        {
            if (i < s.length () && assignments.find (s[i]) != assignments.end ())
                return false;
            else
                return true;
        }

    public:

        // Default Constructor
        //
        Cryptomathic (string string1, string string2, string string3)
        {
            term1 = string1;
            term2 = string2;
            sum = string3;
                
            for (unsigned int i = 0; i < 10; i++)
                global_domain.push_back (true);

            restrict_domain ();
            // reorder_var ();
        }

        // Verifies if variable assignments broken any rule
        //
        bool isConsistant ()
        {
            unsigned int max_index = max (max (term1.length (), term2.length ()), sum.length());
            for (unsigned int i = 0; i < max_index; i++)
            {
                // There is no reason to verify consistency on index i if one of the 
                // variables is not defined for this index. 
                if (!(isDefined (term1, i) && isDefined (term2, i) && isDefined (sum, i)))
                    continue;

                // verifies if there is carry. If there is assign it to carry
                // if not possible to determine assign -1 to carry
                int carry = -1;
                if (i > 0)
                {
                    if (isDefined (term1, i - 1) && isDefined (term2, i - 1))
                    {
                        int s1_digit = getValue (term1, i - 1);
                        int s2_digit = getValue (term2, i - 1);

                        if (s1_digit + s2_digit > 9)
                            carry = 1;
 
                        // We are ignoring some cases where we could already tell that
                        // there is some inconsistency. But they are going to be
                        // recognized in further iterations when there are more letters
                        // defined

                        if (s1_digit + s2_digit < 8)
                            carry = 0;
                    }
                    else
                        carry = -1;

                }
                else
                {
                    carry = 0; // i = 0
                }
               
                // we are assuming that these numbers are defined 
                int s1_digit = getValue (term1, i);
                int s2_digit = getValue (term2, i);
                int sum_digit = getValue (sum, i);

                if (carry == -1)
                    if (s1_digit + s2_digit  == sum_digit || 
                        s1_digit + s2_digit + 1 == sum_digit)
                        continue;
                    else
                        return false;
                else
                    if (s1_digit + s2_digit + carry == sum_digit)
                        continue;
                    else
                        return false;
            }
            return true;
        }       

        
        // Assigns value to a letter c
        // Returns false if led the puzzle to be inconsistent
        //
        bool assign (char c, int value)
        {
            // you can't reassign variables 
            if (assignments.find (c) != assignments.end ())
                return false;
               
            // you can't assign to c restricted values
            if (individual_restrictions[c].find (value) != 
                    individual_restrictions[c].end ())
                return false;
            
            // can't assign an already used value
            if (global_domain[value] == false)
                return false;


            // update attributes
            assignments[c] = value;
            global_domain[value] = false;

            if (isConsistant ())
                return true;
            else
                return false;
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
    cout << puzzle.assign ('A', 1) << endl;
}
