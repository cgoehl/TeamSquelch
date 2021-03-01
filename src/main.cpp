#include <Arduino.h>

#include <Bounce2.h>
#include <Keyboard.h>

#define BTN1 16
#define BTN2 14
#define BTN3 18
#define LED1 9
#define LED2 6
#define LED3 10

Bounce2::Button b1 = Bounce2::Button();
Bounce2::Button b2 = Bounce2::Button();
Bounce2::Button b3 = Bounce2::Button();
static bool isPcMuted = true;

void setInitialMute(bool value) {
 isPcMuted = value;
 analogWrite(LED1, value ? 127 : 0);
 analogWrite(LED2, value ? 0 : 127);
}

void setup() {
	b1.attach(BTN1, INPUT_PULLUP);
	b2.attach(BTN2, INPUT_PULLUP);
	b3.attach(BTN3, INPUT_PULLUP);
	Serial.begin(115200);
	Keyboard.begin();
	setInitialMute(true);
}

void setLed(uint8_t pin, bool isOn) {
	analogWrite(pin, isOn ? 255 : 0);
}

void setMute(bool value) {
	if (value != isPcMuted) {
		isPcMuted = value;
		Keyboard.press(KEY_LEFT_CTRL);
		Keyboard.press(KEY_LEFT_SHIFT);
		Keyboard.press('M');
		delay(30);
		Keyboard.releaseAll();
	}
}


void loop() {
	b1.update();
	b2.update();
	b3.update();

	if(b1.fell()) {
		setMute(false);
		analogWrite(LED1, 127);
		analogWrite(LED2, 0);
	}
	if(b1.rose()) {
		setMute(true);
		analogWrite(LED1, 255);
	}

	if(b2.fell()) {
		setMute(true);
		analogWrite(LED1, 0);
		analogWrite(LED2, 127);
	}
	if(b2.rose()) {
		setMute(false);
		analogWrite(LED2, 255);
	}

	if(b3.fell()) {
		setInitialMute(!isPcMuted);
	}

	analogWrite(LED3, isPcMuted ? 127 : 0);
}