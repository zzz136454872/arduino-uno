#include<MsTimer2.h>

int count=0;

void show() {
    Serial.print("in ");
    Serial.println(count++);
}
    
void setup() {
    Serial.begin(9600);
    MsTimer2::set(500,show);
    MsTimer2::start();
}

void loop() {
    delay(2550);
    Serial.println("in loop");
}
