#include <SoftwareSerialWithHalfDuplex.h>

#define comPin 3

SoftwareSerialWithHalfDuplex TF1637(comPin,comPin,false,false);


void setup(){
  TF1637.begin(115200);
  Serial.begin(9600);

}

void loop(){
  if(TF1637.available()){
    Serial.println(TF1637.read(),HEX);
  }
}
