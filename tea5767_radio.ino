
//V0  for diplaying station freq
//V1 for  tune down
//V2 for tune up
//V3 for volume control

#include <Wire.h>
#include <radio.h>
#include <TEA5767.h>
#include <BlynkSimpleEsp8266.h>
#include<Blynk.h>
#define BLYNK_PRINT Serial

/// The band that will be tuned by this sketch is FM.
#define FIX_BAND RADIO_BAND_FM

/// The station that will be tuned by this sketch is 89.30 MHz.
#define FIX_STATION 8930

TEA5767 radio;    // Create an instance of Class for Si4703 Chip
char ssid[] = "eeee";
char pass[] = "1234abcd";

uint8_t test1;
byte test2;
char auth[] = ""; // Enter Auth code here
int st[]={9110,9190,9270,9350,9430,9500,9830,10130,10290,10400};
int l=sizeof(st)/sizeof(st[0]);
int x=0;
BlynkTimer timer;
/// Setup a FM only radio configuration
/// with some debugging on the Serial port
void setup() {
  // open the Serial port
  timer.setInterval(1000L,myTimerEvent);
  Serial.begin(57600);
  Serial.println("Radio...");
  delay(200);
  Blynk.begin(auth, ssid, pass);

  // Initialize the Radio 
  radio.init();

  // Enable information to the Serial port
  radio.debugEnable();

  // HERE: adjust the frequency to a local sender
  radio.setBandFrequency(FIX_BAND,st[x]); 
  radio.setVolume(1);
  radio.setMono(false);
} // setup

BLYNK_WRITE(V2)//TUNE UP
{
  int *dptr;
  dptr = new int;
  *dptr=param.asInt();
if(*dptr==1)
{x++;
Serial.println(x);
Serial.println(l);
if(x>=l)
  {x=0;
    }
  radio.setBandFrequency(FIX_BAND, st[x]);

}
delete dptr;

  }
  
BLYNK_WRITE(V1)//Tune Down
{
  int *dptr;
  dptr = new int;
  *dptr=param.asInt();
if(*dptr==1)
{//right();
  x--;
  Serial.println(x);
Serial.println(l);
  if(x=0)
  {x=l;
    }
  radio.setBandFrequency(FIX_BAND, st[x]);
  
  }
delete dptr;
 
  }
BLYNK_WRITE(V3)//Volume
{
  int *dptr;
  dptr = new int;
  *dptr=param.asInt();
  if(*dptr==1)
  radio.setMute(1);
  else{
    radio.setMute(0);
   
  }

delete dptr;
 
  }


void myTimerEvent()
{ 
  float freq=float(st[x])/100;
  
  Blynk.virtualWrite(V0,freq);
  }
  
 

void loop() {

timer.run();
Blynk.run();
} // loop


