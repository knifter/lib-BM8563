#ifndef __BM8563_H
#define __BM8563_H

#include <TwoWireDevice.h>

#define BM8563_ADDRESS_DEFAULT      (0x51)

class BM8563 : protected TwoWireDevice 
{
	public:
		//constructors
		BM8563(TwoWire& wire)  : TwoWireDevice(wire, BM8563_ADDRESS_DEFAULT) {};
		BM8563() : TwoWireDevice(BM8563_ADDRESS_DEFAULT) {};
		~BM8563() {};

		typedef struct
		{
			int8_t hour;
			int8_t minute;
			int8_t seconds;
		} rtctime_t;

		typedef struct  
		{
			int8_t  day;
			int8_t  weekday;
			int8_t  month;
			int16_t year;
		} rtcdate_t;

		rtctime_t time;
		rtcdate_t date;

		bool begin();
		void readDateTime();
		void readTime();
		void readDate();
		void writeDateTime();
		void writeTime();
		void writeDate();
};

#endif // __BM8563_H