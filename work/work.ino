//#include<TimerOne.h>
#include<TM1637.h>

#define clk 2
#define dio 3
#define vx A0
#define vy A1
#define sw A2

#define debug

int8_t time[4]={0,0,0,0};
bool clockPoint;

TM1637 displayer();

void setup()
{
    displayer.set(0); //darkest
    displayer.init(); //clear display
}

enum state{work,change};

void update() {
    
}

void change() {
    

void loop() {
    

}
    

