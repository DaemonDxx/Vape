#include "ssd1306.h"
#include "Display.h"

void DisplayInit() {
	SSD1306_Init();
	SSD1306_GotoXY(0, 44); //������������� ������ � ������� 0;44. ������� �� �����������, ����� ���������.
	SSD1306_Puts("Hello, habrahabr!!", &Font_7x10, SSD1306_COLOR_WHITE); //����� ������� � ������������ ������� ������� "Font_7x10" ����� ������.
	SSD1306_DrawCircle(10, 33, 7, SSD1306_COLOR_WHITE); //������ ����� ���������� � ������� 10;33 � �������� 7 ��������
	SSD1306_UpdateScreen();
}
