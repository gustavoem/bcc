/*
Sample Solution-1 for Lab-1, Problem-4
Add your own INPUT/OUTPUT code to test it.
*/
#include <stdio.h>
unsigned int input;  

unsigned int output;  




inline void read_inputs_from_ip_if(){
    scanf ("%u", &input);
}

inline void write_output_to_op_if(){
    printf ("%u\n", output);
}



//The code segment which implements the decision logic
inline void control_action(){

	//Reset output
	output = 0;
	
	//Requirement 1, 2, 3
	switch (input & 0xf)
	{
		case 5:
		case 7:
		case 13:
			output =  0x1;
	}

	//Requirement 4
	switch (input & 0x31)
	{
		case 32:
		case 49:
			output = output | 0x2;
	}

	//Requirement 5
	if ((input & 0xc0) == 12)
			output = output | 0x4;

}


//The main program
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
