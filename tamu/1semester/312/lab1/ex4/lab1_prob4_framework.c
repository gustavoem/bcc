// CSCE312: Lab-1 Problem-3 framework

/* ***   README   **** */

/*
This example program sounds the bell when driver is on seat 
AND haven't closed the doors. Use the general framework and the function 
shells, replace the code inside  the control_action() function with your 
own code to do problems 3 and 4.

Note: This code is designed to run in an infinite loop to mimic a real control system. 
If you prefer to read the inputs from a file, modify the code appropriately to terminate the
loop when all the inputs have been processed.

Turning in this file without your code will result in zero points being awarded for this problem.

run this file as : gcc filename.c -o executableName

*/


#include <stdio.h> //This is useful to do i/o to test the code 

unsigned int input;
unsigned int output;

enum INMASKS {
    DOSM  = 1, 
    DSBFM = 2,   
    ERM   = 4,
    DCM   = 8,
    KICM  = 16,
    DLCM  = 32,
    BPM   = 64,
    CMM   = 128
};

enum OUTMASK {
    BELLM = 1,
    DLAM  = 2,
    BAM   = 4
};


inline unsigned int mask (unsigned int x, unsigned int a)
{
    return (x & a);
}


void read_inputs_from_ip_if ()
{
    scanf ("%u", &input);
}


void write_output_to_op_if ()
{
    printf ("%u\n", output);
}


//The code segment which implements the decision logic
void control_action(){
    output = 0;
    
    if (mask (input, ERM) && (!(mask (input, DSBFM) && mask (input, DCM))))
        output += BELLM;

    if (mask (input, DLCM) && ((!mask (input, KICM)) || mask (input, DOSM)))
        output += DLAM;

    if (mask (input, BPM) && mask (input, CMM))
        output += BAM;
}

/* ---     You should not have to modify anything below this line ---------*/

int main(int argc, char *argv[])
{
	
	/*The main control loop which keeps the system alive and responsive for ever, 
	until the system is powered off */
	for (; ; )
	{
		read_inputs_from_ip_if();
		control_action();
		write_output_to_op_if();

	}
	
	return 0;
}
