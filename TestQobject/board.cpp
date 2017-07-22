#include "board.h"

Board::Board()
    :m_value(0)
{

}

QRectF Board::boundingRect()const{
    return QRectF();
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget){

}

void Board::setValue(int value)
{
    if (value != m_value) {
        m_value = value;
        emit valueChanged(value);
    }
}

BoardTwo::BoardTwo(){

}
