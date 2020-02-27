#define con 3
#define in 4
#define down 10
 
void setup() {
    Serial.begin(9600);
    pinMode(con,OUTPUT);
    pinMode(in,INPUT);
    pinMode(down,OUTPUT);
    digitalWrite(down,LOW);
}

int i=0;

void loop() {
    int in1;
    digitalWrite(con,HIGH);
    delay(50);
    in1=digitalRead(in);
    Serial.println(in1);
    delay(200);
}
