#ifndef NODE_H
#define NODE_H

#include <QObject>

class Node : public QObject
{
    Q_OBJECT
public:
    explicit Node(QObject *parent = nullptr);
    int x;
signals:

};

#endif // NODE_H
