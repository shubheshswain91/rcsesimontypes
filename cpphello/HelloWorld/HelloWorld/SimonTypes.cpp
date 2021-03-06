// SimonTypes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "LiquidCrystal.h" //	Use <> instead of "" when compiling for Arduino
#include "PS2Keyboard.h" //	Use <> instead of "" when compiling for Arduino
#include "Utils.h"

#define DATA_PIN 8

PS2Keyboard keyboard;

const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

std::string random_str;
std::string input_str;

char input_char = '\0';

int level = 0;
int score = -1;

void setup() {
	keyboard.begin(DATA_PIN);
	lcd.begin(16, 2);
	if (keyboard.available()) {
		while (input_char != PS2_ENTER) {
			lcd.print("Press Enter to Start");
			input_char = keyboard.read();
		}
	}
	else {
		lcd.print("Keyboard Unavailable");
	}
}

void loop() {

	if (keyboard.available()) {

		while (!(level >= 1 && level <= 5)) {
			lcd.print("Select Level 1 to 5");
			level = keyboard.read() - '0'; 
		}

		do {
			score++; 
			random_str = random_string(level + 2);
			lcd.print(random_str);
			delay(2000);
			lcd.print("");
			input_str = "";
			input_char = '\0';
			
			while (input_str.length() < random_str.length()) {
				input_char = keyboard.read();
				input_str += input_char;
				lcd.print(input_str);
			}

			if (score % 5 == 0) {
				level++;
			}

		} while (random_str.compare(toUpperCase(input_str))==0);
		lcd.print("Game Over. Score : " + std::to_string(score));
		level = 0;
		score = -1;
		delay(3000);
	}
	
}

int main()
{
	setup();
	while (true) {
		loop();
	}
	return 0;
}

