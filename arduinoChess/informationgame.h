#ifndef INFORMATIONGAME_H
#define INFORMATIONGAME_H

#include <QObject>
#include <QGraphicsItem>

class InformationGame: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    InformationGame(QGraphicsItem *parent=0);
private:
    QPixmap pixmap;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;
    QRectF boundingRect() const Q_DECL_OVERRIDE;
};

#endif // INFORMATIONGAME_H
