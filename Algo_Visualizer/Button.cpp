#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <tuple>
#include <functional>
#include <cmath>
#include "raylib.h"
#include "Board.h"
#include "Cell.h"
#include "Button.h"
using std::cout; using std::cin; using std::endl;
using std::vector; using std::string; using std::tuple;

Button::Button()
{
	mouseOn = false;	
}

Button::Button(const char* t, int xp, int yp, int w, int h)
{
	title = t;
	
	textbox.x = xp;
	textbox.y = yp;
	textbox.width = w;
	textbox.height = h;
	
}


void Button::draw_box()
{
	DrawRectangleRec(textbox, WHITE);
}

void Button::draw_text()
{
	DrawText(title, (int)textbox.x + 2, (int)textbox.y, 50, MAROON);

}

Button::~Button()
{
}
