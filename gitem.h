#ifndef GITEM_H
#define GITEM_H

#include<QGraphicsScene>
#include<QGraphicsObject>
#include<QGraphicsSceneMouseEvent>

class GItem : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit GItem(QObject *parent = nullptr);
    float size=1;
    bool blocked = false;
    int state=-1;
    int index;
    int g=0;
    int h=0;
    int f=0;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    //void advance(){}
signals:
    void clicked_(int index);
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

    void mousePressEvent(QGraphicsSceneMouseEvent *e);

private:




};

#endif // GITEM_H
