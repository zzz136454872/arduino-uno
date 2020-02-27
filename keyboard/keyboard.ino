/* @author f4prime
 * @email zzz136454872@163.com
 */

#include <Keyboard.h>


void setup() {
    Serial.begin(9600);
    Serial.println("start");
    Keyboard.begin();
    Keyboard.println("test keyboard");
}

void loop() {
    
}

// failed
// the uno and nano board does not support keyboard or 
// mouse. 
