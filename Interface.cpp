#include "Interface.h"
#include "Pucman.h"

#include <glut.h>
#include <Windows.h>
#include <string>


bool Interface::interfaceOn = false;
bool Interface::pauseOn = false;
bool Interface::menuOn = false;
bool Interface::winOn = false;
bool Interface::lossOn = false;
bool Interface::exit = false;
bool Interface::startGame = false;
bool Interface::mouseClick = false;

Interface::Interface(int wind_w, int wind_h, int scrW, int scrH) : 
			x(wind_w / 2), y(wind_h / 2), width(x * 0.8), height(y * 0.8), scrW(scrW), scrH(scrH)
{
	interfaceOn = true;
	menuOn = true;
}

void Interface::Menu(float mouse_x, float mouse_y) const
{
	// STATIC
	// draw window rect 
	glColor3f(0.8, 0, 0);
	glRectf(x - width / 2, y - height / 2, x + width / 2, y + height / 2);

	// draw header
	PrintString(x - getStringLength("Menu", 40) / 2, y + 20, "Menu", 40, 0, 0, 0);

	// INTERACTIVE
	// draw buttons
	bool mouseOnButton1 = InteractiveString(x, y - 20, "Play", 20, mouse_x, mouse_y, 0, 0, 0, 1, 1, 0);
	bool mouseOnButton2 = InteractiveString(x, y - 50, "Exit", 20, mouse_x, mouse_y, 0, 0, 0, 1, 1, 0);
	// processing clicks
	if (mouseClick && mouseOnButton1) {
		interfaceOn = false;
		startGame = true;
		menuOn = false;
	}
	if (mouseClick && mouseOnButton2) {
		exit = true;
		menuOn = false;
	}
	mouseClick = false;
}

void Interface::Pause(float mouse_x, float mouse_y) const
{
	// STATIC
	// draw window rect 
	glColor3f(1, 0, 0);
	glRectf(x - width / 2, y - height / 2, x + width / 2, y + height / 2);

	// draw header
	PrintString(x - getStringLength("Pause", 40) / 2, y + 30, "Pause", 40, 0, 0, 0);

	// INTERACTIVE
	// draw buttons
	bool mouseOnButton1 = InteractiveString(x, y - 40, "Continue", 20, mouse_x, mouse_y, 0, 0, 0, 1, 1, 0);
	bool mouseOnButton2 = InteractiveString(x, y - 70, "Menu", 20, mouse_x, mouse_y, 0, 0, 0, 1, 1, 0);
	bool mouseOnButton3 = InteractiveString(x, y - 10, "New game", 20, mouse_x, mouse_y, 0, 0, 0, 1, 1, 0);
	// processing clicks
	if (mouseClick && mouseOnButton1) {
		interfaceOn = false;
		pauseOn = false;
	}
	if (mouseClick && mouseOnButton2) {
		interfaceOn = true;
		menuOn = true;
		pauseOn = false;
	}
	if (mouseClick && mouseOnButton3) {
		interfaceOn = false;
		startGame = true;
		pauseOn = false;
	}
	mouseClick = false;
}

void Interface::Win(float mouse_x, float mouse_y) const
{
	// STATIC
	// draw window rect 
	glColor3f(1, 0, 0);
	glRectf(x - width / 2, y - height / 2, x + width / 2, y + height / 2);

	// draw header
	PrintString(x - getStringLength("Win!", 40) / 2, y + 20, "Win!", 40, 0, 0, 0);


	// INTERACTIVE
	// draw buttons
	bool mouseOnButton1 = InteractiveString(x, y - 20, "New game", 20, mouse_x, mouse_y, 0, 0, 0, 1, 1, 0);
	bool mouseOnButton2 = InteractiveString(x, y - 50, "Menu", 20, mouse_x, mouse_y, 0, 0, 0, 1, 1, 0);
	// processing clicks
	if (mouseClick && mouseOnButton1) {
		interfaceOn = false;
		startGame = true;
		winOn = false;
	}
	if (mouseClick && mouseOnButton2) {
		menuOn = true;
		winOn = false;
	}
	mouseClick = false;
}

void Interface::Loss(float mouse_x, float mouse_y) const
{
	// STATIC
	// draw window rect 
	glColor3f(1, 0, 0);
	glRectf(x - width / 2, y - height / 2, x + width / 2, y + height / 2);

	// draw header
	PrintString(x - getStringLength("Loss!", 40) / 2, y + 20, "Loss!", 40, 0, 0, 0);

	// INTERACTIVE
	// draw buttons
	bool mouseOnButton1 = InteractiveString(x, y - 20, "New game", 20, mouse_x, mouse_y, 0, 0, 0, 1, 1, 0);
	bool mouseOnButton2 = InteractiveString(x, y - 50, "Menu", 20, mouse_x, mouse_y, 0, 0, 0, 1, 1, 0);
	// processing clicks
	if (mouseClick && mouseOnButton1) {
		interfaceOn = false;
		startGame = true;
		lossOn = false;
	}
	if (mouseClick && mouseOnButton2) {
		menuOn = true;
		lossOn = false;
	}
	mouseClick = false;
}

void Interface::printStatistic(int score, int lives) const
{
	float pos = 20;
	PrintString(pos, (y*2) - 25, "Level 1", 20, 0.8, 0.8, 0.8);	// (y * 2) = maxY
	pos += getStringLength("Level 1", 30) + 300;
	PrintString(pos, (y * 2) - 25, "Score: ", 20, 0.8, 0.8, 0.8);
	pos += getStringLength("Score: ", 20);
	PrintNum(pos, (y * 2) - 25, score, 20, 0.8, 0.8, 0.8);

	Pucman p(T(x*2 - 30, y*2 - 15), 10);
	for (int i = 0; i < lives; ++i)
	{
		p.print();
		p.moveBy(-30, 0);
	}
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

bool Interface::InteractiveString(float x, float y, const char* string, float size,
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
		return true;
	} else {
		PrintString(x1, y1, string, size, r1, g1, b1);
		return false;
	}
}

void Interface::PrintNum(float x, float y, int num, float size, float r, float g, float b) const
{
	PrintString(x, y, std::to_string(num).c_str(), size, r, g, b);
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

