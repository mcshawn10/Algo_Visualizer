#pragma once
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
using std::cout; using std::cin; using std::endl;
using std::vector; using std::string; using std::tuple;


class Button
{
public:
	
	Button();
	Button(const char* t, int xp, int yp, int w, int h);
	const char* title;
	Rectangle textbox;
	
	bool mouseOn;
	//void function();
	void draw_box();
	void draw_text();
	~Button();

};
