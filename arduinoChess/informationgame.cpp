#include "informationgame.h"
#include <QtWidgets>

InformationGame::InformationGame(QGraphicsItem *parent)
    :QGraphicsItem(parent), pixmap()
{

}

void InformationGame::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    pixmap.load(":/img/main/text_box.png");
    painter->drawPixmap(QPointF(0,0),pixmap);
}

QRectF InformationGame::boundingRect() const{
    return QRectF();
}
