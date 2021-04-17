/*
 * RTCControl.h
 *
 * Created: 4/15/2021 11:35:23 PM
 *  Author: L03068681
 */ 


#ifndef RTCCONTROL_H_
#define RTCCONTROL_H_

#define SECONDS_ADDR 0x00
typedef union {
	struct  {
		uint8_t un_seconds 	:4,
		dec_seconds    :3,
		ch_sec    :1;
	} field;
	uint8_t reg;
} seconds_type;

#define MINUTES_ADDR 0x01
typedef union {
	struct  {
		uint8_t un_minutes  	:4,
		dec_minutes    :3,
		unused   :1;
	} field;
	uint8_t reg;
} minutes_type;


#define HOURS_ADDR 0x02
typedef union {
	struct  {
		uint8_t un_hours  	:4,
		dec_hours    :1,
		PMAM :1,
		hr_format :1,
		unused    :1;
	} field;
	uint8_t reg;
} hours_type;

#define DAY_ADDR 0x03
typedef union {
	struct {
		uint8_t day	:3,
		unused	:5;
	} field;
	uint8_t reg;
} day_type;

#define DATE_ADDR 0x04
typedef union {
	struct {
		uint8_t un_date	:4,
		dec_date	:2,
		unused	:2;
	} field;
	uint8_t reg;
} date_type;

#define MONTH_ADDR 0x05
typedef union {
	struct  {
		uint8_t un_month  	:4,
		dec_mont    :1,
		unused    :3;
	} field;
	uint8_t reg;
} month_type;

#define YEAR_ADDR 0x06
typedef union {
	struct {
		uint8_t un_year :4,
		dec_year	:4;
	} field;
	uint8_t reg;
} year_type;

typedef struct {
	seconds_type seconds;
	minutes_type minutes;
	hours_type hours;
	day_type day;
	date_type date;
	month_type month;
	year_type year;
} time_type;

void sendI2CDataArray(uint8_t SlAddr, uint8_t ptr, uint8_t *ptrData, uint8_t Size);
void receiveI2CDataArray(uint8_t SlAddr,uint8_t ptr,uint8_t* ptrData,uint8_t Size);
void SendI2CData(uint8_t Data);
void StopCond();
void I2CInit();



#endif /* RTCCONTROL_H_ */