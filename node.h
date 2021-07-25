#ifndef NODE_H
#define NODE_H

#include <QObject>
#include<QGraphicsObject>
class Node : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Node(QObject *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

signals:
    void clicked_(int index);
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    int xxx;
    int branch_b;

};

#endif // NODE_H
