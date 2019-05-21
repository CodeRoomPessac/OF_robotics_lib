#ifndef OF_blink_h
#define OF_blink_h

#include <Arduino.h>
///@brief Class for BlinkClass
class BlinkClass
{
	private:
		int level;
	public:
		BlinkClass();
		void blink();
};

#endif