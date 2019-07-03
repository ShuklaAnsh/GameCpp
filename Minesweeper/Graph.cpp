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
                node.neighbours[0] = &m_border_node;
                node.neighbours[1] = &m_border_node;
                Node &right = m_grid.at(y).at(x+1);
                Node &bottom = m_grid.at(y+1).at(x);
                node.neighbours[2] = &right;
                node.neighbours[3] = &bottom;
                right.neighbours[0] = &node;
                bottom.neighbours[1] = &node;
            }
            //top-right
            else if ( ( x == (COLS-1) ) && ( y == 0 ))
            {
                node.neighbours[2] = &m_border_node;
                node.neighbours[1] = &m_border_node;
                Node &left = m_grid.at(y).at(x-1);
                Node &bottom = m_grid.at(y+1).at(x);
                node.neighbours[0] = &left;
                node.neighbours[3] = &bottom;
                left.neighbours[2] = &node;
                bottom.neighbours[1] = &node;
            }
            //bottom-right
            else if ( ( x == (COLS-1) ) && ( y == (ROWS-1) ))
            {
                node.neighbours[2] = &m_border_node;
                node.neighbours[3] = &m_border_node;
                Node &left = m_grid.at(y).at(x-1);
                Node &top = m_grid.at(y-1).at(x);
                node.neighbours[0] = &left;
                node.neighbours[1] = &top;
                left.neighbours[2] = &node;
                top.neighbours[3] = &node;
            }
            //bottom-left
            else if ( ( x == 0 ) && ( y == (ROWS-1) ))
            {
                node.neighbours[0] = &m_border_node;
                node.neighbours[3] = &m_border_node;
                Node &right = m_grid.at(y).at(x+1);
                Node &top = m_grid.at(y-1).at(x);
                node.neighbours[2] = &right;
                node.neighbours[1] = &top;
                right.neighbours[0] = &node;
                top.neighbours[3] = &node;
            }
            //border conditions
            //left border
            else if (x == 0)
            {
                node.neighbours[0] = &m_border_node;
                Node &top = m_grid.at(y-1).at(x);
                Node &bottom = m_grid.at(y+1).at(x);
                node.neighbours[1] = &top;
                node.neighbours[3] = &bottom;
                bottom.neighbours[1] = &node;
                top.neighbours[3] = &node;
            }
            //top border
            else if (y == 0)
            {
                node.neighbours[1] = &m_border_node;
                Node &left = m_grid.at(y).at(x-1);
                Node &right = m_grid.at(y).at(x+1);
                node.neighbours[0] = &left;
                node.neighbours[2] = &right;
                left.neighbours[2] = &node;
                right.neighbours[0] = &node;
            }
            //right border
            else if (x == (COLS-1))
            {
                node.neighbours[2] = &m_border_node;
                Node &top = m_grid.at(y-1).at(x);
                Node &bottom = m_grid.at(y+1).at(x);
                node.neighbours[1] = &top;
                node.neighbours[3] = &bottom;
                bottom.neighbours[1] = &node;
                top.neighbours[3] = &node;
            }
            //bottom border
            else if (y == (ROWS-1))
            {
                node.neighbours[3] = &m_border_node;
                Node &left = m_grid.at(y).at(x-1);
                Node &right = m_grid.at(y).at(x+1);
                node.neighbours[0] = &left;
                node.neighbours[2] = &right;
                left.neighbours[2] = &node;
                right.neighbours[0] = &node;
            }
            //everything else
            else
            {
                Node &left = m_grid.at(y).at(x-1);
                Node &top = m_grid.at(y-1).at(x);
                Node &right = m_grid.at(y).at(x+1);
                Node &bottom = m_grid.at(y+1).at(x);
                node.neighbours[0] = &left;
                node.neighbours[1] = &top;
                node.neighbours[2] = &right;
                node.neighbours[3] = &bottom;
                left.neighbours[2] = &node;
                top.neighbours[3] = &node;
                right.neighbours[0] = &node;
                bottom.neighbours[1] = &node;
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
    G->search(5, 9);
    G->printGraph();
    delete G;
    return 0;
}