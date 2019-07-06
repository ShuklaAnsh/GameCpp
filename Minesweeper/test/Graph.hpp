#include <vector>
#include <array>

class Graph
{
private:
    
    enum CELL_POS { LEFT, TOP_LEFT, TOP, TOP_RIGHT, RIGHT, BOTTOM_RIGHT, BOTTOM, BOTTOM_LEFT , NUM_POSITIONS};

    struct Node
    {
        bool visited;
        int x, y, value;
        std::array<Node *, CELL_POS::NUM_POSITIONS> neighbours;
    };
    
public:
    Graph(int rows, int cols);
    ~Graph();
    void printGraph();
    void search(int x_i, int y_i, int val);
    void visitNeighbours(Node &node, int val);
    void addNeighbours(Node& node, Node& left, Node& top_left, Node& top, Node& top_right, Node& right, Node& bottom_right, Node& bottom, Node& bottom_left);

private:
    std::vector<std::vector<Node> > m_grid;
    int ROWS;
    int COLS;
    Node m_border_node;
    std::string m_pos_names[CELL_POS::NUM_POSITIONS];
};