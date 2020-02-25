
#define uppin 3
#define downpin 4
#define nopin 5
 
void setup() {
    Serial.begin(9600);
    pinMode(uppin,INPUT_PULLUP);
    //pinMode(downpin,INPUT_PULLDOWN);
    pinMode(nopin,INPUT);
}

void loop() {
    int in1,in2,in3;
    in1=digitalRead(uppin);
    in2=digitalRead(downpin);
    in3=digitalRead(nopin);

    Serial.print("up: ");
    Serial.println(in1);
    //Serial.print("down: ");
    //Serial.println(in1);
    Serial.print("no: ");
    Serial.println(in3);
    delay(2000);
}
