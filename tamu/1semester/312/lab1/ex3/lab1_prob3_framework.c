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

unsigned int engine_running;
unsigned int driver_seat_belt;
unsigned int doors_closed;
unsigned int door_lock_lever;
unsigned int key_inside;
unsigned int driver_on_seat;
unsigned int brake_pedal;
unsigned int car_moving;
unsigned int bell;
unsigned int dla;
unsigned int ba;

void read_inputs_from_ip_if(){
    scanf ("%u %u %u %u %u %u %u %u", &engine_running, &driver_seat_belt, &doors_closed,
            &door_lock_lever, &key_inside, &driver_on_seat, &brake_pedal, &car_moving);
}

void write_output_to_op_if(){
    //to display/print the state of the 3 actuators (DLA/BELL/BA)
    printf ("%u %u %u\n", dla, bell, ba);
}


//The code segment which implements the decision logic
void control_action(){

    /*
    The code given here sounds the bell when driver is on seat 
    AND hasn't closed the doors. (Requirement-2)
    Replace this code segment with your own code to do problems 3 and 4.
    */

    if (engine_running && ((!driver_seat_belt) || (!doors_closed)))
        bell = 1;
    else
        bell = 0;

    if (door_lock_lever && ((!key_inside) || (driver_on_seat)))
        dla = 1;
    else
        dla = 0;

    if (brake_pedal && car_moving)
        ba = 1;
    else
        ba = 0;

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
