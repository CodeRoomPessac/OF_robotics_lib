#include "blink.h"

BlinkClass::BlinkClass()
	: level(0)
	{}

void BlinkClass::blink(){
	level = 1 - level;
	digitalWrite(13,level);
}