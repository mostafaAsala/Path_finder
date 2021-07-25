#include "gitem.h"
#include<QPainter>
GItem::GItem(QObject *parent)
    : QGraphicsObject()
{
    state=-1;
}

#include<QDebug>


QRectF GItem::boundingRect() const
{
    return QRectF(0,0,50*size,50*size);
}

void GItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   QRectF rec = boundingRect();
   QBrush brush(Qt::white);
   if (state==0){
       qDebug()<<state;
       brush.setColor(Qt::red); //start
   }else if(state == 1){
       //qDebug()<<state;
        brush.setColor(Qt::green); //end
   }else if(state == 2){
       //qDebug()<<state;
        brush.setColor(Qt::black); //blocked
   }else if(state == 3){
       //qDebug()<<state;
        brush.setColor(Qt::blue); //explored
   }else if(state == 4){
       //qDebug()<<state;
        brush.setColor(Qt::lightGray); //left
   }else if(state == 5){
       //qDebug()<<state;
        brush.setColor(Qt::gray); //left
   }
   QFont font;
   font.setPixelSize(10*size);
   painter->fillRect(rec,brush);
   painter->drawRect(rec);
   painter->setFont(font);
   painter->drawText(5*size,15*size,QString::number(index));
   painter->drawText(5*size,45*size,QString::number(f));
   painter->drawText(35*size,45*size,QString::number(g));
   painter->drawText(35*size,15*size,QString::number(h));
}

void GItem::mousePressEvent(QGraphicsSceneMouseEvent *e)
{



    emit clicked_(index);
    update();
    QGraphicsItem::mousePressEvent(e);
    //qDebug()<<this->index;

}



void GItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    qDebug()<<"released";
    state = false;

    update();
    QGraphicsItem::mouseReleaseEvent(e);
}
