#include "Graph.hpp"
#include <iostream>

Graph::Graph(int rows, int cols) : ROWS(rows), COLS(cols)
{
    m_pos_names[CELL_POS::LEFT] = "LEFT";
    m_pos_names[CELL_POS::TOP_LEFT] = "TOP_LEFT";
    m_pos_names[CELL_POS::TOP] = "TOP";
    m_pos_names[CELL_POS::TOP_RIGHT] = "TOP_RIGHT";
    m_pos_names[CELL_POS::RIGHT] = "RIGHT";
    m_pos_names[CELL_POS::BOTTOM_RIGHT] = "BOTTOM_RIGHT";
    m_pos_names[CELL_POS::BOTTOM] = "BOTTOM";
    m_pos_names[CELL_POS::BOTTOM_LEFT] = "BOTTOM_LEFT";

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
                addNeighbours(node, m_border_node, m_border_node, m_border_node, m_border_node, right, bottom_right, bottom, m_border_node);
                right.neighbours[CELL_POS::LEFT] = &node;
                bottom_right.neighbours[CELL_POS::TOP_LEFT] = &node;
                bottom.neighbours[CELL_POS::TOP] = &node;
            }
            //top-right
            else if ( ( x == (COLS-1) ) && ( y == 0 ))
            {
                Node &left = m_grid.at(y).at(x-1);
                Node &bottom = m_grid.at(y+1).at(x);
                Node &bottom_left = m_grid.at(y+1).at(x-1);
                addNeighbours(node, left, m_border_node, m_border_node, m_border_node, m_border_node, m_border_node, bottom, bottom_left);
                bottom.neighbours[CELL_POS::TOP] = &node;
                bottom_left.neighbours[CELL_POS::TOP_RIGHT] = &node;
                left.neighbours[CELL_POS::RIGHT] = &node;
            }
            //bottom-right
            else if ( ( x == (COLS-1) ) && ( y == (ROWS-1) ))
            {
                Node &top = m_grid.at(y-1).at(x);
                Node &left = m_grid.at(y).at(x-1);
                Node &top_left = m_grid.at(y-1).at(x-1);
                addNeighbours(node, left, top_left, top, m_border_node, m_border_node, m_border_node, m_border_node, m_border_node);
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
                addNeighbours(node, m_border_node, m_border_node, top, top_right, right, m_border_node, m_border_node, m_border_node);
                right.neighbours[CELL_POS::LEFT] = &node;
                top.neighbours[CELL_POS::BOTTOM] = &node;
                top_right.neighbours[CELL_POS::BOTTOM_LEFT] = &node;
            }
            //border conditions
            //left border
            else if (x == 0)
            {
                Node &top = m_grid.at(y-1).at(x);
                Node &top_right = m_grid.at(y-1).at(x+1);
                Node &right = m_grid.at(y).at(x+1);
                Node &bottom_right = m_grid.at(y+1).at(x+1);
                Node &bottom = m_grid.at(y+1).at(x);
                addNeighbours(node, m_border_node, m_border_node, top, top_right, right, bottom_right, bottom, m_border_node);
                top.neighbours[CELL_POS::BOTTOM] = &node;
                top_right.neighbours[CELL_POS::BOTTOM_LEFT] = &node;
                right.neighbours[CELL_POS::LEFT] = &node;
                bottom_right.neighbours[CELL_POS::TOP_LEFT] = &node;
                bottom.neighbours[CELL_POS::TOP] = &node;
            }
            //top border
            else if (y == 0)
            {
                Node &left = m_grid.at(y).at(x-1);
                Node &right = m_grid.at(y).at(x+1);
                Node &bottom_right = m_grid.at(y+1).at(x+1);
                Node &bottom = m_grid.at(y+1).at(x);
                Node &bottom_left = m_grid.at(y+1).at(x-1);
                addNeighbours(node, left, m_border_node, m_border_node, m_border_node, right, bottom_right, bottom, bottom_left);
                left.neighbours[CELL_POS::RIGHT] = &node;
                right.neighbours[CELL_POS::LEFT] = &node;
                bottom_right.neighbours[CELL_POS::TOP_LEFT] = &node;
                bottom.neighbours[CELL_POS::TOP] = &node;
                bottom_left.neighbours[CELL_POS::TOP_RIGHT] = &node;
            }
            //right border
            else if (x == (COLS-1))
            {
                Node &left = m_grid.at(y).at(x-1);
                Node &top_left = m_grid.at(y-1).at(x-1);
                Node &top = m_grid.at(y-1).at(x);
                Node &bottom = m_grid.at(y+1).at(x);
                Node &bottom_left = m_grid.at(y+1).at(x-1);
                addNeighbours(node, left, top_left, top, m_border_node, m_border_node, m_border_node, bottom, bottom_left);
                left.neighbours[CELL_POS::RIGHT] = &node;
                top_left.neighbours[CELL_POS::BOTTOM_RIGHT] = &node;
                top.neighbours[CELL_POS::BOTTOM] = &node;
                bottom.neighbours[CELL_POS::TOP] = &node;
                bottom_left.neighbours[CELL_POS::TOP_RIGHT] = &node;
            }
            //bottom border
            else if (y == (ROWS-1))
            {
                Node &left = m_grid.at(y).at(x-1);
                Node &top_left = m_grid.at(y-1).at(x-1);
                Node &top = m_grid.at(y-1).at(x);
                Node &top_right = m_grid.at(y-1).at(x+1);
                Node &right = m_grid.at(y).at(x+1);
                addNeighbours(node, left, top_left, top, top_right, right, m_border_node, m_border_node, m_border_node);
                left.neighbours[CELL_POS::RIGHT] = &node;
                top_left.neighbours[CELL_POS::BOTTOM_RIGHT] = &node;
                top.neighbours[CELL_POS::BOTTOM] = &node;
                top_right.neighbours[CELL_POS::BOTTOM_LEFT] = &node;
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
                addNeighbours(node, left, top_left, top, top_right, right, bottom_right, bottom, bottom_left);
                left.neighbours[CELL_POS::RIGHT] = &node;
                top.neighbours[CELL_POS::BOTTOM] = &node;
                right.neighbours[CELL_POS::LEFT] = &node;
                bottom.neighbours[CELL_POS::TOP] = &node;
                bottom_right.neighbours[CELL_POS::TOP_LEFT] = &node;
                bottom_left.neighbours[CELL_POS::TOP_RIGHT] = &node;
                top_right.neighbours[CELL_POS::BOTTOM_LEFT] = &node;
                top_left.neighbours[CELL_POS::BOTTOM_RIGHT] = &node;
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
        printf("%s ( %d, %d )\n", m_pos_names[i].c_str(), node.neighbours.at(i)->x, node.neighbours.at(i)->y);
    }
    printf("\n");
}

void Graph::addNeighbours(Node& node, Node& left, Node& top_left, Node& top, Node& top_right, Node& right, Node& bottom_right, Node& bottom, Node& bottom_left)
{
    node.neighbours[CELL_POS::LEFT] = &left;
    node.neighbours[CELL_POS::TOP_LEFT] = &top_left;
    node.neighbours[CELL_POS::TOP] = &top;
    node.neighbours[CELL_POS::TOP_RIGHT] = &top_right;
    node.neighbours[CELL_POS::RIGHT] = &right;
    node.neighbours[CELL_POS::BOTTOM_RIGHT] = &bottom_right;
    node.neighbours[CELL_POS::BOTTOM] = &bottom;
    node.neighbours[CELL_POS::BOTTOM_LEFT] = &bottom_left;
}

int main()
{
    Graph * G = new Graph(10, 10);
    G->search(0, 9);
    G->printGraph();
    delete G;
    return 0;
}