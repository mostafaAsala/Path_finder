#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsScene>
#include<QGraphicsRectItem>
#include<QtCore>
#include<QtGui>
#include<QGraphicsSceneMouseEvent>
#include"gitem.h"
#include"graph.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void ItemClicked(int index);
private slots:
    void on_pushButton_clicked();
    void mousePressEvent(QMouseEvent *event);//QGraphicsSceneMouseEvent
    void mouseReleaseEvent(QMouseEvent *event);//QGraphicsSceneMouseEvent
    void keyPressEvent(QKeyEvent *event);
    void find_next_path();
    void on_pushButton_2_clicked();

    void on_actionss_triggered();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    int width = 30;
    int height = 30;
    int size = 50;
    int padding = 5;
    int start_point=-1;
    int end_point = -1;
    QGraphicsScene *scene;
    QVector<GItem*> map;
    void find_path();
    void step_find_path();
    void set_new_grid();
    QTimer *timer;
    Path_finder p;
    int prev_id=-1;
    int timer_interval = 100;
};
#endif // MAINWINDOW_H
