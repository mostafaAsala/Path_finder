#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QMouseEvent>
#include<QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);


    QBrush b(Qt::white);
    QPen pen(Qt::black);
    pen.setWidth(4);

    GItem *rect;
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    for (int i=0;i<height;i++){
        for (int j=0;j<width;j++){

            rect = new GItem();

            connect(rect , SIGNAL(clicked_(int)),this,SLOT(ItemClicked(int)));
            scene->addItem(rect);
            rect->index = j+i*width;
            rect->setPos(j*(size+padding),i*(size+padding));
            map.append(rect);
        }
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent *event) {
/*
    //qDebug()<<event->scenePos().y()<<"  "<< event->scenePos().y();

    auto pos = ui->graphicsView->mapToScene(event->pos());
    auto items = scene->items();
    //auto item = items.indexOf(scene->itemAt(pos , ui->graphicsView->transform()));
    auto x =qgraphicsitem_cast<GItem*>(ui->graphicsView->itemAt(event->pos()));

    auto item2 = items.indexOf(x);

    qDebug()<< " "<<x->index;

*/

}


void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"released";
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_S){
        ui->setStart->setChecked(true);
    }else if (event->key() == Qt::Key_E){
        ui->setEnd->setChecked(true);
    }else if (event->key() == Qt::Key_B){
        ui->setOBstacle->setChecked(true);
    }
}

void MainWindow::ItemClicked(int index)
{
    //qDebug()<<index;
    if(ui->setOBstacle->isChecked()){
        map[index]->state =map[index]->state==2? -1:2 ;
        map[index]->blocked = !map[index]->blocked;

    }
    else if(ui->setStart->isChecked()){

        if(start_point != index){
            if (start_point!=-1){
            map[start_point]->state = -1;
            map[start_point]->update();
            }
            map[index]->state = 0;
            start_point = index;

        }
    }else if(ui->setEnd->isChecked()){
        if(end_point != index){
            if (end_point!=-1){
            map[end_point]->state = -1;
            map[start_point]->update();
            }
            map[index]->state = 1;
            end_point = index;

        }
    }
    if(ui->checkBox->isChecked()){
        on_pushButton_clicked();
    }

}


void MainWindow::on_pushButton_clicked()
{
    find_path();
}

void MainWindow::find_path(){

    QVector<Node*> vect;


    for (int i=0;i<map.count();i++ ) {
        Node *n = new Node(i%width,i/width,i);

        vect.append(n);
    }
    qDebug()<<"here1";
    for (int item=0;item<map.count();item++ ) {
        //qDebug()<<"item "<<item;
        int col = item%width;int row = item/width;
        if(map[item]->state!=2)
            for (int i=row-1;i<=row+1 ;i++ ) {
                for (int j=col-1;j<=col+1 ;j++ ) {
                    if(i>=0 && j>=0 && i<height && j<width){
                        int index_ = i*width+j;
                        if (map[index_]->state!=2 ){
                            int cost=10;
                            if (i!=row && j!=col) cost= 14;
                            if (index_!=item){
                                //qDebug()<<"neighbour "<<index_;
                                vect[item]->neighbours.append(QPair<Node*,int>(vect[index_],cost));

                            }
                        }
                    }
                }
            }
    }
    qDebug()<<"here2";
    Path_finder p;
    p.A_star(vect[start_point],vect[end_point]);
    for (int i=0;i<vect.count();i++ ) {
        if (i==start_point){
             map[i]->state = 0;
        }else if (i==end_point){
             map[i]->state = 1;
        }else if(vect[i]->inpath){
            map[i]->state = 3;

        }else if (vect[i]->isVisited){
            map[i]->state = 4;
        }else if (map[i]->state!=2 ) {
            map[i]->state = -1;
        }
        map[i]->h = vect[i]->get_h();
        map[i]->g = vect[i]->get_g();
        map[i]->f = vect[i]->get_f();
        map[i]->update();

    }
    vect.erase(vect.begin(),vect.end());

}

void MainWindow::step_find_path()
{




}

void MainWindow::set_new_grid()
{   //scene = new QGraphicsScene(this);
    //ui->graphicsView->setScene(scene);

    while(!scene->items().empty()) {
        auto item = scene->items()[0];

        scene->removeItem(item);
        map.remove(0);
        delete item;
      }
    QBrush b(Qt::white);
    QPen pen(Qt::black);
    pen.setWidth(4);

    GItem *rect;
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    for (int i=0;i<height;i++){
        for (int j=0;j<width;j++){

            rect = new GItem();

            connect(rect , SIGNAL(clicked_(int)),this,SLOT(ItemClicked(int)));
            scene->addItem(rect);
            rect->index = j+i*width;
            rect->setPos(j*(size+padding),i*(size+padding));
            map.append(rect);
        }
    }



}
void MainWindow::on_pushButton_2_clicked()
{
    QVector<Node*> vect;


    for (int i=0;i<map.count();i++ ) {
        Node *n = new Node(i%width,i/width,i);

        vect.append(n);
    }
    //qDebug()<<"here1";
    for (int item=0;item<map.count();item++ ) {
        //qDebug()<<"item "<<item;
        int col = item%width;int row = item/width;
        if(map[item]->state!=2)
            for (int i=row-1;i<=row+1 ;i++ ) {
                for (int j=col-1;j<=col+1 ;j++ ) {
                    if(i>=0 && j>=0 && i<height && j<width){
                        int index_ = i*width+j;
                        if (map[index_]->state!=2 ){
                            int cost=10;
                            if (i!=row && j!=col) cost= 14;
                            if (index_!=item){
                                //qDebug()<<"neighbour "<<index_;
                                vect[item]->neighbours.append(QPair<Node*,int>(vect[index_],cost));

                            }
                        }
                    }
                }
            }
    }
    //qDebug()<<"here2";

    p.set_astar_step(vect[start_point],vect[end_point],vect);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(find_next_path()));
    timer->start(timer_interval);
}

void MainWindow::find_next_path()
{
    qDebug()<<"here1";
    auto n = p.Q_star_step();
    qDebug()<<"here2";
    qDebug()<<n->id;
    if(prev_id!=-1){
        map[prev_id]->state = 4;
        map[prev_id]->update();
    }
    map[n->id]->h = n->get_h();
    map[n->id]->g = n->get_g();
    map[n->id]->f = n->get_f();
    map[n->id]->state = 5;
    map[n->id]->update();

    prev_id = n->id;
    if(p.found_target || !p.no_next_path_avilable()){
        Node *current = p.graph[end_point];
        while(current != nullptr && current != p.graph[start_point] ){
            current->inpath=true;
            current=current->came_from;
        }
        qDebug()<<p.found_target <<"  "<<p.no_next_path_avilable();
        for (int i=0;i<p.graph.count();i++ ) {
            if (i==start_point){
                 map[i]->state = 0;
            }else if (i==end_point){
                 map[i]->state = 1;
            }else if(p.graph[i]->inpath){
                map[i]->state = 3;

            }else if (p.graph[i]->isVisited){
                map[i]->state = 4;
            }else if (map[i]->state!=2 ) {
                map[i]->state = -1;
            }
            map[i]->h = p.graph[i]->get_h();
            map[i]->g = p.graph[i]->get_g();
            map[i]->f = p.graph[i]->get_f();
            map[i]->update();

        }
        timer->stop();
        p.graph.erase(p.graph.begin(),p.graph.end());

        qDebug()<<n->id<<"timer stoped";
    }

}


void MainWindow::on_actionss_triggered()
{

    for (int i=0;i<map.count() ;i++ ) {
        map[i]->blocked =true;
        map[i]->state = 2;
        map[i]->update();
    }

    QVector<QVector<int>>frontier;
    int rand = random()%map.count();
    rand = 11;
    qDebug()<<rand;
    auto state = QVector<int>(rand,rand);
    frontier.append(state);
    QVector<int> cell = QVector<int>(rand,rand);

    while(!frontier.empty()){
        int index = random()%frontier.count();

        cell = frontier[index];
        //qDebug()<<index<<": "<<cell[0];
        frontier.remove(index);
        int x1 = cell[1]%width; int y1 = cell[1]/width;
        if(map[cell[1]]->blocked ==true){

            map[cell[0]]->blocked = false;
            map[cell[0]]->state = -1;
            map[cell[0]]->update();

            map[cell[1]]->blocked = false;
            map[cell[1]]->state = -1;
            map[cell[1]]->update();
            if(x1>=2 ){
                if(map[cell[1]-2]->blocked==true){
                    qDebug()<<"cell: "<<cell[0]<<" "<<cell[1];

                    QVector<int> x;
                    x.append(cell[1]-1);x.append(cell[1]-2);
                    frontier.append(x);
                }
            }
            if(y1>=2 ){
                if(map[cell[1]-2*width]->blocked==true){
                    qDebug()<<"cell: "<<cell[0]<<" "<<cell[1];

                    QVector<int> x;
                    x.append(cell[1]-width);x.append(cell[1]-2*width);
                    frontier.append(x);
                }
            }
            if(x1<width-3 ){
                if(map[cell[1]+2]->blocked==true){
                    qDebug()<<"cell: "<<cell[0]<<" "<<cell[1];

                    QVector<int> x;
                    x.append(cell[1]+1);x.append(cell[1]+2);
                    frontier.append(x);
                }
            }
            if(y1< height-3){
                if(map[cell[1]+2*width]->blocked==true){
                    qDebug()<<"cell: "<<cell[0]<<" "<<cell[1];

                    QVector<int> x;
                    x.append(cell[1]+width);x.append(cell[1]+2*width);
                    frontier.append(x);
                }
            }
        }
    }



}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    for (int i=0;i<height ;i++ ) {
        for(int j=0;j<width;j++){
            float x = (value+10)*1.0/100;
            map[i*width+j]->size = x;
            map[i*width+j]->setPos(j*(map[i]->size+padding*x*11),i*(map[i]->size+padding*x*11));
            map[i*width+j]->update();
        }

    }
}


void MainWindow::on_pushButton_3_clicked()
{
    int width = ui->spinBox->value();

    int height = ui->spinBox_2->value();
    this->width = width;
    this->height = height;
    set_new_grid();
}

