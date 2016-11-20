# Arduino-SilverBellsFloat2016
Arduino sketches used on the LMN 2016 Lansing Silver Bells in the City Electric Light Parade Float's side marquees.
There are three (4) Arduinos: 2 Magic Wands and 2 Mega-Blocks. 

The 2 Magic Wand kiosk panels were loaded with identical code that simply runs Test patterns. Where it simply needed to be tweeked to fit the size of strand and hold the power enable ON.

The 2 Mega-Block were placed on sides and used as marquees. Where each panel is compiled with the "#defined PORT" vs STARBOARD commented or un-commented out, as to properly match the panels orientation.

Both sketches use and combine Adafruit NeoPixel and NeoMatrix libraries. The Magic Wand panels use WS2811 RGB LED's however the NeoPixel strandtest was boring. Rather the Adafruit_WS2801 strandtest using the NeoPixel library was used.

The Mega-Block Marquees use the NeoMatrix library which in turn calls the NeoPixel library. This implementation has a local copy of these libraries that can use a DEFINE to implement either WS2801 or WS2811.
