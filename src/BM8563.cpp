#include "BM8563.h"
#include "BM8563_regs.h"

#include <time.h>

#include "tools-log.h"

bool BM8563::begin()
{
	if(!TwoWireDevice::begin())
	{
		// ERROR("TwoWireDevice.begin() failed.");
		return false;
	};

	writereg8(REG_CS1, 0x00);
	writereg8(REG_CS2, 0x00);
	writereg8(REG_CLKOUTCTL,  0x00);
	writereg8(REG_TIMERCTL, TIMERCTL_MIN); // Saves power if timer not used

	// _lastread = 0;
	if(last_error())
	{
		WARNING("BM8563.begin() failed: %s", last_error_text());
		return false;
	};
	return true;
};

uint8_t bcd2uint(const uint8_t in)
{
	return 10 * (in >> 4) + (in & 0x0F);
};

uint8_t uint2bcd(const uint8_t in)
{
	return ((in / 10) << 4) | (in % 10);
};

// struct tm* BM8563::dateTime()
// {
// 	if(millis() - _lastread > 999)
// 		readDateTime(&_dt);
// 	return &_dt;
// };

// struct tm* BM8563::readDateTime() 
// {
// 	if(millis() - _lastread > 999)
// 		readDateTime(&_dt);
// 	return &_dt;
// };

bool BM8563::readDateTime(struct tm* target)
{
	uint8_t buf[7];
	readreg(REG_SECONDS, buf, 7);

	target->tm_sec 		= bcd2uint(buf[0] & 0x7F);
	target->tm_min  	= bcd2uint(buf[1] & 0x7F);
	target->tm_hour		= bcd2uint(buf[2] & 0x3F);
	target->tm_mday 	= bcd2uint(buf[3] & 0x3F);
	target->tm_wday 	= bcd2uint(buf[4] & 0x07);
	target->tm_mon		= bcd2uint(buf[5] & 0x1F);
	target->tm_year		= bcd2uint(buf[6]) + ((buf[5] & MONTH_2K) ? 2000 : 1900);

	// FIXME?
	target->tm_isdst = false;
	target->tm_yday = 0;

	return last_error() == 0;
};

bool BM8563::writeDateTime(const struct tm* dt)
{
	uint8_t buf[7];
	buf[0] = uint2bcd(dt->tm_sec);
	buf[1] = uint2bcd(dt->tm_min);
	buf[2] = uint2bcd(dt->tm_hour);
	buf[3] = uint2bcd(dt->tm_mday);
	buf[4] = uint2bcd(dt->tm_wday);
	buf[5] = uint2bcd(dt->tm_mon) | ((dt->tm_year > 1999) ? MONTH_2K : 0x00);
	buf[6] = uint2bcd(dt->tm_year % 100);

	writereg(REG_SECONDS, buf, 7);

	// // invalidate cache
	// _lastread = 0;

	return last_error() == 0;
};
