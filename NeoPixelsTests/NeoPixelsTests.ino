#include <Adafruit_NeoPixel.h>

#define NUMPIXELS      30

#define PIN0            6 // analogIn 0 -> symbal
#define PIN1            4 // analogIn 1 -> right tam
#define PIN2            5 // analogIn 2 -> bass drum
#define PIN3            7 // analogIn 3 -> left tam

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels0 = Adafruit_NeoPixel(NUMPIXELS, PIN0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(NUMPIXELS, PIN3, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pixels0.begin(); // This initializes the NeoPixel library.
  pixels1.begin(); // This initializes the NeoPixel library.
  pixels2.begin(); // This initializes the NeoPixel library.
  pixels3.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600); // send and receive at 9600 baud
}

int brightness = 0;
int lst0, lst1, lst2, lst3 = 0; // last average volume
int vlm0, vlm1, vlm2, vlm3 = 0; // average volume
int hit0, hit1, hit2, hit3 = 0; // trigger
int brt0, brt1, brt2, brt3 = 0; // brightness

#define DECAY_RATE 200/256
#define HIT_THRESHOLD 200
#define BASE_THRESHOLD 2

void loop(){
  vlm0 = abs(analogRead(0) - lst0) + vlm0 * DECAY_RATE;
  vlm1 = abs(analogRead(1) - lst1) + vlm1 * DECAY_RATE;
  vlm2 = abs(analogRead(2) - lst2) + vlm2 * DECAY_RATE;
  vlm3 = abs(analogRead(3) - lst3) + vlm3 * DECAY_RATE;

  lst0 = analogRead(0);
  lst1 = analogRead(1);
  lst2 = analogRead(2);
  lst3 = analogRead(3);
  
  if(vlm0 > HIT_THRESHOLD && !hit0){
    hit0 = 1;
    Serial.print(0);
    Serial.print(" ");
    Serial.println(vlm0);
    brt0 = 255;
  }else{
    if(brt0 > 0){
      brt0 --;
    }
    if(vlm0 < BASE_THRESHOLD) hit0 = 0;
  }

  if(vlm1 > HIT_THRESHOLD && !hit1){
    hit1 = 1;
    Serial.print(1);
    Serial.print(" ");
    Serial.println(vlm1);
    brt1 = 255;
  }else{
    if(brt1 > 0){
      brt1 --;
    }
  }

    if(vlm1 < BASE_THRESHOLD) hit1 = 0;

  if(vlm2 > HIT_THRESHOLD && !hit2){
    hit2 = 1;
    Serial.print(2);
    Serial.print(" ");
    Serial.println(vlm2);
    brt2 = 255;
  }else{
    if(brt2 > 0){
      brt2 --;
    }
    if(vlm2 < BASE_THRESHOLD) hit2 = 0;
  }

  if(vlm3 > HIT_THRESHOLD && !hit3){
    hit3 = 1;
    Serial.print(3);
    Serial.print(" ");
    Serial.println(vlm3);
    brt3 = 255;
  }else{
    if(brt3 > 0){
      brt3 --;
    }
    if(vlm3 < BASE_THRESHOLD)hit3 = 0;
  }


  // center drum
  for(int i=0;i<NUMPIXELS;i++){
    pixels2.setPixelColor(i, pixels2.Color(brt2,brt2,brt2));
  }
  pixels2.show();
  
  
  
  
  // right tam
     int r1 ;
     int g1 ;
     int b1 ;
     int H1 ;
     int S1 ;
     int BB1 ;

     
      H1 = 0 ;
      BB1 = brt1 ;
    if(brt1 < 100){
      S1 = brt1 ;
    }else if(brt1 <155){
      S1 = 100 ;
    }else{
      S1 = - brt1 + 255 ;
    }

    int max=BB1;
    int min=max-S1*max/255;
    int hue=H1;

	if(hue<60){
	   r1=max;
	   g1=min+hue*(max-min)/60;
	   b1=min;
	}else if(hue<120){
	  r1=max-(hue-60)*(max-min)/60;
	  g1=max;
	  b1=min;
	}else if(hue<180){
	  r1=min;
	  g1=max;
	  b1=min+(hue-120)*(max-min)/60;
	}else if(hue<240){
	  r1=min;
	  g1=max-(hue-180)*(max-min)/60;
	  b1=max;
	}else if(hue<300){
	  r1=min+(hue-240)*(max-min)/60;
	  g1=min;
	  b1=max;
	}else{		//hue<360
	  r1=max;
	  g1=min;
	b1=max-(hue-300)*(max-min)/60;
	}

  for(int i=0;i<10;i++){
    pixels1.setPixelColor(i, pixels1.Color(r1,g1,b1));
  }
  pixels1.show();
}




