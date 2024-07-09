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

		bool begin();

		struct tm* dateTime(); // Caching version
		struct tm* readDateTime();
		bool readDateTime(struct tm* target);
		bool writeDateTime(const struct tm* datetime);
	
	private:
		time_t _lastread;
		struct tm _dt;
};

#endif // __BM8563_H