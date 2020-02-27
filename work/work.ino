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
bool timepoint = true;

TM1637 displayer();

enum state{work,change};
int counter;
int vx,vy;

state now;

void setup()
{
    displayer.set(0); //darkest
    displayer.init(); //clear display
    time[0]=1;
    time[1]=2;
    time[2]=3;
    time[3]=4;
    displayer.display(time);
    displayer.point(clockPoint);
    counter=0;
    now=work;
#ifdef debug
    Serial.begin(9600);
#endif
}

void change() {
    static int c=0;
    static int loc=3;
    if(c==0)
    {
        if(vx < 100)
        {
            time[loc]--;
            if(time[loc]==-1)
            {
                if(loc==2)
                {
                    time[loc]=5;
                }
                else
                    time[loc]=9;
            }
            
        }
        else if(vx > 1000)
        {
            time[loc]++;
            if(loc==2)
            {
                if(time[loc]==6)
                    time[loc]==0;
            }
            else
            {
                if(time[loc]==10)
                    time[loc]=0;
            }
        }
        else if(vy < 100)
        {
            loc=(loc - 1)%4;
        }
        else if(vy > 1000)
        {
            loc=(loc+1)%4;
        }
        else
            c++;
    }
    else 
    {
        c++;
        c=c%4;
    }
}   

void update() {
    TODO: update function
    if(counter=

}

void loop() 
{
    counter++;
    dx=analogRead(vx);
    dy=analogRead(vy);
    if((vx<100||vx>1000||vy<100||vy>1000))
        now=change;
    if(counter > 1000)
    {
        now=work;
        counter=0;
    }
    if(now==change)
        change();
    //if(now==work)
    update();
    displayer.point(clockPoint)
    displayer.display(time);
    delay(50);
}
    
