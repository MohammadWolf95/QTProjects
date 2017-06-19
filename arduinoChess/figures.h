#ifndef FIGURES_H
#define FIGURES_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsObject>

QT_FORWARD_DECLARE_CLASS(QPixmap)

class FigureBase: public QGraphicsObject{
public:
    FigureBase(QGraphicsItem*parent=0);
    virtual ~FigureBase();

protected:
    QPixmap pixmap;
    bool color;
    QString name;

    QRectF boundingRect() const Q_DECL_OVERRIDE;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

class Pawn : public FigureBase
{
public:
    Pawn(const bool &color, QGraphicsItem *parent=0);
    virtual ~Pawn();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;

    bool firstStep;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

class King : public FigureBase
{
public:
    King(const bool &color, QGraphicsItem *parent=0);
    virtual ~King();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;
};

class Queen : public FigureBase
{
public:
    Queen(const bool &color, QGraphicsItem *parent=0);
    virtual ~Queen();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;
};

class Elephant : public FigureBase
{
public:
    Elephant(const bool &color, QGraphicsItem *parent=0);
    virtual ~Elephant();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;
};

class Horse : public FigureBase
{
public:
    Horse(const bool &color, QGraphicsItem *parent=0);
    virtual ~Horse();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;
};

class Rook : public FigureBase
{
public:
    Rook(const bool &color, QGraphicsItem *parent=0);
    virtual ~Rook();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;

};

class Figures: public FigureBase
{
public:
    Figures(const bool &color, QGraphicsItem *parent=0);
    virtual ~Figures();
    bool getColor();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;

    //QVector<FigureBase*> getVectorFig();
private:
    //QVector<FigureBase*> vecFig;
};

#endif // FIGURES_H
