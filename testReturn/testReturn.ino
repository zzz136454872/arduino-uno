/* @author f4prime
 * @email zzz136454872@163.com
 */


void setup() {
    Serial.begin(9600);
    Serial.println("start");
}

void loop() {
    Serial.println("in loop");
    delay(2000);
    return;//return means restart the loop
}
