/*******************************************************************************

 Lansing Makers Network
 ------------------------------

 Marquee20x10.ino - Lansing Silver Bells in the City 
                    Electric Light Parade Float's side marquees.

 Author: Michael P. Flaga

 Arduino based WS2811 20W x 10H 
 https://www.aliexpress.com/item/WS2801IC-LED-Pixel-module-DC12V-waterproof-30mm-diameter-6pcs-5050-SMD-RGB-20pcs-a-string/718859966.html
 
 This sketch combines elements of .\Adafruit_WS2801\examples\strandtest and 
 .\Adafruit_NeoMatrix\examples\matrixtest. The Adafruit_NeoPixel.cpp is minorly 
 modified to work on the WS2801 as SPI.

 This work is licensed under a Creative Commons Attribution-ShareAlike 3.0
 Unported License (CC BY-SA 3.0) http://creativecommons.org/licenses/by-sa/3.0/

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

*******************************************************************************/

#include "Adafruit_NeoPixel.h"  // Need to use modified Library to support WS2801
#include "Adafruit_NeoMatrix.h" // also needs to modified as to call the local Adafruit_NeoPixel

#define PIN 6

#define PORT //(Driver Side), Comment out for Starboard (Passenger Side)

// object to handle matrix as a matrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(20, 10, PIN,
                            NEO_MATRIX_BOTTOM  +
#ifdef PORT
                            NEO_MATRIX_RIGHT +
#else // must be Starboard
                            NEO_MATRIX_LEFT +
#endif //PORT
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

// object to handle matrix as a single string.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(((2 * 10) * 20), PIN, NEO_GRB + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

void setup() {
  Serial.begin(115200);
  Serial.println(F("LMN Marquee Started"));

  // initial setup of matrix
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(250);
  matrix.setTextColor(colors[0]);

  // POST Test Pattern of RGB LEDs
  colorWipe(strip.Color(255, 0, 0), 1); // Red
  colorWipe(strip.Color(0, 255, 0), 1); // Green
  colorWipe(strip.Color(0, 0, 255), 1); // Blue
}

void loop() {
  
  colorWipe(strip.Color(255, 0, 0), 10); // Red
  colorWipe(strip.Color(0, 255, 0), 10); // Green
  colorWipe(strip.Color(0, 0, 255), 10); // Blue
  
  marque("Lansing Makers Network", 120);
  theaterChase(strip.Color(127, 127, 127), 100); // White
  theaterChase(strip.Color(127, 0, 0), 100); // Red
  
  marque("Your Friendly Makerspace", 120);
  theaterChase(strip.Color(0, 127, 0), 100); // Green
  theaterChase(strip.Color(0, 0, 127), 100); // Blue

  marque("Silver Bells in the City", 120);
  rainbow(10);
  
  marque("Electric Light Parade", 120);
  rainbowCycle(10);
  
  marque("Happy Holidays", 120);
  theaterChaseRainbow(75);
  
  marque("Elf Makerspace", 120);

} // end loop()

void marque(char* message, uint8_t wait) {
  
  uint8_t posY = 1;
  int posX = matrix.width(); // start initial print from the right most

  int messageLength = -1 * ((strlen(message) * 6) + 6); 
  // Note: each character is 6 pixels wide and 8 pixels tall, then pad another character at end to give chance to read.

  while (--posX >= messageLength) {
    matrix.fillScreen(0);
    matrix.setCursor(posX, posY);
    matrix.print(message);
    //Serial.print(F("L-Print-Ended X = "));
    matrix.show();
    delay(wait);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
