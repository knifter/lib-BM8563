#ifndef __BM8563_REGS_H
#define __BM8563_REGS_H

// Control / Status Register 1
#define REG_CS1							(0x00)
	// #define CS1_TESTC					(0b00001000)	// == 0
	#define CS1_STOP					(0b00100000)
	// #define CS1_TEST					(0b10000000)		// == 0

// Control / Status Register 2
#define REG_CS2							(0x01)
	// Timer Interrupt Enable = 1
	#define CS2_TIE						(0b00000001)
	// Alarm Interrupt Enable = 1
	#define CS2_AIE						(0b00000010)
	// Timer Flag, read = whether active, write(0) = clear
	#define CS2_TF						(0b00000100)
	// Alarm Flag, read = active?, write(0) = clear
	#define CS2_AF						(0b00001000)
	#define CS2_TITP					(0b00010000)

#define REG_SECONDS						(0x02)
	#define SECONDS_VL					(0b10000000)	// Battery low
#define REG_MINUTES						(0x03)
#define REG_HOURS						(0x04)
#define REG_DAYS						(0x05)
#define REG_WEEKDAY						(0x06)
#define REG_MONTH					(0x07)
	#define MONTH_2K					(0b10000000)	// Wheter 2k should be added to year
#define REG_YEAR					(0x08)

#define REG_MINUTE_ALARM			(0x09)
#define REG_HOUR_ALARM				(0x0A)
#define REG_DAY_ALARM				(0x0B)
#define REG_WEEKDAY_ALARM			(0x0C)
	#define ALARM_ENABLE_BIT		(0b10000000)
	#define ALARM_NONE				(0xFF)
	// #define ALARM_SIZE				(0x04)

// [ 0x0D ] CLKOUT Register
#define REG_CLKOUTCTL				(0x0D)
	#define CLKOUTCTL_FE			(0b10000000)

// [ 0x0E ] Timer Control Register
#define REG_TIMERCTL				(0x0E)
	#define TIMERCTL_ENABLE			(0b10000000) 
	typedef enum
	{
		// TD0, TD1 bits of TIMERCTL
		TIMERCTL_4096HZ = 0x00,
		TIMERCTL_64HZ   = 0x01,
		TIMERCTL_1HZ	= 0x10,
		TIMERCTL_MIN	= 0x11
	} timer_divider_t;

// [ 0x0F ] Timer Countdown Register
#define REG_TIMERCNT				(0x0F)

#endif // __BM8563_REGS_H
