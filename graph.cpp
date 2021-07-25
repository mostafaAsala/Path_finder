#include "graph.h"
#include <QtMath>
#include <limits>
#include<QDebug>
Graph::Graph(QVector<Node*> nodes)
{
    this->Nodes = nodes;
}

Node::Node(int x,int y,int id)
{
    this->id= id;
    this->x = x;
    this->y = y;
    g=0;
    h=0;
    f=0;
    this->came_from = nullptr;
}

void Node::set_g(int g)
{
    this->g = g;
}

float Node::get_g()
{
    return g;
}

float Node::get_h(QPair<int,int> p)
{
    h = qSqrt(qPow((p.first-this->x),2) + qPow((p.second-this->y),2))*10;
    return h;
}

float Node::clac_f()
{
    f = h+g;
    return f;
}

Path_finder::Path_finder()
{

}

QVector<Node*>  Path_finder::A_star(Node *start, Node *goal)
{
    this->start_Node = start;
    this->goal_Node = goal;
    this->frontier.append(start);
    Node* current = start;
    while (!frontier.empty()) {
        //qDebug()<<current->id;
        current = choose_node(current);
        if(current == goal){
            break;
        }
        auto neighbours = current->neighbours;
        qDebug()<<"count "<<neighbours.count();
        for(int i = 0 ;i<neighbours.count();i++){

            auto next = neighbours[i].first;
            float new_cost = current->get_g() + neighbours[i].second;
            if(new_cost < next->get_g() || !next->isVisited){
                next->set_g(new_cost);
                next->get_h(goal->get_coords());
                next->clac_f();
                next->came_from = current;
                frontier.append(next);
                next->isVisited = true;
            }
        }
    }


    QVector<Node*> list;
    current = goal;

    while(current != nullptr && current != start ){
        list.append(current);
        current->inpath=true;
        current=current->came_from;

    }
    qDebug()<<"found goall";
    return list;

}

void Path_finder::set_astar_step(Node *start, Node *goal, QVector<Node *> nodes)
{
    this->start_Node = start;
    this->goal_Node = goal;
    this->graph = nodes;
    this->frontier.append(start);
    current = start;
}

Node* Path_finder::Q_star_step()
{
    if (frontier.empty()){
        return current;
    }
    if (stage_step == neighbours.count()){
        neighbours = get_neighbours();
        qDebug()<<frontier.count()<<"   "<<neighbours.count();
        stage_step = 0;
    }
    if(found_target ){


        return current;
    }
    qDebug()<<"step n "<<stage_step;


    auto next = neighbours[stage_step].first;
    if (next == current->came_from){
        stage_step++;
        return current;
    }
    //qDebug()<<"after n";
    float new_cost = current->get_g() + neighbours[stage_step].second;
    if(new_cost < next->get_g() || !next->isVisited){
        next->set_g(new_cost);
        next->get_h(this->goal_Node->get_coords());
        next->clac_f();
        next->came_from = current;
        if(!frontier.contains(next))
            frontier.append(next);
        next->isVisited = true;
    }
    stage_step++;
    return next;
}
QVector<QPair<Node *, int> > Path_finder::get_neighbours()
{
    current = choose_node(current);
    if(current == goal_Node){
        qDebug()<<"current = goal";
        found_target = true;

    }else {
        found_target =false;
    }
    auto neighbours = current->neighbours;
    return neighbours;

}
Node * Path_finder::choose_node(Node * current)
{
    int index=-1;
    float min = std::numeric_limits<float>::max();
    for (int i=0;i<frontier.count();i++){
        if(frontier[i]->get_f() < min){
            current = frontier[i];
            min = frontier[i]->get_f();
            index = i;
        }
    }
    frontier.remove(index);
    return current;
}



bool Path_finder::no_next_path_avilable()
{
    qDebug()<<"frontier size: "<<frontier.count();
    return !frontier.empty();
}
