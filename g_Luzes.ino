//------------------------------------------------------------------------------------------------------
// FUNCOES - Luzes
//------------------------------------------------------------------------------------------------------
int color_id = 0;

void ALL_WHITE_BUZZER() {

  if(color_id != 1){

  FastLED.addLeds<WS2811, LED_PIN_DIR, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811, LED_PIN_ESQ, RGB>(leds, NUM_LEDS);

  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    // Turn our current led on to white, then show the leds
    leds[whiteLed] = CRGB::White;

    // Show the leds (only one of which is set to white, from above)
    

    // Wait a little bit
    //delay(100);

    }
  
  FastLED.show();
  color_id = 1;
  }
  else {
    return;
  }
}

void ALL_GREEN_ESQ() {

  FastLED.addLeds<WS2811, LED_PIN_ESQ, RGB>(leds, NUM_LEDS);

  for (int greenLed = 0; greenLed < NUM_LEDS; greenLed = greenLed + 1) {
    // Turn our current led on to green, then show the leds
    leds[greenLed] = CRGB::Green;

    // Show the leds (only one of which is set to white, from above)
    

    // Wait a little bit
    //delay(100);

  }
  FastLED.show();
}

void ALL_GREEN_DIR() {

  FastLED.addLeds<WS2811, LED_PIN_DIR, RGB>(leds, NUM_LEDS);

  for (int greenLed = 0; greenLed < NUM_LEDS; greenLed = greenLed + 1) {
    // Turn our current led on to green, then show the leds
    leds[greenLed] = CRGB::Green;

    // Show the leds (only one of which is set to white, from above)
    

    // Wait a little bit
    //delay(100);

  }
  FastLED.show();
}

void ALL_GREEN() { // é isso...

  if (color_id != 2){
  FastLED.addLeds<WS2811, LED_PIN_DIR, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811, LED_PIN_ESQ, RGB>(leds, NUM_LEDS);

  for (int redLed = 0; redLed < NUM_LEDS; redLed = redLed + 1) {
    // Turn our current led on to red, then show the leds
    leds[redLed] = CRGB::Red;

    // Show the leds (only one of which is set to white, from above)
    

    // Wait a little bit
    //delay(100);

  }
  FastLED.show();
  color_id = 2;
  }
  else {
    return;
  }


}

void ALL_RED() { // entao....

  if (color_id != 3){
  FastLED.addLeds<WS2811, LED_PIN_DIR, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811, LED_PIN_ESQ, RGB>(leds, NUM_LEDS);

  for (int greenLed = 0; greenLed < NUM_LEDS; greenLed = greenLed + 1) {
    // Turn our current led on to green, then show the leds
    leds[greenLed] = CRGB::Green;

    // Show the leds (only one of which is set to white, from above)
    

    // Wait a little bit
    //delay(100);

  }
  color_id = 3;
  FastLED.show(); 
  } 
  else {
    return;
  }
}

void ALL_BLUE() {

  if (color_id != 4){
  FastLED.addLeds<WS2811, LED_PIN_DIR, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811, LED_PIN_ESQ, RGB>(leds, NUM_LEDS);

  for (int blueLed = 0; blueLed < NUM_LEDS; blueLed = blueLed + 1) {
    // Turn our current led on to green, then show the leds
    leds[blueLed] = CRGB::Blue;

    // Show the leds (only one of which is set to white, from above)
    

    // Wait a little bit
    //delay(100);

  }
  color_id = 4;
  FastLED.show();
  }
  else {
    return;
  }
}

void ALL_BLACK() {

  if (color_id != 5){
  FastLED.addLeds<WS2811, LED_PIN_DIR, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811, LED_PIN_ESQ, RGB>(leds, NUM_LEDS);

  for (int blackLed = 0; blackLed < NUM_LEDS; blackLed = blackLed + 1) {
    // Turn our current led on to black, then show the leds
    leds[blackLed] = CRGB::Black;

    // Show the leds (only one of which is set to white, from above)
    

    // Wait a little bit
    //delay(100);

  }
  color_id = 5;
  FastLED.show();
  }
  else {
    return;
  }


}
void ALL_YELLOW() {

  if (color_id != 6){
  FastLED.addLeds<WS2811, LED_PIN_DIR, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811, LED_PIN_ESQ, RGB>(leds, NUM_LEDS);

  for (int yellowLed = 0; yellowLed < NUM_LEDS; yellowLed = yellowLed + 1) {
    // Turn our current led on to black, then show the leds

    leds[yellowLed] = CRGB::Yellow;

    // ColorFromPalette( RainbowColors_p, colorIndex, brightness, currentBlending)
    // Show the leds (only one of which is set to white, from above)
    

    // Wait a little bit
    //delay(100);

  }
  color_id = 6;
  FastLED.show();
  }
  else {
    return;
  }
}
