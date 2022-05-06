#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <functional>
#include <cmath>
#include <tuple>
#include "raylib.h"
#include "Cell.h"
#include "Button.h"
using std::cout; using std::cin; using std::endl;
using std::vector; using std::string; using std::tuple;



class Board
{
private:
	int width;
	int height;
	int rows;
	int cols;
	int fps;
	int cell_size;
	
	bool found;
	vector <Cell> path;
	
	Button A_button;
	Button D_button;
	Button BFS_button;
	Button start_button;
	Button goal_button;
	Button clr_search;
	Button clr_board;
	
	



public:
	Cell* start;
	Cell* goal;
	//Cell** blocks;
	vector<Cell*> blocks;
	Cell** parent;

	Board();
	void set_blocks();
	void set_parent();
	
	
	void initialize_lists();
	void draw_board();
	int get_pos();
	void set_start();
	void set_goal();
	void draw_obstacles(int i);
	void clear_board();
	void clear_search();
	void find_path();
	int m_dist(const Cell& c1, const Cell& c2);
	void A_star();
	void Dijkstra();
	void BFS();
	void RUN();
	~Board();
	
};

