#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <functional>
#include <cmath>
#include <stdio.h>
#include "raylib.h"
#include "Board.h"
using std::cout; using std::cin; using std::endl;
using std::vector; using std::string; using std::tuple;

class Cell
{
private:
	int row;
	int col;
	int size;
	float g;
	float h;
	float f;
	int counter;
	Color color;
	
	

public:
	Cell();
	Cell(int r, int c, Color clr);

	
	
	void set_color(Color cr);
	void display_cell();
	

	~Cell();

};
