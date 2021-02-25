#include <Arduino.h>

#include <Adafruit_DotStar.h>
#include <Bounce2.h>
#include <Keyboard.h>

#define NUMPIXELS 1 
#define DATAPIN   7
#define CLOCKPIN  8

#define BTN1 4
#define BTN2 3
#define LED 13

Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
Bounce2::Button b1 = Bounce2::Button();
Bounce2::Button b2 = Bounce2::Button();
static bool isMuted = true;

void setColor(uint8_t r, uint8_t g, uint8_t b);



void setup() {
  strip.begin();
  strip.setBrightness(80);
	setColor(0, 0x44, 0);
	digitalWrite(LED, isMuted ? HIGH : LOW);
	b1.attach(BTN1, INPUT_PULLUP);
	b2.attach(BTN2, INPUT_PULLUP);
	Keyboard.begin();
}

void setColor(uint8_t r, uint8_t g, uint8_t b) {
	strip.setPixelColor(0, strip.gamma32(strip.Color(g, r, b)));
	strip.show();
}


void setMute(bool value) {
	if (value != isMuted) {
		isMuted = value;
		digitalWrite(LED, value ? HIGH : LOW);
		Keyboard.press(KEY_LEFT_CTRL);
		Keyboard.press(KEY_LEFT_SHIFT);
		Keyboard.press('M');
		delay(80);
		Keyboard.releaseAll();
	}
}

void loop() {
	b1.update();
	b2.update();

	if(b1.fell()) {
		setMute(true);
		setColor(0, 0, 0x66);
	}
	if(b1.rose()) {
		setMute(false);
	}

	if(b2.fell()) {
		setColor(0, 0x44, 0);
		setMute(false);
	}
	if(b2.rose()) {
		setMute(true);
	}
}