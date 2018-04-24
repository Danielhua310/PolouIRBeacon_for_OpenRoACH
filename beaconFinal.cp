#include "mbed.h"
#include <string>

//Motor speed constant
//Can be modified to achieve specific function
#define SPEED_PWM 0.25

//Beacon read from each (W, S, N, E) directions
AnalogIn north(p19);
AnalogIn east(p18);
AnalogIn south(p17);
AnalogIn west(p16);

//Motor write to two motor, each motor can support forward motion or backward motion
PwmOut m1_fwd(p21);
PwmOut m1_back(p22);
PwmOut m2_fwd(p23);
PwmOut m2_back(p24);

Serial pc(USBTX, USBRX);

//beacon signal read. Retreive transmitter's direction
// four direction available (W, S, N, E)
int readBeacon() {
    if(north.read() < 0.5f) return 1;
    else if(east.read() < 0.5f) return 2;
    else if(west.read() < 0.5f) return 3;
    else if(south.read() < 0.5f) return 0;
    return 5;
}
//main execution program
//first read direction by callying readBeacon()
//then write motor speed accordingly to the return of readBeacon() function
int main() {
    //en able = 1;
    int prev_dir;
    int direction;
    while(1) {
        direction = readBeacon();//get direction from beacon read
        if(direction == 1) {//if the direction is north, let both motor move forward
            m2_fwd.write(SPEED_PWM);
            m2_back.write(0);
            m1_fwd.write(SPEED_PWM);
            m1_back.write(0);
        } else if (direction == 0) {//if the direction is south, let both motor move backward
            m2_fwd.write(0);
            m2_back.write(SPEED_PWM);
            m1_fwd.write(0);
            m1_back.write(SPEED_PWM);
        } else if(direction == 2) {//if the direction is east, let left motor(m1) move backward and right motor(m2) move forward
            m2_fwd.write(SPEED_PWM);
            m2_back.write(0);
            m1_fwd.write(0);
            m1_back.write(SPEED_PWM);
        } else if(direction == 3) {//if the direction is west, let left motor(m1) move forward and right motor(m2) move backward
            m2_fwd.write(0);
            m2_back.write(SPEED_PWM);
            m1_fwd.write(SPEED_PWM);
            m1_back.write(0);
        }
    }
}