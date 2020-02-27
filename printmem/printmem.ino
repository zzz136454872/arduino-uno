//根据长度显示指定位置内存
//parameter:
//info: message for the print
//start: start address
//len: length 
void printmem(const void * const start, const int len, const char* info) 
{
    unsigned char *ptr = (unsigned char*)start;
    int i;
    Serial.print(info);
    for(i=0;i<len;i++)
    {
        if(i%16==0)
            Serial.write('\n');
        if(ptr[i] < 0xf)
            Serial.print(0);
        Serial.print(ptr[i],HEX);
        Serial.write(' ');
    }
    Serial.write('\n');
}

/* @author f4prime
 * @email zzz136454872@163.com
 */

void setup() {
    Serial.begin(9600);

    
}

void loop() {
    delay(3000);
    int i;
    char test[100];
    for(i=0;i<100;i++)
        test[i]=i;
    //char test[] ={0x9,0x8,0x8,0xc,0xc,0x9,0xd,0xd};
    printmem(test,100,"test");
}
