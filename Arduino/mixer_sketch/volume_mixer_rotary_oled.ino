#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RotaryEncoder.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int PIN_ENCODER_A = 8;
const int PIN_ENCODER_B = 6;
const int SW = 4;
const int amountSliders = 4;
const String sliderNames[amountSliders] = {"Master", "Music", "Browser", "Discord"};
const int increment[amountSliders] = {1, 1, 1, 1}; // Smaller increments for finer control
int displayValue[amountSliders] = {100, 100, 100, 100};
const int barWidth = 100;
const int barHeight = 7;
const int barX = 14;
const int barY = 20;

RotaryEncoder encoder(PIN_ENCODER_A, PIN_ENCODER_B, RotaryEncoder::LatchMode::FOUR3);
int sliderNumber = 0;
bool adjustingValue = false;

// Debounce variables for button and rotary actions
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool lastButtonState = HIGH;
bool buttonPressed = false;

int lastA = HIGH;
int lastB = HIGH;

// Additional variables for rotation debouncing
unsigned long lastRotationTime = 0;
const unsigned long rotationDebounceDelay = 100; // 100 milliseconds between rotations

void setup() {
  pinMode(SW, INPUT_PULLUP);
  pinMode(PIN_ENCODER_A, INPUT);
  pinMode(PIN_ENCODER_B, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();

  Serial.begin(9600);
}

void loop() {
  bool currentButtonState = digitalRead(SW);
  if (currentButtonState != lastButtonState) {
    lastDebounceTime = millis();
  }

  if (!buttonPressed && (millis() - lastDebounceTime) > debounceDelay) {
    if (currentButtonState == LOW) {
      ButtonPress();
      buttonPressed = true;
    }
  }

  if (currentButtonState == HIGH) {
    buttonPressed = false;
  }

  lastButtonState = currentButtonState;

  int currentA = digitalRead(PIN_ENCODER_A);
  int currentB = digitalRead(PIN_ENCODER_B);

  // Implement debouncing for rotation
  if (millis() - lastRotationTime > rotationDebounceDelay) {
    if (currentB == HIGH && currentA == LOW) {
      RotateRight();
      lastRotationTime = millis();
    }

    if (currentB == LOW && currentA == HIGH) {
      RotateLeft();
      lastRotationTime = millis();
    }
  }

  lastA = currentA;
  lastB = currentB;

  UpdateOLED();
}

void ButtonPress() {
  adjustingValue = !adjustingValue; // Toggle between selecting and adjusting
}

void RotateRight() {
  if (adjustingValue && displayValue[sliderNumber] + increment[sliderNumber] <= 100) {
    displayValue[sliderNumber] += increment[sliderNumber];
  } else if (!adjustingValue) {
    sliderNumber = (sliderNumber + 1) % amountSliders;
  }
}

void RotateLeft() {
  if (adjustingValue && displayValue[sliderNumber] - increment[sliderNumber] >= 0) {
    displayValue[sliderNumber] -= increment[sliderNumber];
  } else if (!adjustingValue) {
    sliderNumber = (sliderNumber - 1 + amountSliders) % amountSliders;
  }
}

void UpdateOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(14, 5);
  display.println(sliderNames[sliderNumber]);

  display.setCursor((displayValue[sliderNumber] == 100) ? 97 : 103, 5);
  display.println(displayValue[sliderNumber]);

  display.drawRect(barX, barY, barWidth, barHeight, SSD1306_WHITE);
  int fillWidth = (displayValue[sliderNumber] * barWidth) / 100;
  display.fillRect(barX, barY, fillWidth, barHeight, SSD1306_WHITE);

  if (!adjustingValue) {
    display.fillTriangle(0, 5, 0, 11, 6, 8, SSD1306_WHITE);
  } else {
    display.fillTriangle(0, barY + (barHeight / 2) - 3, 0, barY + (barHeight / 2) + 3, 6, barY + (barHeight / 2), SSD1306_WHITE);
  }

  display.display();
}
