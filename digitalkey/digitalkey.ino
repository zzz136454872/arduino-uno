const int x=4;
const int y=2;
const int key=3;

void setup() {
    pinMode(x,INPUT);
    pinMode(y,INPUT);
    pinMode(key,INPUT);
    Serial.begin(9600);
}

void loop() {
    int valuex;
    int valuey;
    int valuekey;
    Serial.print("x: ");
    valuex=digitalRead(x);
    Serial.print(valuex);
    Serial.print(" y: ");
    valuey=digitalRead(y);
    Serial.print(valuey);
    Serial.print(" key: ");
    valuekey=digitalRead(key);
    Serial.println(valuekey);
    delay(1000);
}
