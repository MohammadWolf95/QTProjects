#ifndef BOARDCHESS_H
#define BOARDCHESS_H

#include <QGraphicsItem>
#include <QPair>

class BoardChessBase;
class BoardChess;
class BoardChessCell;
class BoardChessFrame;

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
QT_END_NAMESPACE

class BoardChessBase : public QGraphicsItem{
public:
    BoardChessBase(QGraphicsItem*parent=0);
    virtual ~BoardChessBase();

    static const QMap<QPair<char, char>, QPointF> mapCoordinates;
protected:
    QPixmap pixmap;
};

class BoardChess : public BoardChessBase
{
public:
    BoardChess(QGraphicsItem*parent=0);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;
    QVector<QVector<BoardChessCell*>> getChessCells(){
        return chessCells;
    }

private:
    QVector<QVector<BoardChessCell*>> chessCells;
};

class BoardChessCell: public BoardChessBase
{
public:
    BoardChessCell(const QPair<char, char> id, QGraphicsItem*parent=0);
    QPair<char, char> getId();
    QPair<char, char> idCoordinate;

    bool pressed;
private:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE; 
    const QRect targetSquare() const;
    int cellSize() const;

    QRect highlightedRect;
};

class BoardChessFrame: public BoardChessBase
{
public:
    BoardChessFrame(QGraphicsItem *parent = 0);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;
};

#endif // BOARDCHESS_H
