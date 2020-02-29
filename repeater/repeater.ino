/* @author f4prime
 * @email zzz136454872@163.com
 */


void setup() {
    Serial.begin(9600);
    Serial.println("start");

    
}

void loop() {
    String tmp;
    while(Serial.peek()==-1)
        ;
    tmp=Serial.readString();
    Serial.println(tmp.length());
    Serial.print(tmp);
    delay(100);
    //接收到的string 是包括换行符的。
}
