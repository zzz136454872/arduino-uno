#define com 3
#define in 4
 
void setup() {
    Serial.begin(9600);
    pinMode(com,OUTPUT);
    pinMode(in,INPUT);
}

void loop() {
    int in1;
    digitalWrite(com,high);
    Serial.println("high");
    delay(50);
    in1=digitalRead(in);
    Serial.println("in: ");
    Serial.println(in1);
    Serial.println();
    delay(5000);
}
