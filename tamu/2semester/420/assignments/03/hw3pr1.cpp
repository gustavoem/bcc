#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

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

    
        // Stores the index of the next variable to be assigned
        // 
        unsigned int next_var;


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
            if (i < s.length () && assignments.find (s[i]) == assignments.end ())
                return false;
            else
                return true;
        }


        void init_letters ()
        {
            set<char> letters_set;
            string s;
            stringstream ss;
            ss << term1 << term2 << sum;
            s = ss.str ();

            for (unsigned int i = 0; i < s.length (); i++)
                letters_set.insert (s[i]);
            
            for (set<char>::iterator it = letters_set.begin (); it != letters_set.end (); ++it)
                letters.push_back (*it);
        }

    public:

        // Default Constructor
        //
        Cryptomathic (string string1, string string2, string string3)
        {
            term1 = string1;
            term2 = string2;
            sum = string3;
            next_var = 0;
                
            for (unsigned int i = 0; i < 10; i++)
                global_domain.push_back (true);
            
            init_letters ();
            restrict_domain ();
            reorder_var ();
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
                

                cout << "Determined carry: " << carry << endl;

                // we are assuming that these numbers are defined 
                int s1_digit = getValue (term1, i);
                int s2_digit = getValue (term2, i);
                int sum_digit = getValue (sum, i);
                
                

                if (carry == -1)
                    if ((s1_digit + s2_digit) % 10  == sum_digit || 
                        (s1_digit + s2_digit + 1) % 10 == sum_digit)
                        continue;
                    else
                    {
                        cout << "Failed with uncertain carry" << endl;
                        return false;
                    }
                else
                    if ((s1_digit + s2_digit + carry) % 10 == sum_digit)
                        continue;
                    else
                    {
                        cout << "Failed with certain cary" << s1_digit << " + " << s2_digit << " + " << carry << "!= " << sum_digit<<endl;
                        return false;
                    }
            }
            return true;
        }       

        
        // Assigns value to a letter c
        // Returns false if led the puzzle to be inconsistent
        //
        bool assign (char c, int value)
        {
            bool answ = true;
            // you can't reassign variables 
            if (assignments.find (c) != assignments.end ())
            {
                answ = false;
                cout << "tried to reassign" << endl;
            }
               
            // you can't assign to c restricted values
            if (individual_restrictions[c].find (value) != 
                    individual_restrictions[c].end ())
            {
                answ = false;
                cout << "assigned bad value" << endl;
            }
            
            // can't assign an already used value
            if (global_domain[value] == false)
                answ = false;


            // update attributes
            assignments[c] = value;
            global_domain[value] = false;
            next_var++;

            cout << "Verifying if it is consistant" << endl;

            if (isConsistant () && answ)
                return true;
            else
                return false;
        }
        
        
        // Return next letter to be assigned a value
        //
        char getNextLetter ()
        {
            return letters[next_var];
        }

        // Returns the map letter->value
        //
        map<char, int> getAssignments ()
        {
            return assignments;
        }


        // Returns true if all variables are assigned
        // 
        bool allAssigned ()
        {
            return next_var == letters.size ();
        }


        // Prints current assignments
        //
        void printAssignments ()
        {
            for (map<char,int>::iterator it = assignments.begin (); 
                    it != assignments.end (); ++it)
                cout << it->first << " => " << it->second << '\n';
        }
};


map<char, int> solve_puzzle (Cryptomathic start_state)
{
    vector<Cryptomathic> stack;
    stack.push_back (start_state);
    map<char, int> answer;
    
    int debug = 0;

    while (stack.size () != 0)
    {
        Cryptomathic state = stack.back ();
        stack.pop_back ();
        
        cout << "DFS Loop: " << endl;
        state.printAssignments ();
        
        if (state.allAssigned ()) // found solution
        {
            cout << "think its all assigned" << endl;
            return state.getAssignments ();
        }

        // otherwise continue searching
        char next_letter = state.getNextLetter ();
        cout << "Letter to open: " << next_letter << endl;
        for (unsigned int i = 0; i <= 9; i++)
        {
            Cryptomathic child (state);

            bool answ = child.assign (next_letter, i);
            cout << "State to be verified: " << endl;
            child.printAssignments ();
            cout << "Consistant: " << answ << endl;
            if (answ)
            {
                stack.push_back (child);
            }
            // else {
                // if (child.getAssignments ()['A'] == 4 //&&
                    // child.getAssignments ()['E'] == 5 &&
                    // child.getAssignments ()['M'] == 1 && 
                    // child.getAssignments ()['N'] == 6 &&
                    // child.getAssignments ()['O'] == 0 &&  
                    // child.getAssignments ()['R'] == 8 
                    // )
                // {
                // debug++;
                // if (debug == 9)
                     // while (1);
                // }
            //}
        }
    }

    return answer;
}

int main ()
{
    string string1;
    string string2;
    string string3;

    cin >> string1;
    cin >> string2;
    cin >> string3; 
    
    reverse (string1.begin (), string1.end ());
    reverse (string2.begin (), string2.end ());
    reverse (string3.begin (), string3.end ());

    Cryptomathic puzzle (string1, string2, string3);
    map<char, int> solution = solve_puzzle (puzzle);
        
    cout << "Do I ever come here?" << endl;

    for (map<char,int>::iterator it = solution.begin (); it != solution.end (); ++it)
        cout << it->first << " => " << it->second << endl;
}
