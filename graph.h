#ifndef GRAPH_H
#define GRAPH_H
#include<QtCore>
#include<QtGui>

class Node{
public:
    Node(int x, int y,int id);
    void set_g(int g);
    float get_g();
    float get_h(QPair<int,int>);
    float get_h(){return h;}
    float clac_f();
    float get_f(){return f;}
    QVector<QPair<Node*,int>> neighbours; //node + cost to it
    int get_index(){return id;}
    QPair<int,int> get_coords(){return QPair<int,int>(x,y);}
    Node *came_from;
    int id;
    bool isVisited = false;
    bool inpath = false;
private :

    int x;
    int y;
    float f;
    float h;
    float g;
};

class Graph
{
public:
    Graph(QVector<Node*>);
    QVector<Node*> Nodes;

};

class Path_finder{
public:
    Path_finder();
    QVector<Node*>  A_star(Node *start , Node *goal);
    void set_astar_step(Node *start , Node *goal , QVector<Node*> nodes);
    Node* Q_star_step();
    Node * choose_node(Node*);
    QVector<QPair<Node*,int>> get_neighbours();
    bool no_next_path_avilable();
    bool found_target=false;
    QVector<Node*> graph;
private:
    Node *start_Node;
    Node *goal_Node;
    Node *current;

    QVector<Node*>frontier;
    int stage_step=0;
    int n_count;
    QVector<QPair<Node*,int>> neighbours;


};


#endif // GRAPH_H
