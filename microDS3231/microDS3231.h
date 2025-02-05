#ifndef microDS3231_h
#define microDS3231_h
/*
	Ультра лёгкая библиотека для работы с RTC DS3231
	Для работы нужна библиотека microWire.h
	Версия 1.3 by Egor
	- Совместимость с microWire 2.0
	v1.2 - добавлены ограничения на вводимые в setTime числа. Также нельзя ввести 29 февраля увы =)
	v1.3 - пофикшено зависание, когда модуль отключен но опрашивается
	v1.4 - незначительный фикс
	v2.0 - новые возможности, оптимизация и облегчение
	v2.1 - добавил вывод температуры, вывод в String и char
*/

//#include "microWire.h"	// выбор между библиотеками Wire и microWire
#include "Wire.h"

#define DS_ADDR 0x68	// адрес чипа

#include <Arduino.h>
#include "buildTime.h"

struct DateTime {
	uint8_t second; 
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint16_t year;
};

class MicroDS3231 {
public:
	MicroDS3231();					// конструктор
	void setTime(int8_t seconds, int8_t minutes, int8_t hours, int8_t date, int8_t month, int16_t year);	// установка времени
	void setTime(uint8_t param);	// установка времени == времени компиляции
	void setTime(DateTime time);	// установить из структуры DateTime
	DateTime getTime(void);			// получить в структуру DateTime
	String getTimeString();			// получить время как строку вида 12:08:09
	String getDateString();			// получить дату как строку вида 2021.04.08
	void getTimeChar(char* array);	// получить время как char array [8] вида 12:08:09
	void getDateChar(char* array);	// получить дату как char array [10] вида 2021.04.08
	bool lostPower(void);			// проверка на сброс питания
	uint8_t getSeconds(void);		// получить секунды
	uint8_t getMinutes(void);		// получить минуты
	uint8_t getHours(void);			// получить часы
	uint8_t getDay(void);			// получить день недели
	uint8_t getDate(void);			// получить число
	uint16_t getYear(void);			// получить год
	uint8_t getMonth(void);			// получить месяц
	float getTemperatureFloat(void);// получить температуру float
	int getTemperature(void);		// получить температуру int
	
private:
	uint8_t encodeRegister(int8_t data);
	int getTemperatureRaw(void);
	uint8_t readRegister(uint8_t addr);
	uint8_t unpackRegister(uint8_t data);
	uint8_t unpackHours(uint8_t data);
};

const bool COMPILE_TIME = true;
#endif