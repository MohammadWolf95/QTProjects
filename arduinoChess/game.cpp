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
        for(auto vec2:vec1){
            mapCell.insert(vec2->idCoordinate, vec2);
        }

    figuresWhite = new Figures(true, board);
    figuresWhite->setPos(ALIGNMENT_TOP_AND_LEFT_FIGURE,ALIGNMENT_TOP_AND_LEFT_FIGURE);
    vecWhite = figuresWhite->getVectorFig();

    figuresBlack = new Figures(false, board);
    figuresBlack->setPos(ALIGNMENT_TOP_AND_LEFT_FIGURE,ALIGNMENT_TOP_AND_LEFT_FIGURE);
    vecBlack = figuresBlack->getVectorFig();

    figuresBlack->setEnabled(true);
    figuresBlack->setEnabled(false);
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

Game * Game::getInstance(){
    if(!Game::p_instance){
        Game::p_instance = new Game();
        Game::p_instance->queue=true;
        QSerialPort &serialPort = Game::p_instance->serial;
        serialPort.setPortName("COM5");
        serialPort.setBaudRate(QSerialPort::Baud9600);
        serialPort.setDataBits(QSerialPort::Data8);
        serialPort.setParity(QSerialPort::NoParity);
        serialPort.setStopBits(QSerialPort::OneStop);
        serialPort.setFlowControl(QSerialPort::NoFlowControl);
        serialPort.open(QIODevice::ReadWrite);

    }
    return Game::p_instance;
}
