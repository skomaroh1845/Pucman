#pragma once

#include <tuple>

class Interface
{
	float x, y;  // windows pos 
	float width, height;  // windows size
	float scrW, scrH;  // screen size
	
public:
	static bool interfaceOn;
	static bool pauseOn;
	static bool menuOn;
	static bool winOn;
	static bool lossOn;
	
	Interface(int screen_w, int screen_h, int scrW = 1920, int scrH = 1080);

	void PrintMenu(float mouse_x, float mouse_y) const;
	
	void PrintPause(float mouse_x, float mouse_y) const;

	void PrintWin(float mouse_x, float mouse_y) const;

	void PrintLoss(float mouse_x, float mouse_y) const;
	
private:
	
	void PrintString(float x, float y, const char* string, float size, float r = 1, float g = 1, float b = 1) const;
	
	void InteractiveString(float x, float y, const char* string, float size, 
						   float mouse_x, float mouse_y, 
						   float r1 = 1, float g1 = 1, float b1 = 1,
						   float r2 = .5, float g2 = .5, float b2 = .5) const;

	void PrintNum(float x, float y, int num, float size, float r = 1, float g = 1, float b = 1) const;

	std::tuple<float, float, float, float> getStringRect(float x, float y, const char* string, float size) const;

	float getStringLength(const char* string, float size) const;
};

