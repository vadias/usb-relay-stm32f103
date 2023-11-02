#ifndef _16S2_H_
#define _16S2_H_
#include "stm32f103xb.h"

void LCDInit(void);
void WriteByte(uint8_t b, _Bool cd);
void WriteData(uint8_t b);
void WriteCmd(uint8_t b);
void LcdGoTo(uint8_t x, uint8_t y);
void LcdWriteString(uint8_t * stringToWrite);

// Переменные с командами HD44780


// Очистка экрана и установка адресного счетчика DDRAM в 0
// 1ms
#define HD44780_INSTRUCTION_CLEAR					0x01	

// Устанавливает адресный счетчик DDRAM в 0. Помимо этого, возвращает экран в оригинальное положениее.
// Если он был сдвинут. Содержимое DDRAM остается неизменным.
// 1.52ms
#define HD44780_INSTRUCTION_HOME					0x02	

// Позволяет установить направление движения курсора(DB1) и разрешать/запрещать сдвиг экрана(DB0)
// 37 us
#define HD44780_INSTRUCTION_ENTRY_MODE				0x04

// Управление экраном. Включен/выключен (DB2) , Показывать курсор или нет (DB1), Мигать курсором или нет (DB0)
// 37 us
#define HD44780_INSTRUCTION_LCD_CTRL				0x08

// Двигает курсор и сдвигает экран без изменения содержимого DDRAM (DB3 что / DB2 направление)
// 37 us
#define HD44780_INSTRUCTION_SHIFT					0x10

// Функция инициализации. Используется при пером запуске. Потом она не работает.
// Она так-же устанавливает битность (DB4 1=8bit/0=4bit)
// Количество строк на экране (DB3 1=2строки/0=1строка)
// Размер шрифта (DB2 1=5x10 / 0=5x8)
// 37 us
#define HD44780_INSTRUCTION_FUNCTION_SET			0x20

// Устанавливает CGRAM адрес. Обмен данными(приём/передача) происходят сразу после этой команды.
// В DB0-DB5 адрес.
// 37 us
#define HD44780_INSTRUCTION_CGRAM_ADDRESS			0x40

// Устанавливает DDRAM адрес. Обмен данными(приём/передача) происходят сразу после этой команды.
// В DB0-DB6 адрес.
// 37 us
#define HD44780_INSTRUCTION_DDRAM_ADDRESS			0x80


// Флаги (необходимы для работы других дефайнов) HD44780


// Флаг готовности LCD.(принимает-ли он команды или еще нет) Так-же возвращается ссылка на содержимое адресного счетчика.
// Передается вместе с RW
// 0 us
#define HD44780_FLAG_BUSY							0x80   //(1<<HD44780_CONFIG_D7_PIN) // 0x80

// Направление курсора вправо
#define HD44780_FLAG_CURSOR_DIRECTION				0x02

// Разрешить сдвиг экрана со сдвигом курсора
#define HD44780_FLAG_DISPLAY_SHIFT					0x01

// Включение экрана
#define HD44780_FLAG_DISPLAY_ACTIVE					0x04

// Разрешает показ курсора на экране
#define HD44780_FLAG_CURSOR_ACTIVE					0x02

// Мигающий урсор
#define HD44780_FLAG_CURSOR_BLINK					0x01

// Сдвиг экрана
#define HD44780_FLAG_SHIFT_DISPLAY					0x08

// Движение экрана или курсора вправо
#define HD44780_FLAG_SHIFT_DIRECTION				0x04

// Включение 8 битного режима
#define HD44780_FLAG_EIGHT_BIT						0x10

// Включение двух и более строчного режима
#define HD44780_FLAG_TWO_LINES						0x08

// Размер шрифта 5x10
#define HD44780_FLAG_FONT_SIZE						0x04

#define HD44780_CURSOR_SHIFT_RIGHT					0x14

#define HD44780_LCD_CURSOR_OFF					0x0C

#define HD44780_LCD_CHAR_BLINK					0x0D

#endif
