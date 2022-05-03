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

Cell::Cell()
{

}
Cell::Cell(int r, int c, Color clr, string c_s)
{
	row = r; //row pos
	col = c; //columns pos
	color = clr;
	size = 17;
	g = 0;
	h = 0;
	f = 0;
	color_str = c_s;

	
	
}



void Cell::set_color(Color cr)
{
	color = cr;

}

void Cell::display_cell()
{
	DrawRectangle(col * 20 + 1 , row * 20 + 202, size, size, color);
}

Color Cell::get_color()
{
	Color return_color = color;
	return return_color;
}

void Cell::set_color_str(string c_s)
{
	color_str = c_s;
}



string Cell::get_color_str()
{
	return color_str;
}

bool Cell::operator==(const Cell& other) const
{
	if (this->row == other.row && this->col == other.col) return true;
	else return false;
}


Cell::~Cell()
{
	
}