const int x=A1;
const int y=A2;
const int key=A3;

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
    valuex=analogRead(x);
    Serial.print(valuex);
    Serial.print(" y: ");
    valuey=analogRead(y);
    Serial.print(valuey);
    Serial.print(" key: ");
    valuekey=analogRead(key);
    Serial.println(valuekey);
    delay(1000);
}
