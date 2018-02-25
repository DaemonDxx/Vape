#include "ssd1306.h"
#include "Display.h"

void DisplayInit() {
	SSD1306_Init();
	SSD1306_GotoXY(0, 44); //Устанавливаем курсор в позицию 0;44. Сначала по горизонтали, потом вертикали.
	SSD1306_Puts("Hello, habrahabr!!", &Font_7x10, SSD1306_COLOR_WHITE); //пишем надпись в выставленной позиции шрифтом "Font_7x10" белым цветом.
	SSD1306_DrawCircle(10, 33, 7, SSD1306_COLOR_WHITE); //рисуем белую окружность в позиции 10;33 и радиусом 7 пикселей
	SSD1306_UpdateScreen();
}
