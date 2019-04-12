#ifndef RTC_H
#define RTC_H

void rtc_setup();
void rtc_task();

void DS1302_clock_burst_read( uint8_t);
void DS1302_clock_burst_write( uint8_t);
uint8_t DS1302_read(int );
void _DS1302_start( void);
void _DS1302_stop(void);
void DS1302_write( int, uint8_t);


#endif
