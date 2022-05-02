#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <tuple>
#include <functional>
#include <cmath>
#include "raylib.h"
#include "Board.h"
#include "Cell.h"
using std::cout; using std::cin; using std::endl;
using std::vector; using std::string; using std::tuple;



Board::Board()
{
	width = 1200;
	height = 700;
	rows = 25; // number of rows
	cols = 60; // number of columns
	fps = 60;
	cell_size = 18;
	found = false;

	A_button = Button("A* Search", 20, 150, 300, 50, &Board::A_star);
	D_button = Button("Dijkstra",400, 150, 250, 50, &Board::Dijkstra);
	BFS_button = Button("BFS", 700,150, 250, 50, &Board::BFS);
	start_button = Button("Start Cell",20, 50, 300, 50, &Board::set_start);
	goal_button = Button("Goal Cell",350, 50, 300, 50, &Board::set_goal);
	clr_board = Button("Clear Board", 800, 50, 350, 50, &Board::clear_board);
	clr_search = Button("Clear Search", 800, 100, 350, 50, &Board::clear_search);
	
	

	

	 
}

void Board::set_blocks()
{
	blocks = new Cell * [rows];
	for (int i = 0; i < rows; i++)
	{
		blocks[i] = new Cell[cols];
	}

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			blocks[r][c] = Cell(r, c, WHITE);
		}
	}
}

void Board::set_parent()
{
	parent = new Cell * [rows];
	for (int i = 0; i < rows; i++)
	{
		parent[i] = new Cell[cols];
	}

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			parent[r][c] = Cell(r, c, WHITE);
		}
	}
}

void Board::initialize_lists()
{
	set_blocks();
	set_parent();
	
}

void Board::draw_board()
{
	ClearBackground(LIGHTGRAY); 

	for (int r = 0; r < rows; r++) // draw cells
	{
		for (int c = 0; c < cols; c++)
		{
			blocks[r][c].display_cell();
		}
	}


	for (int r = 0; r < rows; r++) // draw grid lines
	{
		DrawLine(0, 200 + r * 20, 1200, 200 + r * 20, BLACK);
	}
	for (int c = 0; c < cols; c++)
	{
		DrawLine(c * 20, 200, c * 20, 700, BLACK);
	}

	
}

tuple<int, int> Board::get_pos()
{
	int r = floor((GetMouseY()-200)/20);
	int c = floor(GetMouseX()/20);
	tuple<int, int> pos = std::make_tuple(r, c);
		return pos;
}

void Board::set_start()
{

	//something
}

void Board::set_goal()
{
	// something
}

void Board::draw_obstacles(int r, int c)
{
	blocks[r][c].set_color(BLACK);
	blocks[r][c].display_cell();

}

void Board::clear_board()
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			blocks[r][c].set_color(WHITE);
			blocks[r][c].display_cell();
		}
	}
}

void Board::clear_search()
{
	//something
}

void Board::find_path()
{
	//something
}

void Board::A_star()
{
	cout << "A*" << endl;
}

void Board::Dijkstra()
{
	cout << "Dijkstra" << endl;
}

void Board::BFS()
{
	cout << "BFS" << endl;
}

void Board::RUN()
{
	initialize_lists(); // set all cells to white
	InitWindow(width, height, "Search Algorithm Visualizer");
	SetTargetFPS(fps);
	Button button_list[7] = { A_button, D_button, BFS_button, start_button, goal_button, clr_board, clr_search };
	while (!WindowShouldClose()) // while loop that controls the rest
	{
		BeginDrawing();


		draw_board(); 

		A_button.draw_box();
		A_button.draw_text();

		D_button.draw_box();
		D_button.draw_text();

		BFS_button.draw_box();
		BFS_button.draw_text();

		start_button.draw_box();
		start_button.draw_text();

		goal_button.draw_box();
		goal_button.draw_text();

		clr_board.draw_box();
		clr_board.draw_text();
		
		clr_search.draw_box();
		clr_search.draw_text();


		for (int i=0;i<7;i++)
		{
			if (CheckCollisionPointRec(GetMousePosition(), button_list[i].textbox)) button_list[i].mouseOn = true;
			else  button_list[i].mouseOn = false;
		}
		for (int i = 0; i < 7; i++)
		{
			if (button_list[i].mouseOn)
			{
				DrawRectangleLines((int)button_list[i].textbox.x, (int)button_list[i].textbox.y, (int)button_list[i].textbox.width, (int)button_list[i].textbox.height, GREEN);
			}
			else DrawRectangleLines((int)button_list[i].textbox.x, (int)button_list[i].textbox.y, (int)button_list[i].textbox.width, (int)button_list[i].textbox.height, BLACK);
		} 

		

		


		// game logic

		if (IsMouseButtonDown(0))
		{
			if (GetMouseY() > 200)
			{
				tuple<int, int> coord = get_pos();
				draw_obstacles(std::get<0>(coord), std::get<1>(coord));
			}
			else if (GetMouseY() < 200)
			{

				for (int i = 0; i < 7; i++)
				{
					if (CheckCollisionPointRec(GetMousePosition(), button_list[i].textbox)) (button_list[i].*func)();
					
				}

			}
		}


		EndDrawing();

	}
}
Board::~Board()
{
	delete blocks;
	delete parent;
}