#include <stdio.h>
/*
Lab-1, Problem-4, Sample soltion-2
Note: Only requirement 1,2,3,4 is covered 
modify this code to include requirement 5 also

Also add your own INPUT/OUTPUT code to test it.

*/

unsigned int input;  

unsigned int output;  



//For input interface implementation
inline void read_inputs_from_ip_if(){
    scanf ("%u", &input);
}

//For output interface implementation
inline void write_output_to_op_if(){
    printf ("%u\n", output);
}


//The code segment which implements the decision logic
inline void control_action(){

    //Requirement 1, 2, 3, 4 only
    switch (input & 0x3f) //Change to 0xff for all 5 requirements
    {
        case 5:
            output = 1;
            break;
        case 7:
            output = 1;
            break;
        case 13:
            output = 1;
            break;
        case 32:
            output = 1;
            break;
        case 34:
            output = 2;
            break;
        case 36:
            output = 2;
            break;
        case 38:
            output = 2;
            break;
        case 40:
            output = 2;
            break;
        case 42:
            output = 2;
            break;
        case 44:
            output = 2;
            break;
        case 46:
            output = 2;
            break;
        case 49:
            output = 2;
            break;
        case 51:
            output = 2;
            break;
        case 53:
            output = 3;
            break;
        case 55:
            output = 3;
            break;
        case 57:
            output = 2;
            break;
        case 59:
            output = 2;
            break;
        case 61:
            output = 3;
            break;
        case 63:
            output = 2;
            break;
        case 192:
            output = 4;
            break;
        case 193:
            output = 4;
            break;
        case 194:
            output = 4;
            break;
        case 195:
            output = 4;
            break;
        case 196:
            output = 4;
            break;
        
        case 197:
            output = 5;
            break;
        case 198:
            output = 4;
            break;
        case 199:
            output = 5;
            break;
        case 200:
            output = 4;
            break;
        case 201:
            output = 4;
            break;
        case 202:
            output = 4;
            break;
        case 203:
            output = 4;
            break;
        case 204:
            output = 4;
            break;
        case 205:
            output = 5;
            break;
        case 206:
            output = 4;
            break;
        case 207:
            output = 4;
            break;
        case 208:
            output = 4;
            break;
        case 209:
            output = 4;
            break;
        case 210:
            output = 4;
            break;
        case 211:
            output = 4;
            break;
        case 212:
            output = 4;
            break;
        case 213:
            output = 4;
            break;
        case 214:
            output = 4;
            break;
        case 215:
            output = 4;
            break;
        case 216:
            output = 4;
            break;
        case 217:
            output = 4;
            break;
        case 218:
            output = 4;
            break;
        case 219:
            output = 4;
            break;
        case 220:
            output = 4;
            break;
        case 221:
            output = 4;
            break;
        case 222:
            output = 4;
            break;
        case 223:
            output = 4;
            break;
        case 224:
            output = 6;
            break;
        case 225:
            output = 4;
            break;
        case 226:
            output = 6;
            break;
        case 227:
            output = 4;
            break;
        case 228:
            output = 6;
            break;
        case 229:
            output = 4;
            break;
        case 230:
            output = 6;
            break;
        case 231:
            output = 4;
            break;
        case 232:
            output = 6;
            break;
        case 233:
            output = 4;
            break;
        case 234:
            output = 6;
            break;
        case 235:
            output = 4;
            break;
        case 236:
            output = 6;
            break;
        case 237:
            output = 4;
            break;
        case 238:
            output = 6;
            break;
        case 239:
            output = 4;
            break;
        case 240:
            output = 4;
            break;
        case 241:
            output = 6;
            break;
        case 242:
            output = 4;
            break;
        case 243:
            output = 6;
            break;
        case 244:
            output = 4;
            break;
        case 245:
            output = 7;
            break;
        case 246:
            output = 4;
            break;
        case 247:
            output = 7;
            break;
        case 248:
            output = 4;
            break;
        case 249:
            output = 6;
            break;
        case 250:
            output = 4;
            break;
        case 251:
            output = 6;
            break;
        case 252:
            output = 4;
            break;
        case 253:
            output = 7;
            break;
        case 254:
            output = 4;
            break;
        case 255:
            output = 6;
            break;

        default:
            output = 0;
    }
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
