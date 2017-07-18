#ifndef FIGURES_H
#define FIGURES_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsObject>
#include "boardchess.h"

QT_FORWARD_DECLARE_CLASS(QPixmap)

class FigureBase: public QGraphicsObject{
public:
    FigureBase(QGraphicsItem*parent=0);
    virtual ~FigureBase();
    bool getColor(){
        return color;
    }

    bool firstStep;

    virtual void possibleSteps();   //функция для рассчета
                                    //возможных ходов для фигур

protected:
    QPixmap pixmap;
    bool color;
    QString name;
    QVector<BoardChessCell*> vector;

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void writePosInByte(const char&x, const char&y);
    bool calcStepsForKQERH(BoardChessCell*cell, QVector<BoardChessCell*>&vec);
    void reDrawing(){
        /*
         * Эта функция предназначена для перерисовки
         * объектов типа BoardChessCell*,
         * в которых член pressed равен true
        */
        if(!vector.size())
            return;
        for(auto v:vector){
            v->pressed = false;
            v->update();
        }
        vector.clear();
    }
    void setVector(QVector<BoardChessCell*> vec){
        /*
         * Эта функция сохраняет элементы
         * типа BoardChessCell*,
         * и делает член pressed равным true, затем.
         * После обновления у элементов член pressed
         * становится равным false. После всех операций vector очищается
        */
        for(auto &i:vec){
            i->pressed = true;
            i->update();
        }
        vector=vec;
    }

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
    void possibleSteps()Q_DECL_OVERRIDE;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

class King : public FigureBase
{
public:
    King(const bool &color, QGraphicsItem *parent=0);
    virtual ~King();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;
    void possibleSteps()Q_DECL_OVERRIDE;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

class Queen : public FigureBase
{
public:
    Queen(const bool &color, QGraphicsItem *parent=0);
    virtual ~Queen();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;
    void possibleSteps()Q_DECL_OVERRIDE;
private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

class Elephant : public FigureBase
{
public:
    Elephant(const bool &color, QGraphicsItem *parent=0);
    virtual ~Elephant();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;
    void possibleSteps()Q_DECL_OVERRIDE;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

class Horse : public FigureBase
{
public:
    Horse(const bool &color, QGraphicsItem *parent=0);
    virtual ~Horse();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;
    void possibleSteps()Q_DECL_OVERRIDE;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

class Rook : public FigureBase
{
public:
    Rook(const bool &color, QGraphicsItem *parent=0);
    virtual ~Rook();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;
    void possibleSteps()Q_DECL_OVERRIDE;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
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
    static QString chessMimeType() { return QStringLiteral("figures/x-chess"); }
    QVector<FigureBase*> getVectorFig(){
        return vecFig;
    }

private:
    QVector<FigureBase*> vecFig;
};

#endif // FIGURES_H
