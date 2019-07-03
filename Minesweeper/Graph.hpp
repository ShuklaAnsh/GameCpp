#include <vector>
#include <array>

class Graph
{
private:

    struct Node
    {
        bool visited;
        int x, y, value;
        std::array<Node *, 4> neighbours;
    };
    
public:
    Graph(int rows, int cols);
    ~Graph();
    void printGraph();
    void search(int x_i, int y_i, int val);
    void visitNeighbours(Node &node, int val);

private:
    std::vector<std::vector<Node> > m_grid;
    int ROWS;
    int COLS;
    Node m_border_node;
};