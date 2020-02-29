/* @author f4prime
 * @email zzz136454872@163.com
 */

#include<SoftwareSerial.h>

SoftwareSerial ss(3,4);
// 3->rx  4->tx

void setup() {
    Serial.begin(9600);
    Serial.println("start");
    ss.begin(9600);
    ss.println("start");
}

void loop() {
    String tmp;
    while(Serial.peek()==-1)
        ;
    tmp=Serial.readString();
    ss.print("from computer: ");
    delay(100);
    ss.print(tmp);
    delay(100);
    //接收到的string 是包括换行符的。
}
