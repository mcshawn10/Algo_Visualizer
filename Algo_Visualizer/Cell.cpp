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
	:size(17), h(0), color_str("WHITE"), color(WHITE)
{
	counter++;
}

Cell::Cell(int r, int c, Color clr, string c_s)
{
	row = r; //row pos
	col = c; //columns pos
	color = clr;
	size = 17;
	//g = 0;
	//h;
	//f = 0;
	color_str = c_s;
	
	

	
	
}
Cell& Cell::operator=(const Cell& rhs) // assignment operator
{
	this->row =  rhs.row;
	this->col = rhs.col;
	this->size = rhs.size;
	this->g = rhs.g;
	this->h = rhs.h;
	this->f = rhs.f;
	this->counter = rhs.counter;
	this->color = rhs.color;

	this->color_str = rhs.color_str;


	return *this;
	// // O: insert return statement here
}
Cell::Cell(const Cell& c1) // copy constructor
{
	row = c1.row;
	col = c1.col;
	size = c1.size;
	
	g = c1.g;
	h = c1.h;
	f = c1.f;
	counter = c1.counter;
	color = c1.color;
	color_str = c1.color_str;
	//cout << "copy called" << endl;


}

Cell::Cell(Cell&& src) noexcept // move constructor
{
	row = src.row;
	col = src.col;
	size = src.size;
	h = src.h;
	color = src.color;
	color_str = src.color_str;
	//cout << "MOVE called" << endl;

	

}

Cell& Cell::operator=(Cell&& src) noexcept// move assignment operator
{
	if (this != &src)
	{
	}
	row = src.row;
	col = src.col;
	size = src.size;
	h = src.h;
	color = src.color;
	color_str = src.color_str;
	//cout << "move assignment OP called" << endl;
	return *this;
	// // O: insert return statement here
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

void Cell:: set_h(int i)
{
	h = i;
}
bool Cell::operator==(const Cell& other) const
{
	if (this->row == other.row && this->col == other.col) return true;
	else return false;
}

bool Cell::operator!=(const Cell& other) const
{
	if (this->row != other.row && this->col != other.col) return true;
	else return false;
}


bool Cell::operator<(const Cell& other) const
{
	if (this->counter <= other.counter) return true;
	else if (this->counter > other.counter) return false;
	
}
bool Cell::operator>(const Cell& other) const
{
	if (this->counter > other.counter) return true;
	else if (this->counter <= other.counter) return false;

}

Cell::~Cell()
{
	
	//cout << "destructor called" << endl;
}