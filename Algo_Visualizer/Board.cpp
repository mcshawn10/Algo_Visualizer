#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <tuple>
#include <functional>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <random>
#include <cstdlib>
#include <limits>
#include "raylib.h"
#include "Board.h"
#include "Cell.h"

using std::cout; using std::cin; using std::endl;
using std::vector; using std::string; using std::tuple; using std::make_tuple;
using std::priority_queue; using std::find; using std::stack; using std::list;



Board::Board()
{
	width = 1200;
	height = 700;
	rows = 25; // number of rows
	cols = 60; // number of columns
	fps = 60;
	cell_size = 18;
	found = false;
	

	A_button = Button("A* Search", 20, 150, 300, 50);
	D_button = Button("Dijkstra",400, 150, 250, 50);
	BFS_button = Button("BFS", 700,150, 250, 50);
	start_button = Button("Start Cell",20, 50, 300, 50);
	goal_button = Button("Goal Cell",350, 50, 300, 50);
	clr_board = Button("Clear Board", 800, 50, 350, 50);
	clr_search = Button("Clear Search", 800, 100, 350, 50);
	
	

	

	 
}

void Board::set_blocks()
{
	blocks = new Cell * [rows];// array layer one
	block_ptrs = new Cell*[rows * cols]; 

	for (int i = 0; i < rows; i++)
	{
		blocks[i] = new Cell[cols]; // array layer two
	}
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			blocks[r][c] = Cell(r, c, WHITE, "WHITE"); // element access aka array layer 3
		}
	}

	for (int r = 0; r < rows; r++) // initialize pointer array
	{
		for (int c = 0; c < cols; c++)
		{
			block_ptrs[(r * 60) + c] = &blocks[r][c];
		}
	}



	
}

void Board::set_parent()
{
	parent = new Cell* [rows*cols];

	for (int r = 0; r < rows; r++) // initialize pointer array
	{
		for (int c = 0; c < cols; c++)
		{
			parent[(r * 60) + c] = &blocks[r][c];
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


	for (int i = 0; i < (25 * 60); i++)
	{
		block_ptrs[i]->display_cell();
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

int Board::get_pos()
{
	int r = floor((GetMouseY()-200)/20);
	int c = floor(GetMouseX()/20);
	
	
	return (r*60)+c;
}

void Board::set_start()
{
	
	int r = rand() % 25;
	int c = rand() % 60;

	
	start = &blocks[r][c];
	
	start->set_color(GREEN);
	start->set_color_str("GREEN");
	start->display_cell();
}

void Board::set_goal()
{
	int r = rand() % 25;
	int c = rand() % 60;
	
	goal = &blocks[r][c];

	goal->set_color(RED);
	goal->set_color_str("RED");
	goal->display_cell();
}

void Board::draw_obstacles(int i)
{
	
	block_ptrs[i]->set_color(BLACK);
	block_ptrs[i]->set_color_str("BLACK");
	block_ptrs[i]->display_cell();

}

void Board::clear_board()
{
	for (int i=0;i<(rows*cols); i++)
	{
		block_ptrs[i]->set_color(WHITE);
		block_ptrs[i]->set_color_str("WHITE");
		block_ptrs[i]->display_cell();
	}
	// should also delete the pointers and path ? 
	//delete[] parent;
}

void Board::clear_search()
{
	for (int i = 0; i < (rows * cols); i++)
	{
		
		
		string temp_color = block_ptrs[i]->get_color_str();

		if (temp_color == "SKYBLUE")
		{
			block_ptrs[i]->set_color(WHITE);
			block_ptrs[i]->set_color_str("WHITE");
			block_ptrs[i]->display_cell();
		}

		
	}
	//delete[] parent;
}

void Board::find_path()
{
	Cell* p = goal; // goal is a pointer to &blocks[r][c], I need p to be initialized to the same pointer?
	cout << goal->color_str << endl;
	cout << p->color_str << endl;
	cout << "find working 1" << endl;
	if (found)
	{
		while (*p != *start)
		{
			cout << p->row << ", " << p->col << endl;
			cout << p->color_str << endl;
			path.push_back(p);

			p = parent[(p->row * 60) + p->col];
			cout << p -> row << ", " << p->col << endl;
			cout << "find working 2" << endl;
		}

		for (Cell* i : path)
		{
			cout << "working 2" << endl;
			if (i->get_color_str() != "RED" && i->get_color_str() != "GREEN")
			{
				i->set_color(YELLOW);
				i->set_color_str("YELLOW");
				i->display_cell();
			}
		}
	}
	else
	{
		cout << "path not found" << endl;
	}
}

int Board::m_dist(const Cell& c1, const Cell& c2)
{

	return abs(c1.row - c2.row) + abs(c1.col - c2.col);
}

void Board::A_star()
{
	found = false;
	vector<Cell> CLOSED;

	start->g = 0;
	start->h = m_dist(*start, *goal);
	start->f = start->g + start->h;

	goal->h = 0;
	vector <Cell*> children;

	priority_queue< tuple<int, int, Cell> > OPEN;
	vector <Cell> O_ls;

	tuple<int, int, Cell> init_tup;
	init_tup = std::tie(start->h, start->g, *start);
	OPEN.push(init_tup);


	vector <Cell>::iterator cl_itr;
	vector <Cell>::iterator o_itr;

	while (!OPEN.empty())
	{
		tuple<int, int, Cell> curr_tuple;
		curr_tuple = OPEN.top();
		OPEN.pop();

		int h_curr = std::get<0> (curr_tuple);
		int g_curr = std::get<1>(curr_tuple);
		Cell current_cell = std::get<2>(curr_tuple);

		CLOSED.push_back(current_cell);
		O_ls.push_back(current_cell);

		
		if (current_cell == *goal)
		{
			found = true;
			break;
		}

		else
		{
			int temp_r = current_cell.row;
			int temp_c = current_cell.col;


			if (0 <= temp_r + 1 && temp_r + 1 <= 24) // HOW TO ACCESS THE ORIGINAL
			{
				int index = ((temp_r + 1) * 60) + temp_c;
				children.push_back(block_ptrs[index]);

			}
			if (0 <= current_cell.row - 1 && current_cell.row - 1 <= 24)
			{
				int index = ((temp_r - 1) * 60) + temp_c;
				children.push_back(block_ptrs[index]);

			}

			if (0 <= current_cell.col - 1 && current_cell.col - 1 <= 59)
			{
				int index = (temp_r * cols) + temp_c - 1;
				children.push_back(block_ptrs[index]);
			}
			if (0 <= current_cell.col + 1 && current_cell.col + 1 <= 59)
			{
				int index = (temp_r * cols) + temp_c + 1;
				children.push_back(block_ptrs[index]);
			}


			for (Cell* child : children)
			{
				if (child->color_str == "BLACK") continue;

				child->g = m_dist(*child, *start);
				child->h = m_dist(*child, *goal);
				child->f = child->g + child->h;

				int cost = current_cell.g + 1;
				cl_itr = find(CLOSED.begin(), CLOSED.end(), *child);
				o_itr = find(O_ls.begin(), O_ls.end(), *child);


				if (o_itr != O_ls.end() && cost < child->g)
				{
					// remove item from queue;
					//remove from open vector;
					O_ls.erase(o_itr);
				}


				else if (cl_itr != CLOSED.end() && child->g < cost) CLOSED.erase(cl_itr);

				else if (o_itr == O_ls.end() && cl_itr == CLOSED.end())
				{
					child->g = cost;
					child->f = child->g + child->h;
					O_ls.push_back(*child);
					tuple<int, int, Cell> tup;
					tup = std::tie(child->h, child->g, *child);
					OPEN.push(tup);

					parent[(child->row*60) + child->col] = &current_cell;

					if (child->color_str != "RED" && child->color_str != "GREEN")
					{
						child->set_color(SKYBLUE);
						child->set_color_str("SKYBLUE");
						child->display_cell();

					}


				}


			}
			children.clear();
			
		}

	}

}

void Board::Dijkstra()
{
	found = false;
	priority_queue< tuple<int, Cell> > OPEN;
	vector <Cell> CLOSED;

	start->h = 0;

	for (int i = 0; i < (rows*cols); i++)
	{
		
		if (block_ptrs[i] != start)
		{
			block_ptrs[i]->set_h(1000);
		}
		
	}
	
	
	tuple<int, Cell> init_tup;
	init_tup = std::tie(start->h, *start);
	

	
	OPEN.push(init_tup);	


	while (!OPEN.empty())
	{
		
		
		tuple<int, Cell> current_tup; 
		int dist_curr;
		Cell current_cell; 

		
		
		current_tup = OPEN.top();
		OPEN.pop();
		dist_curr = std::get<0>(current_tup);
		current_cell = std::get<1>(current_tup);

		

		CLOSED.push_back(current_cell);

		if (current_cell == (*goal))
		{
			found = true;
			break;
		}

		vector<Cell*> children;
		
		int temp_r = current_cell.row;
		int temp_c = current_cell.col;


		if (0 <= temp_r + 1 && temp_r + 1 <= 24) // HOW TO ACCESS THE ORIGINAL
		{
			int index = ((temp_r+1) * 60) + temp_c;
			children.push_back(block_ptrs[index]);

		}
		if (0 <= current_cell.row - 1 && current_cell.row - 1 <= 24)
		{
			int index = ((temp_r-1) * 60) + temp_c;
			children.push_back(block_ptrs[index]);
			
		}

		if (0 <= current_cell.col - 1 && current_cell.col - 1 <= 59)
		{
			int index = (temp_r*cols) + temp_c - 1;
			children.push_back(block_ptrs[index]);
		}
		if (0 <= current_cell.col + 1 && current_cell.col + 1 <= 59)
		{
			int index = (temp_r * cols) + temp_c + 1;
			children.push_back(block_ptrs[index]);
		}
		

		for (Cell* child : children) // child is a pointer 
		{

			if (child->color_str == "BLACK") continue;

			int alt = dist_curr + m_dist(current_cell, *child);
			

			if (alt < child->h && find(CLOSED.begin(), CLOSED.end(), *child) == CLOSED.end()) // NOT in closed --- && find(CLOSED.begin(), CLOSED.end(), *child) == CLOSED.end()
			{
				
				child->h = alt;
				

				
				tuple<int, Cell> tup;
				tup = std::tie(child->h, *child);
				

				OPEN.push(tup);


				parent[(child->row*60) + child->col] = &current_cell; // calls assignment operator
				

				if (*child == *goal)
				{
					found = true;
					break;
				}
				if (child->color_str == "WHITE")
				{
					
					child->set_color(SKYBLUE);
					child->set_color_str("SKYBLUE");
					child->display_cell();
				}
			}
			
		}
		children.clear();

	}
	find_path();
}

void Board::BFS()
{
	list <Cell*> Q;
	vector <Cell*> children;

	Q.push_front(start);

	vector<Cell*> visited;

	while (!Q.empty())
	{
		Cell* current_cell = Q.front(); //this is the problem
		Q.pop_front();
		
		if (current_cell == goal)
		{
			found = true;
			break;
		}

		else if (find(visited.begin(), visited.end(), current_cell) == visited.end())
		{
			visited.push_back(current_cell);

			int temp_r = current_cell->row;
			int temp_c = current_cell->col;


			if (0 <= temp_r + 1 && temp_r + 1 <= 24) // HOW TO ACCESS THE ORIGINAL
			{
				int index = ((temp_r + 1) * 60) + temp_c;
				children.push_back(block_ptrs[index]);

			}
			if (0 <= current_cell->row - 1 && current_cell->row - 1 <= 24)
			{
				int index = ((temp_r - 1) * 60) + temp_c;
				children.push_back(block_ptrs[index]);

			}

			if (0 <= current_cell->col - 1 && current_cell->col - 1 <= 59)
			{
				int index = (temp_r * cols) + temp_c - 1;
				children.push_back(block_ptrs[index]);
			}
			if (0 <= current_cell->col + 1 && current_cell->col + 1 <= 59)
			{
				int index = (temp_r * cols) + temp_c + 1;
				children.push_back(block_ptrs[index]);
			}

			for (Cell* child : children)
			{
				
				if (child->color_str == "BLACK" || find(visited.begin(), visited.end(), child) != visited.end())
				{
					continue;
				}
				else if (*child == *goal)
				{
					parent[(child->row*60) + child->col] = current_cell;
					Q.clear();
				}

				else if (child->color_str == "WHITE")
				{
					parent[(child->row * 60) + child->col] = current_cell;
					Q.push_back(child);
					child->set_color(SKYBLUE);
					child->set_color_str("SKYBLUE");
					child->display_cell();
				}
			}
			children.clear();

		}
		else continue;
	}
	//find_path();
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

		
		
		if (IsMouseButtonPressed(0) && GetMouseY() < 200)
		{
			if (CheckCollisionPointRec(GetMousePosition(), button_list[0].textbox)) this->A_star();

			else if (CheckCollisionPointRec(GetMousePosition(), button_list[1].textbox)) this->Dijkstra();

			else if (CheckCollisionPointRec(GetMousePosition(), button_list[2].textbox)) this->BFS();

			else if (CheckCollisionPointRec(GetMousePosition(), button_list[3].textbox)) this->set_start();

			else if (CheckCollisionPointRec(GetMousePosition(), button_list[4].textbox)) this->set_goal();

			else if (CheckCollisionPointRec(GetMousePosition(), button_list[5].textbox)) this->clear_board();

			else if (CheckCollisionPointRec(GetMousePosition(), button_list[6].textbox)) this->clear_search();
		}
			
		
		else if (IsMouseButtonDown(0) && GetMouseY() > 200)
		{
			
			int position = get_pos();
			draw_obstacles(position);
			
		}


		EndDrawing();

	}
}



Board::~Board()
{
	//delete[] blocks;
	//delete[] block_ptrs;
	//delete[] parent;
}