#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main () 
{
    string line;
    string file_name;
    cin >> file_name;
    ifstream myfile (file_name);
    
    if (myfile.is_open())
    {
        while (getline (myfile,line))
        {
            // get the left part
            unsigned int division = line.find (":-");
            string left_var = line.substr (0, division);
            cout << "left_predicate: " << left_var << "|\n";
            string right_part = line.substr (division + 2);

            while (right_part != ".")
            {
                unsigned int comma_index;
                string right_var = right_part.substr (0, )
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    return 0;
}
