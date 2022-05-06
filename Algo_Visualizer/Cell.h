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


public:
	int row;
	int col;
	int size;
	int g;
	int h;
	int f;
	int counter;
	string color_str;
	Color color;


	Cell();
	Cell(int r, int c, Color clr, string c_s); // parameter constructor
	Cell& operator=(const Cell& rhs); // copy assignment operator
	Cell(const Cell& c1); // copy constructor
	Cell(Cell&& src) noexcept; // move constructor
	Cell& operator=(Cell&& src) noexcept; //move assignment operator
	
	


	
	
	void set_color(Color cr);
	void display_cell();
	Color get_color();
	void set_color_str(string c_s);
	string get_color_str();
	void set_h(int i);
	
	bool operator==(const Cell&) const;
	bool operator!=(const Cell&) const;
	bool operator < (const Cell& other) const;
	bool operator > (const Cell& other) const;

	~Cell();

};
