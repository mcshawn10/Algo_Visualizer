void Board::BFS()
{
    vector<Cell> visited;
    queue<Cell> q;
    Cell current_cell = start;
    Cell temp;

    // Add start cell to both queue and list of visited cells
    q.push(current_cell);
    visited.push_back(current_cell);

    while (!q.empty())
    {
        if (current_cell == goal)
        {
            found = true;
            break;
        }

        if (0 <= current_cell.row + 1 && current_cell.row + 1 <= 24)
        {
            temp = current_cell;
            q.push(blocks[current_cell.row + 1][current_cell.col]);
        }
        if (0 <= current_cell.row - 1 && current_cell.row + 1 <= 24 && (current_cell.row - 1).color_str != "BLACK")
        {
            q.push(blocks[current_cell.row - 1][current_cell.col]);
        }
        if (0 <= current_cell.col && current_cell.col - 1 <= 59 && (current_cell.col + 1).color_str != "BLACK")
        {
            q.push(blocks[current_cell.row][current_cell.col + 1]);
        }
        if (0 <= current_cell.col + 1 && current_cell.col + 1 <= 59 && (current_cell.col - 1).color_str != "BLACK")
        {
            q.push(blocks[current_cell.row][current_cell.col - 1]);
        }
    }

}


// Base BFS algorithm to use as reference
/*
#include <iostream>
#include <list>

using namespace std;

class Graph {
    int numVertices;
    list<int>* adjLists;
    bool* visited;

public:
    Graph(int vertices);
    void addEdge(int src, int dest);
    void BFS(int startVertex);
};

// Create a graph with given vertices,
// and maintain an adjacency list
Graph::Graph(int vertices) {
    numVertices = vertices;
    adjLists = new list<int>[vertices];
}

// Add edges to the graph
void Graph::addEdge(int src, int dest) {
    adjLists[src].push_back(dest);
    adjLists[dest].push_back(src);
}

// BFS algorithm
void Graph::BFS(int startVertex) {
    visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;

    list<int> queue;

    visited[startVertex] = true;
    queue.push_back(startVertex);

    list<int>::iterator i;

    while (!queue.empty()) {
        int currVertex = queue.front();
        cout << "Visited " << currVertex << " ";
        queue.pop_front();

        for (i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i) {
            int adjVertex = *i;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue.push_back(adjVertex);
            }
        }
    }
}

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    //g.addEdge(2, 0);
    //g.addEdge(2, 3);
    g.addEdge(3, 3);
    g.addEdge(2, 4);

    g.BFS(0);

    return 0;
}*/
