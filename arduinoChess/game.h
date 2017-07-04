#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "boardchess.h"
#include "figures.h"
#include "defines.h"
#include <QtSerialPort/QSerialPort>

class Game:public QGraphicsItem
{
  private:
    static Game * p_instance;
    QMap<QPair<char, char>,BoardChessCell*> mapCell;
    QVector<BoardChessCell*> vector;
    // Конструкторы и оператор присваивания недоступны клиентам
    Game(QGraphicsItem *parent=0);
    Game( const Game& );
    Game& operator=( Game& );
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;
    FigureBase *figureMoved;
  public:
    QByteArray byte;
    QSerialPort serial;

    static Game * getInstance();/* {
        if(!p_instance){
            p_instance = new Game();
            QSerialPort &serialPort = p_instance->serial;
            serialPort.setPortName("COM3");
            serialPort.setBaudRate(QSerialPort::Baud9600);
            serialPort.setDataBits(QSerialPort::Data8);
            serialPort.setParity(QSerialPort::NoParity);
            serialPort.setStopBits(QSerialPort::OneStop);
            serialPort.setFlowControl(QSerialPort::NoFlowControl);
            serialPort.open(QIODevice::ReadWrite);
        }
        return p_instance;
    }*/
    QMap<QPair<char, char>,BoardChessCell*> &getMapCell(){
        return mapCell;
    }
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
         * в которых член pressed
         * равен true
        */
        vector=vec;
    }

    void setFigureMoved(FigureBase *figureMoved){
        this->figureMoved = figureMoved;
    }

    FigureBase *getFigureMoved(){
        return figureMoved;
    }
};

#endif // GAME_H
