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
Cell::Cell(int r, int c, Color clr)
{
	row = r; //row pos
	col = c; //columns pos
	color = clr;
	size = 17;
	g = 0;
	h = 0;
	f = 0;

	
	
}



void Cell::set_color(Color cr)
{
	color = cr;

}

void Cell::display_cell()
{
	DrawRectangle(col * 20 + 1 , row * 20 + 202, size, size, color);
}

Cell::~Cell()
{
	
}