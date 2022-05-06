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
	/*blocks = new Cell * [rows];
	for (int i = 0; i < rows; i++)
	{
		blocks[i] = new Cell[cols];
	}

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			blocks[r][c] = Cell(r, c, WHITE, "WHITE");
		}
	}*/
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			blocks.push_back(Cell(r, c, WHITE, "WHITE"));
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
			parent[r][c] = Cell(r, c, WHITE, "WHITE");
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

	/*for (int r = 0; r < rows; r++) // draw cells
	{
		for (int c = 0; c < cols; c++)
		{
			int index = r * c;
			blocks.at(index).display_cell();
		}
	}*/
	for (int i = 0; i < (25 * 60); i++)
	{
		blocks.at(i)->display_cell();
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
	
	//tuple<int, int> pos = make_tuple(r, c);
	return (r*60)+c;
}

void Board::set_start()
{
	
	int r = rand() % 25;
	int c = rand() % 60;

	int index = r * c;
	start = blocks.at(index);
	
	start->set_color(GREEN);
	start->set_color_str("GREEN");
	start->display_cell();
}

void Board::set_goal()
{
	int r = rand() % 25;
	int c = rand() % 60;
	int index = r * c;
	goal = blocks.at(index);

	goal->set_color(RED);
	goal->set_color_str("RED");
	goal->display_cell();
}

void Board::draw_obstacles(int i)
{
	int index = i;
	blocks.at(index)->set_color(BLACK);
	blocks.at(index)->set_color_str("BLACK");
	blocks.at(index)->display_cell();

}

void Board::clear_board()
{
	for (auto i : blocks)
	{
		i->set_color(WHITE);
		i->set_color_str("WHITE");
		i->display_cell();
	}
}

void Board::clear_search()
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			int index = r * c;
			string temp_color = blocks.at(index)->get_color_str();
			if (temp_color == "BLUE")
			{
				blocks.at(index)->set_color(WHITE);
				blocks.at(index)->set_color_str("WHITE");
				blocks.at(index)->display_cell();
			}

		}
	}
}

void Board::find_path()
{
	Cell* p = goal;
	if (found)
	{
		while (p != start)
		{
			path.push_back(*p);

			p = &parent[p->row][p->col];
		}

		for (Cell i : path)
		{
			if (i.get_color_str() != "RED" && i.get_color_str() != "GREEN")
			{
				i.set_color(YELLOW);
				i.set_color_str("YELLOW");
				i.display_cell();
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
	start->h = std::numeric_limits<int>::max();
	goal->h = 0;
	vector <Cell*> children;

	priority_queue< tuple<int, int, Cell> > OPEN;
	vector <Cell> O_ls;
	tuple<int, int, Cell> init_tup = make_tuple(m_dist(*start, *goal), 0, *start);
	vector <Cell>::iterator cl_itr;
	vector <Cell>::iterator o_itr;
	OPEN.push(init_tup);

	while (!OPEN.empty())
	{
		tuple<int, int, Cell> curr_tuple = OPEN.top();
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
				int index = (temp_r + 1) * temp_c;
				children.push_back(blocks.at(index));

			}
			if (0 <= current_cell.row - 1 && current_cell.row - 1 <= 24)
			{
				int index = (temp_r - 1) * temp_c;
				children.push_back(blocks.at(index));

			}

			if (0 <= current_cell.col - 1 && current_cell.col - 1 <= 59)
			{
				int index = (temp_c - 1) * temp_r;
				children.push_back(blocks.at(index));
			}
			if (0 <= current_cell.col + 1 && current_cell.col + 1 <= 59)
			{
				int index = (temp_c + 1) * temp_r;
				children.push_back(blocks.at(index));
			}

			for (auto child : children)
			{
				if (child->color_str == "BLACK") continue;

				child->g = m_dist(*child, *start);
				child->h = m_dist(*child, *goal);
				child->f = child->g + child->h;

				int cost = current_cell.g + 1;
				cl_itr = find(CLOSED.begin(), CLOSED.end(), child);
				o_itr = find(O_ls.begin(), O_ls.end(), child);


				if (o_itr != O_ls.end() && cost < child->g)
				{
					cout << "first if statement" << endl;
				}


				else if (cl_itr != CLOSED.end() && child->g < cost) CLOSED.erase(cl_itr);

				else if (o_itr == O_ls.end() && cl_itr == CLOSED.end())
				{
					child->g = cost;
					child->f = child->g + child->h;
					O_ls.push_back(*child);
					tuple<int, int, Cell> tup = make_tuple(child->h, child->g, *child);
					OPEN.push(tup);

					parent[child->row][child->col] = current_cell;

					if (child->color_str != "RED" && child->color_str != "GREEN")
					{
						child->set_color(BLUE);
						child->set_color_str("BLUE");
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
	priority_queue< tuple<int, Cell> > OPEN;
	vector <Cell> CLOSED;

	start->h = 0;

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			if (blocks.at(i*j) != start)
			{
				blocks.at(i*j)->set_h(1000);
			}
		}
	}
	
	tuple<int, Cell> init_tup = make_tuple(start->h, *start); // I think im making a copy of start right here
	cout << "   " << endl;
	cout << "initial push: " << start->h << ", " << start->color_str << endl;

	
	OPEN.push(init_tup);	


	while (!OPEN.empty())
	{
		cout << "working 1" << endl;
		
		tuple<int, Cell> current_tup; 
		int dist_curr;
		Cell current_cell; // a new Cell in the stack, should this be a pointer?... I need to access the ACTUAL cell ie blocks[r][c]

		
		//std::tie(dist_curr, current_cell) = OPEN.top(); //extracting from the Q, am I getting a copy? - yes
		current_tup = OPEN.top();
		OPEN.pop();
		dist_curr = std::get<0>(current_tup);
		current_cell = std::get<1>(current_tup);

		cout <<"current distance and cell: " << dist_curr << ", " << current_cell.color_str << endl;
		cout << "current: " << current_cell.row << " " << current_cell.col << endl;

		CLOSED.push_back(current_cell);

		if (current_cell == (*goal))
		{
			found = true;
			break;
		}

		vector<Cell*> children;
		//Cell child_s;
		int temp_r = current_cell.row;
		int temp_c = current_cell.col;


		if (0 <= temp_r + 1 && temp_r + 1 <= 24) // HOW TO ACCESS THE ORIGINAL
		{
			int index = (temp_r + 1) * temp_c;
			children.push_back(blocks.at(index)); 

		}
		if (0 <= current_cell.row - 1 && current_cell.row - 1 <= 24)
		{
			int index = (temp_r - 1) * temp_c;
			children.push_back(blocks.at(index));
			
		}

		if (0 <= current_cell.col - 1 && current_cell.col - 1 <= 59)
		{
			int index = (temp_c - 1) * temp_r;
			children.push_back(blocks.at(index));
		}
		if (0 <= current_cell.col + 1 && current_cell.col + 1 <= 59)
		{
			int index = (temp_c + 1) * temp_r;
			children.push_back(blocks.at(index));
		}
		

		for (Cell* child : children) // child is a pointer 
		{
			cout << "working 2" << endl;
			cout << child->row << " " << child->col << endl;

			if (child->color_str == "BLACK") continue;

			int alt = dist_curr + m_dist(current_cell, *child);
			cout << "alt, child.h: " << alt << ", " << child->h << endl;

			if (alt < child->h && find(CLOSED.begin(), CLOSED.end(), child) == CLOSED.end())
			{
				cout << "working 3" << endl;
				child->h = alt;
				cout << "working 3.1" << endl;

				tuple<int, Cell> tup = make_tuple(child->h, *child);
				cout << "working 3.2" << endl;

				OPEN.push(tup);
				//parent[child->row][child->col] = current_cell; //calls assignment operator
				cout << "working 3.3" << endl;

				if (*child == *goal)
				{
					found = true;
					break;
				}
				if (child->color_str == "WHITE")
				{
					cout << "working 4" << endl;
					
					child->set_color(BLUE);
					child->set_color_str("BLUE");
					child->display_cell();
				}
			}
		}
		children.clear();



	}
	//find_path();
}

void Board::BFS()
{
	list <Cell> Q;
	vector <Cell*> children;
	Q.push_front(*start);

	vector<Cell> visited;

	while (!Q.empty())
	{
		Cell current_cell = Q.front(); //this is the problem
		Q.pop_front();
		cout << "working 1" << endl;
		if (current_cell == *goal)
		{
			found = true;
			break;
		}

		else if (find(visited.begin(), visited.end(), current_cell) == visited.end())
		{
			int temp_r = current_cell.row;
			int temp_c = current_cell.col;
			visited.push_back(current_cell);
			if (0 <= temp_r + 1 && temp_r + 1 <= 24) // HOW TO ACCESS THE ORIGINAL
			{
				int index = (temp_r + 1) * temp_c;
				children.push_back(blocks.at(index));

			}
			if (0 <= current_cell.row - 1 && current_cell.row - 1 <= 24)
			{
				int index = (temp_r - 1) * temp_c;
				children.push_back(blocks.at(index));

			}

			if (0 <= current_cell.col - 1 && current_cell.col - 1 <= 59)
			{
				int index = (temp_c - 1) * temp_r;
				children.push_back(blocks.at(index));
			}
			if (0 <= current_cell.col + 1 && current_cell.col + 1 <= 59)
			{
				int index = (temp_c + 1) * temp_r;
				children.push_back(blocks.at(index));
			}

			for (auto child : children)
			{
				cout << "working 2" << endl;
				if (child->color_str == "BLACK" || find(visited.begin(), visited.end(), current_cell) != visited.end())
				{
					continue;
				}
				else if (*child == *goal)
				{
					parent[child->row][child->col] = current_cell;
					Q.clear();
				}

				else if (child->color_str != "RED" && child->color_str != "GREEN")
				{

					cout << "working 3" << endl;
					parent[child->row][child->col] = current_cell;
					Q.push_front(*child);
					child->set_color(BLUE);
					child->set_color_str("BLUE");
					child->display_cell();
				}
			}
			children.clear();

		}
		else continue;
	}
	find_path();
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
	//delete blocks;
	delete parent;
}