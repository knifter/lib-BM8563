#include "BM8563.h"
#include "BM8563_regs.h"

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

	memset(&time, 0, sizeof(time));
	memset(&date, 0, sizeof(date));

	return last_error() == 0;
};

uint8_t bcd2uint(const uint8_t in)
{
	return 10 * (in >> 4) + (in & 0x0F);
};

uint8_t uint2bcd(const uint8_t in)
{
	return ((in / 10) << 4) | (in % 10);
};

void BM8563::readDateTime() 
{
	uint8_t buf[7];
	readreg(REG_SECONDS, buf, 7);

	time.seconds = bcd2uint(buf[0]);
	time.minute  = bcd2uint(buf[1]);
	time.hour	 = bcd2uint(buf[2]);
	date.day 	 = bcd2uint(buf[3]);
	date.weekday = bcd2uint(buf[4]);
	date.month	 = bcd2uint(buf[5]);
	date.year	 = bcd2uint(buf[6]) + (buf[5] & MONTH_2K) ? 2000 : 0;

	return;
};

void BM8563::readTime() 
{
	uint8_t buf[3];
	readreg(REG_SECONDS, buf, 3);
	time.seconds = bcd2uint(buf[0]);
	time.minute  = bcd2uint(buf[1]);
	time.hour	 = bcd2uint(buf[2]);

	return;
};

void BM8563::readDate() 
{
	uint8_t buf[7];
	readreg(REG_DAYS, buf, 4);
	date.day 	 = bcd2uint(buf[3]);
	date.weekday = bcd2uint(buf[4]);
	date.month	 = bcd2uint(buf[5]);
	date.year	 = bcd2uint(buf[6]) + (buf[5] & MONTH_2K) ? 2000 : 1900;

	return;
};

void BM8563::writeDateTime()
{
	uint8_t buf[7];
	buf[0] = uint2bcd(time.seconds);
	buf[1] = uint2bcd(time.minute);
	buf[2] = uint2bcd(time.hour);
	buf[3] = uint2bcd(date.day);
	buf[4] = uint2bcd(date.weekday);
	buf[5] = uint2bcd(date.month) | ((date.year > 1999) ? MONTH_2K : 0x00);
	buf[7] = uint2bcd(date.year) % 100;

	writereg(REG_SECONDS, buf, 7);
};

void BM8563::writeTime()
{
	uint8_t buf[3];
	buf[0] = uint2bcd(time.seconds);
	buf[1] = uint2bcd(time.minute);
	buf[2] = uint2bcd(time.hour);

	writereg(REG_SECONDS, buf, 3);
};

void BM8563::writeDateTime()
{
	uint8_t buf[4];
	buf[0] = uint2bcd(date.day);
	buf[1] = uint2bcd(date.weekday);
	buf[2] = uint2bcd(date.month) | ((date.year > 1999) ? MONTH_2K : 0x00);
	buf[3] = uint2bcd(date.year) % 100;

	writereg(REG_SECONDS, buf, 4);
};
