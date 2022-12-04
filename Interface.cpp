#include "Interface.h"
#include <glut.h>
#include <Windows.h>


bool Interface::pauseOn = false;

Interface::Interface(int wind_w, int wind_h, int scrW, int scrH) : 
			x(wind_w / 2), y(wind_h / 2), width(x), height(y), scrW(scrW), scrH(scrH)
{
}

void Interface::PrintPause(float mouse_x, float mouse_y) const
{
	// STATIC
	// draw window rect 
	glColor3f(1, 0, 0);
	glRectf(x - width / 2, y - height / 2, x + width / 2, y + height / 2);
	
	// draw header
	PrintString(x - getStringLength("Pause", 40) / 2, y + 20, "Pause", 40, 0, 0, 0);


	// INTERACTIVE
	InteractiveString(x, y - 20, "Continue", 20, mouse_x, mouse_y, 0, 0, 0, 1, 1, 0);

	InteractiveString(x, y - 50, "Menu", 20, mouse_x, mouse_y, 0, 0, 0, 1, 1, 0);
}

void Interface::PrintString(float x, float y, const char* string, float size, float r, float g, float b) const
{
	glPushMatrix();
	
	glColor3f(r, g, b);	
	glTranslatef(x, y, 0);
	
	float scale = size / 100;  // original size = 100 by Y
	glScalef(scale * 0.8, scale, 1);
	glLineWidth(scale * 10);

	for (int i = 0; string[i] != '\0'; ++i) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[i]);
	}

	glPopMatrix();
}

void Interface::InteractiveString(float x, float y, const char* string, float size,
								  float mouse_x, float mouse_y, 
								  float r1, float g1, float b1,
								  float r2, float g2, float b2) const
{
	// calculate string rect coordinates
	float x1, y1, x2, y2;
	float length = getStringLength(string, size);
	x1 = x - length / 2;
	y1 = y;
	x2 = x1 + length;
	y2 = y + size;

	// color
	mouse_y = (scrH - mouse_y) * (this->y * 2) / scrH;
	mouse_x = mouse_x * (this->x * 2) / scrW;
	if (mouse_x > x1 && mouse_x < x2 &&  // if cursor in string rect - change color 
		mouse_y > y1 && mouse_y < y2) {
		PrintString(x1, y1, string, size, r2, g2, b2);
	} else {
		PrintString(x1, y1, string, size, r1, g1, b1);
	}

}

void Interface::PrintNum(float x, float y, int num, float size, float r, float g, float b) const
{
	char str[10] = {'\0'};
	int i = 9;
	while (i >= 0) {
		str[i] = char(num % 10);
		--i;
		num = num / 10;
	}

	PrintString(x, y, str + i + 1, size, r, g, b);
}

std::tuple<float, float, float, float> Interface::getStringRect(float x, float y, const char* string, float size) const
{
	float scale = size / 100;  // original size = 100 by Y
	float x2 = x + glutStrokeLength(GLUT_STROKE_ROMAN,
									reinterpret_cast<const unsigned char*>(string)) * scale * 0.8;
	float y2 = y + size;
	return std::make_tuple(x, y, x2, y2);
}

float Interface::getStringLength(const char* string, float size) const
{	
	float scale = size / 100;  // original size = 100 by Y
	return glutStrokeLength(GLUT_STROKE_ROMAN, reinterpret_cast<const unsigned char*>(string)) * scale * 0.8;
}
