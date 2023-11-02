#ifndef _16S2_H_
#define _16S2_H_
#include "stm32f103xb.h"

void LCDInit(void);
void WriteByte(uint8_t b, _Bool cd);
void WriteData(uint8_t b);
void WriteCmd(uint8_t b);
void LcdGoTo(uint8_t x, uint8_t y);
void LcdWriteString(uint8_t * stringToWrite);

// ���������� � ��������� HD44780


// ������� ������ � ��������� ��������� �������� DDRAM � 0
// 1ms
#define HD44780_INSTRUCTION_CLEAR					0x01	

// ������������� �������� ������� DDRAM � 0. ������ �����, ���������� ����� � ������������ ����������.
// ���� �� ��� �������. ���������� DDRAM �������� ����������.
// 1.52ms
#define HD44780_INSTRUCTION_HOME					0x02	

// ��������� ���������� ����������� �������� �������(DB1) � ���������/��������� ����� ������(DB0)
// 37 us
#define HD44780_INSTRUCTION_ENTRY_MODE				0x04

// ���������� �������. �������/�������� (DB2) , ���������� ������ ��� ��� (DB1), ������ �������� ��� ��� (DB0)
// 37 us
#define HD44780_INSTRUCTION_LCD_CTRL				0x08

// ������� ������ � �������� ����� ��� ��������� ����������� DDRAM (DB3 ��� / DB2 �����������)
// 37 us
#define HD44780_INSTRUCTION_SHIFT					0x10

// ������� �������������. ������������ ��� ����� �������. ����� ��� �� ��������.
// ��� ���-�� ������������� �������� (DB4 1=8bit/0=4bit)
// ���������� ����� �� ������ (DB3 1=2������/0=1������)
// ������ ������ (DB2 1=5x10 / 0=5x8)
// 37 us
#define HD44780_INSTRUCTION_FUNCTION_SET			0x20

// ������������� CGRAM �����. ����� �������(����/��������) ���������� ����� ����� ���� �������.
// � DB0-DB5 �����.
// 37 us
#define HD44780_INSTRUCTION_CGRAM_ADDRESS			0x40

// ������������� DDRAM �����. ����� �������(����/��������) ���������� ����� ����� ���� �������.
// � DB0-DB6 �����.
// 37 us
#define HD44780_INSTRUCTION_DDRAM_ADDRESS			0x80


// ����� (���������� ��� ������ ������ ��������) HD44780


// ���� ���������� LCD.(���������-�� �� ������� ��� ��� ���) ���-�� ������������ ������ �� ���������� ��������� ��������.
// ���������� ������ � RW
// 0 us
#define HD44780_FLAG_BUSY							0x80   //(1<<HD44780_CONFIG_D7_PIN) // 0x80

// ����������� ������� ������
#define HD44780_FLAG_CURSOR_DIRECTION				0x02

// ��������� ����� ������ �� ������� �������
#define HD44780_FLAG_DISPLAY_SHIFT					0x01

// ��������� ������
#define HD44780_FLAG_DISPLAY_ACTIVE					0x04

// ��������� ����� ������� �� ������
#define HD44780_FLAG_CURSOR_ACTIVE					0x02

// �������� �����
#define HD44780_FLAG_CURSOR_BLINK					0x01

// ����� ������
#define HD44780_FLAG_SHIFT_DISPLAY					0x08

// �������� ������ ��� ������� ������
#define HD44780_FLAG_SHIFT_DIRECTION				0x04

// ��������� 8 ������� ������
#define HD44780_FLAG_EIGHT_BIT						0x10

// ��������� ���� � ����� ��������� ������
#define HD44780_FLAG_TWO_LINES						0x08

// ������ ������ 5x10
#define HD44780_FLAG_FONT_SIZE						0x04

#define HD44780_CURSOR_SHIFT_RIGHT					0x14

#define HD44780_LCD_CURSOR_OFF					0x0C

#define HD44780_LCD_CHAR_BLINK					0x0D

#endif
