/* @author f4prime
 * @email zzz136454872@163.com
 * @function test if the led marked as L is
 * linked to digital pin 13
 */

#define testPin 13

void setup() {
    Serial.begin(9600);
    Serial.print("start");
    pinMode(testPin,OUTPUT);
}

void loop() {
    Serial.println("high");
    digitalWrite(testPin,HIGH);
    delay(1000);
    Serial.println("low");
    digitalWrite(testPin,LOW);
    delay(1000);
}

