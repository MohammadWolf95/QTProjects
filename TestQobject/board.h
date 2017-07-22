#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsItem>


class Board:public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Board();
    int value() const { return m_value; }
public slots:
    void setValue(int value);
signals:
    void valueChanged(int newValue);
private:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;

    int m_value;
};

class BoardTwo:public Board
{
    Q_OBJECT
public:
    BoardTwo();
};

#endif // BOARD_H
