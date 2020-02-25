
int inpin=A0;
int outpin=A1;

void setup() {
    pinMode(inpin,INPUT);
    pinMode(outpin,OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int i;
    int out;
    for(i=0;i<20;i++)
    {
        Serial.print(i*10);
        analogWrite(outpin,i*10);
        delay(50);
        Serial.print(" : ");
        out=analogRead(inpin);
        Serial.println(out);
        delay(1000);
    }
}
