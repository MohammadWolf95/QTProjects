#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "boardchess.h"
#include "figures.h"
#include "defines.h"
#include <QtSerialPort/QSerialPort>
#include <qmutex.h>
#include "informationgame.h"
#include "qdebug.h"

class Game:public QObject, public QGraphicsItem
{
    Q_OBJECT
  private:
    static Game * p_instance;
    QMap<QPair<char, char>,BoardChessCell*> mapCell;
    QVector<BoardChessCell*> vecCell;

    Figures*figuresWhite;
    Figures*figuresBlack;
    // Конструкторы и оператор присваивания недоступны клиентам
    Game(QGraphicsItem *parent=0);
    Game( const Game& );
    Game& operator=( Game& );
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) Q_DECL_OVERRIDE;
    FigureBase *figureMoved;
    bool queue;

  public:
    QByteArray byte;
    QSerialPort serial;
    FigureBase* savedFig=NULL;              //эта фигура, которая сделала
                                            //предыдущий ход
    InformationGame *infoBox;

    QVector<FigureBase*> vecWhite;
    QVector<FigureBase*> vecBlack;

    QMap<QPair<char, char>, BoardChessCell*>mapCellsShah;   //Эти ходы заняты, т.е. король на
                                            //на них стоять не может

    static Game * getInstance();
    QMap<QPair<char, char>,BoardChessCell*> &getMapCell(){
        return mapCell;
    }
    void reDrawing(){
        /*
         * Эта функция предназначена для перерисовки
         * объектов типа BoardChessCell*,
         * в которых член pressed равен true
        */
        if(!vecCell.size())
            return;
        for(auto v:vecCell){
            v->pressed = false;
            v->update();
        }
        vecCell.clear();
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
        vecCell=vec;
    }

    void setFigureMoved(FigureBase *figureMoved){
        this->figureMoved = figureMoved;
    }

    FigureBase *getFigureMoved(){
        return figureMoved;
    }

    void setQueue(){
        //Game::getInstance()->mapCellsShah.clear();
        QVector<FigureBase*> vec;
        //FigureBase * king;

        if(figureMoved->getName()!="King")
            figureMoved->possibleSteps();

        if(queue){
            figuresWhite->setEnabled(false);
            figuresBlack->setEnabled(true);
            vec = vecBlack;
            queue=false;
        }
        else{
            figuresWhite->setEnabled(true);
            figuresBlack->setEnabled(false);
            vec = vecWhite;
            queue=true;
        }
        for(auto&i:vec){
            if(i!=figureMoved){
                i->possibleSteps();
                qDebug()<<i<<getFigureMoved()<<endl;
            }
            else{
                qDebug()<<i<<getFigureMoved()<<endl;
            }
            //qDebug()<<i<<Game::getFigureMoved()<<endl;
        }
            //else
                //king = i;
        //king->possibleSteps();
    }

    bool getQueue(){
        return queue;
    }
};

#endif // GAME_H
