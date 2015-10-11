//CSCE312: Lab-3 Problem-1 Timing Framework

/* ***   README   **** */
/*This file is a framework: i.e. there is no actual code whose execution time will be
measured. You need to populate the appropriate functions with the code that you wrote 
for the previous problems in order to get useful data. 

Turning in this file without your code will result in zero points being awarded for this problem.

run this file as: gcc FileName.c -o ExecutableName -lrt 

*/


#include <stdio.h>
#include <time.h>
// Macro definitions to ensure portablity between both sun.cs and linux.cs

#if defined(sun)
    #define CLOCKNAME CLOCK_HIGHRES
        
#else
    #define CLOCKNAME CLOCK_PROCESS_CPUTIME_ID
#endif
    

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


/* ---     You should not have to modify anything below this line ---------*/

/*timespec diff from
http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/
*/
struct timespec diff(struct timespec start, struct timespec end)
 {
    struct timespec temp;
    //the if condition handles time stamp end being smaller than than 
    //time stamp start which could lead to negative time.

     if ((end.tv_nsec-start.tv_nsec)<0) {
          temp.tv_sec = end.tv_sec-start.tv_sec-1;
          temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
      } else {
          temp.tv_sec = end.tv_sec-start.tv_sec;
          temp.tv_nsec = end.tv_nsec-start.tv_nsec;
      }
  return temp;
 }

int main(int argc, char *argv[])
{
    unsigned int cpu_mhz;
    unsigned long long int begin_time, end_time;
    struct timespec timeDiff,timeres;
    struct timespec time1, time2, calibrationTime;
    
    clock_gettime(CLOCKNAME, &time1);
    clock_gettime(CLOCKNAME, &time2);
    calibrationTime = diff(time1,time2); //calibration for overhead of the function calls
    clock_getres(CLOCKNAME, &timeres);  // get the clock resolution data
    
    read_inputs_from_ip_if(); // get the sensor inputs
    
    clock_gettime(CLOCKNAME, &time1); // get current time
    control_action();       // process the sensors
    clock_gettime(CLOCKNAME, &time2);   // get current time

    write_output_to_op_if();    // output the values of the actuators
    
    timeDiff = diff(time1,time2); // compute the time difference

    printf("Timer Resolution = %u nanoseconds \n ",timeres.tv_nsec);
    printf("Calibrartion time = %u seconds and %u nanoseconds \n ", calibrationTime.tv_sec, calibrationTime.tv_nsec);
    printf("The measured code took %u seconds and ", timeDiff.tv_sec - calibrationTime.tv_sec);
    printf(" %u nano seconds to run \n", timeDiff.tv_nsec - calibrationTime.tv_nsec);
    
    return 0;
}
