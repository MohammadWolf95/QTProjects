#include "game.h"
#include <QtWidgets>

Game * Game::p_instance = 0;

Game::Game(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    BoardChess *board = new BoardChess(this);
    board->setPos(200,100);
    auto chessCells = board->getChessCells();
    for(auto vec1:chessCells)
        for(auto vec2:vec1)
            mapCell.insert(vec2->idCoordinate, vec2);

    Figures*figuresWhite = new Figures(true, board);
    figuresWhite->setPos(ALIGNMENT_TOP_AND_LEFT_FIGURE,ALIGNMENT_TOP_AND_LEFT_FIGURE);

    Figures*figuresBlack = new Figures(false, board);
    figuresBlack->setPos(ALIGNMENT_TOP_AND_LEFT_FIGURE,ALIGNMENT_TOP_AND_LEFT_FIGURE);
}

QRectF Game::boundingRect() const{
    return QRectF();
}

void Game::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option,
           QWidget *widget){
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
