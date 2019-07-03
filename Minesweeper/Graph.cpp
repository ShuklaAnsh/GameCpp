#include "Graph.hpp"
#include <iostream>

Graph::Graph(int rows, int cols) : ROWS(rows), COLS(cols)
{
    //init graph
    for (int y = 0; y < ROWS; y++)
    {
        std::vector<Node> row;
        for (int x = 0; x < COLS; x++)
        {
            Node node;
            node.x = x;
            node.y = y;
            node.value = 0;
            node.visited = false;
            row.emplace_back(std::move(node));
        }
        m_grid.emplace_back(std::move(row));
    }
    //init neighbours
    m_border_node.value = -1;
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            Node &node = m_grid.at(y).at(x);
            
            //corner conditions
            //top-left
            if ( ( x == 0 ) && ( y == 0 ))
            {
                Node &right = m_grid.at(y).at(x+1);
                Node &bottom = m_grid.at(y+1).at(x);
                Node &bottom_right = m_grid.at(y+1).at(x+1);
                node.neighbours[CELL_POS::LEFT] = &m_border_node;
                node.neighbours[CELL_POS::TOP] = &m_border_node;
                node.neighbours[CELL_POS::TOP_LEFT] = &m_border_node;
                node.neighbours[CELL_POS::RIGHT] = &right;
                node.neighbours[CELL_POS::BOTTOM] = &bottom;
                node.neighbours[CELL_POS::BOTTOM_RIGHT] = &bottom_right;
                right.neighbours[CELL_POS::LEFT] = &node;
                bottom.neighbours[CELL_POS::TOP] = &node;
                bottom_right.neighbours[CELL_POS::TOP_LEFT] = &node;
            }
            //top-right
            else if ( ( x == (COLS-1) ) && ( y == 0 ))
            {
                Node &left = m_grid.at(y).at(x-1);
                Node &bottom = m_grid.at(y+1).at(x);
                Node &bottom_left = m_grid.at(y+1).at(x-1);
                node.neighbours[CELL_POS::RIGHT] = &m_border_node;
                node.neighbours[CELL_POS::TOP] = &m_border_node;
                node.neighbours[CELL_POS::TOP_RIGHT] = &m_border_node;
                node.neighbours[CELL_POS::LEFT] = &left;
                node.neighbours[CELL_POS::BOTTOM] = &bottom;
                node.neighbours[CELL_POS::BOTTOM_LEFT] = &bottom_left;
                left.neighbours[CELL_POS::RIGHT] = &node;
                bottom.neighbours[CELL_POS::TOP] = &node;
                bottom_left.neighbours[CELL_POS::TOP_RIGHT] = &node;
            }
            //bottom-right
            else if ( ( x == (COLS-1) ) && ( y == (ROWS-1) ))
            {
                Node &top = m_grid.at(y-1).at(x);
                Node &left = m_grid.at(y).at(x-1);
                Node &top_left = m_grid.at(y-1).at(x-1);
                node.neighbours[CELL_POS::RIGHT] = &m_border_node;
                node.neighbours[CELL_POS::BOTTOM] = &m_border_node;
                node.neighbours[CELL_POS::BOTTOM_RIGHT] = &m_border_node;
                node.neighbours[CELL_POS::LEFT] = &left;
                node.neighbours[CELL_POS::TOP] = &top;
                node.neighbours[CELL_POS::TOP_LEFT] = &top_left;
                left.neighbours[CELL_POS::RIGHT] = &node;
                top.neighbours[CELL_POS::BOTTOM] = &node;
                top_left.neighbours[CELL_POS::BOTTOM_RIGHT] = &node;
            }
            //bottom-left
            else if ( ( x == 0 ) && ( y == (ROWS-1) ))
            {
                Node &right = m_grid.at(y).at(x+1);
                Node &top = m_grid.at(y-1).at(x);
                Node &top_right = m_grid.at(y-1).at(x+1);
                node.neighbours[CELL_POS::LEFT] = &m_border_node;
                node.neighbours[CELL_POS::BOTTOM] = &m_border_node;
                node.neighbours[CELL_POS::BOTTOM_LEFT] = &m_border_node;
                node.neighbours[CELL_POS::RIGHT] = &right;
                node.neighbours[CELL_POS::TOP] = &top;
                node.neighbours[CELL_POS::TOP_RIGHT] = &top_right;
                right.neighbours[CELL_POS::LEFT] = &node;
                top.neighbours[CELL_POS::BOTTOM] = &node;
                top_right.neighbours[CELL_POS::BOTTOM_LEFT] = &node;
            }
            //border conditions
            //left border
            else if (x == 0)
            {
                Node &top = m_grid.at(y-1).at(x);
                Node &bottom = m_grid.at(y+1).at(x);
                node.neighbours[CELL_POS::LEFT] = &m_border_node;
                node.neighbours[CELL_POS::TOP] = &top;
                node.neighbours[CELL_POS::BOTTOM] = &bottom;
                bottom.neighbours[CELL_POS::TOP] = &node;
                top.neighbours[CELL_POS::BOTTOM] = &node;
            }
            //top border
            else if (y == 0)
            {
                Node &left = m_grid.at(y).at(x-1);
                Node &right = m_grid.at(y).at(x+1);
                node.neighbours[CELL_POS::TOP] = &m_border_node;
                node.neighbours[CELL_POS::LEFT] = &left;
                node.neighbours[CELL_POS::RIGHT] = &right;
                left.neighbours[CELL_POS::RIGHT] = &node;
                right.neighbours[CELL_POS::LEFT] = &node;
            }
            //right border
            else if (x == (COLS-1))
            {
                node.neighbours[CELL_POS::RIGHT] = &m_border_node;
                Node &top = m_grid.at(y-1).at(x);
                Node &bottom = m_grid.at(y+1).at(x);
                node.neighbours[CELL_POS::TOP] = &top;
                node.neighbours[CELL_POS::BOTTOM] = &bottom;
                bottom.neighbours[CELL_POS::TOP] = &node;
                top.neighbours[CELL_POS::BOTTOM] = &node;
            }
            //bottom border
            else if (y == (ROWS-1))
            {
                node.neighbours[CELL_POS::BOTTOM] = &m_border_node;
                Node &left = m_grid.at(y).at(x-1);
                Node &right = m_grid.at(y).at(x+1);
                node.neighbours[CELL_POS::LEFT] = &left;
                node.neighbours[CELL_POS::RIGHT] = &right;
                left.neighbours[CELL_POS::RIGHT] = &node;
                right.neighbours[CELL_POS::LEFT] = &node;
            }
            //everything else
            else
            {
                Node &left = m_grid.at(y).at(x-1);
                Node &top = m_grid.at(y-1).at(x);
                Node &right = m_grid.at(y).at(x+1);
                Node &bottom = m_grid.at(y+1).at(x);
                Node &top_left = m_grid.at(y-1).at(x-1);
                Node &top_right = m_grid.at(y-1).at(x+1);
                Node &bottom_left = m_grid.at(y+1).at(x-1);
                Node &bottom_right = m_grid.at(y+1).at(x+1);
                node.neighbours[CELL_POS::LEFT] = &left;
                node.neighbours[CELL_POS::TOP] = &top;
                node.neighbours[CELL_POS::RIGHT] = &right;
                node.neighbours[CELL_POS::BOTTOM] = &bottom;
                node.neighbours[CELL_POS::BOTTOM_LEFT] = &bottom_left;
                node.neighbours[CELL_POS::BOTTOM_RIGHT] = &bottom_right;
                node.neighbours[CELL_POS::TOP_LEFT] = &top_left;
                node.neighbours[CELL_POS::TOP_RIGHT] = &top_right;
                left.neighbours[CELL_POS::RIGHT] = &node;
                top.neighbours[CELL_POS::BOTTOM] = &node;
                right.neighbours[CELL_POS::LEFT] = &node;
                bottom.neighbours[CELL_POS::TOP] = &node;
                bottom_right.neighbours[CELL_POS::BOTTOM_RIGHT] = &node;
                bottom_left.neighbours[CELL_POS::BOTTOM_LEFT] = &node;
                top_right.neighbours[CELL_POS::TOP_RIGHT] = &node;
                top_left.neighbours[CELL_POS::TOP_LEFT] = &node;
            }
        }
    }
}

Graph::~Graph()
{
}

void Graph::printGraph()
{
    std::string graph = "\n";
    for (int y = 0; y < ROWS; y++)
    {
        std::string row;
        for (int x = 0; x < COLS; x++)
        {
            std::string val = "[" + std::to_string(m_grid.at(y).at(x).visited) + "]";
            row += m_grid.at(y).at(x).visited ? val : "[ ]";
        }
        graph += row + "\n";
    }
    graph += "\n";
    std::cout << graph;
}

void Graph::search(int x_i, int y_i, int val = 0)
{
    m_grid.at(y_i).at(x_i).visited = true;
    m_grid.at(y_i).at(x_i).value = val;
    visitNeighbours(m_grid.at(y_i).at(x_i), val);
}

void Graph::visitNeighbours(Node &node, int val)
{
    for (int i = 0; i < node.neighbours.size(); i++)
    // for (int i = 0; i < node.neighbours.size(); i++)
    {
        if(node.neighbours.at(i)->value == -1 ){
            continue;
        }
        printf(" ( %d, %d ) : %d\n", node.neighbours.at(i)->x, node.neighbours.at(i)->y, i);
    }
    printf("\n");
}

int main()
{
    Graph * G = new Graph(10, 10);
    G->search(0, 0);
    G->printGraph();
    delete G;
    return 0;
}