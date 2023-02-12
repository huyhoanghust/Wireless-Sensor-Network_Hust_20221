#include <IRremote.h>
#define receiver 14
/*-----( Declare objects )-----*/
IRrecv irrecv(receiver); // create instance of 'irrecv'
decode_results resultxs;  // create instance of 'decode_results'
/*-----( Declare Variables )-----*/

void infrared()
{
    if (irrecv.decode()) // have we received an IR signal?
    {
        Serial.println(resultxs.value, HEX);
        // translateIR();
        // if (results.value == 0x1FE50AF)
        // {
        //     digitalWrite(device, !digitalRead(device));
        //     delay(100);
        // }
        // else
        // {
        //     Serial.println("Wrong button pressed");
        //     delay(100);
        // }

        irrecv.resume(); // receive the next value
    }
}
