#include "boardchess.h"
#include <QtWidgets>
#include "defines.h"
#include "game.h"

BoardChessBase::BoardChessBase(QGraphicsItem*parent)
    :QGraphicsItem(parent)
{
}

BoardChessBase::~BoardChessBase()
{
}

const QMap<QPair<char, char>, QPointF>  BoardChessBase::mapCoordinates =
{   {{'a','1'},QPointF(0,  350)}, {{'a','2'},QPointF(0,  300)}, {{'a','3'},QPointF(0,  250)}, {{'a','4'},QPointF(0,  200)}, {{'a','5'},QPointF(0,  150)}, {{'a','6'},QPointF(0,  100)}, {{'a','7'},QPointF(0,  50)}, {{'a','8'},QPointF(0,  0)},
    {{'b','1'},QPointF(50, 350)}, {{'b','2'},QPointF(50, 300)}, {{'b','3'},QPointF(50, 250)}, {{'b','4'},QPointF(50, 200)}, {{'b','5'},QPointF(50, 150)}, {{'b','6'},QPointF(50, 100)}, {{'b','7'},QPointF(50, 50)}, {{'b','8'},QPointF(50, 0)},
    {{'c','1'},QPointF(100,350)}, {{'c','2'},QPointF(100,300)}, {{'c','3'},QPointF(100,250)}, {{'c','4'},QPointF(100,200)}, {{'c','5'},QPointF(100,150)}, {{'c','6'},QPointF(100,100)}, {{'c','7'},QPointF(100,50)}, {{'c','8'},QPointF(100,0)},
    {{'d','1'},QPointF(150,350)}, {{'d','2'},QPointF(150,300)}, {{'d','3'},QPointF(150,250)}, {{'d','4'},QPointF(150,200)}, {{'d','5'},QPointF(150,150)}, {{'d','6'},QPointF(150,100)}, {{'d','7'},QPointF(150,50)}, {{'d','8'},QPointF(150,0)},
    {{'e','1'},QPointF(200,350)}, {{'e','2'},QPointF(200,300)}, {{'e','3'},QPointF(200,250)}, {{'e','4'},QPointF(200,200)}, {{'e','5'},QPointF(200,150)}, {{'e','6'},QPointF(200,100)}, {{'e','7'},QPointF(200,50)}, {{'e','8'},QPointF(200,0)},
    {{'f','1'},QPointF(250,350)}, {{'f','2'},QPointF(250,300)}, {{'f','3'},QPointF(250,250)}, {{'f','4'},QPointF(250,200)}, {{'f','5'},QPointF(250,150)}, {{'f','6'},QPointF(250,100)}, {{'f','7'},QPointF(250,50)}, {{'f','8'},QPointF(250,0)},
    {{'g','1'},QPointF(300,350)}, {{'g','2'},QPointF(300,300)}, {{'g','3'},QPointF(300,250)}, {{'g','4'},QPointF(300,200)}, {{'g','5'},QPointF(300,150)}, {{'g','6'},QPointF(300,100)}, {{'g','7'},QPointF(300,50)}, {{'g','8'},QPointF(300,0)},
    {{'h','1'},QPointF(350,350)}, {{'h','2'},QPointF(350,300)}, {{'h','3'},QPointF(350,250)}, {{'h','4'},QPointF(350,200)}, {{'h','5'},QPointF(350,150)}, {{'h','6'},QPointF(350,100)}, {{'h','7'},QPointF(350,50)}, {{'h','8'},QPointF(350,0)}
};

//BoardChessBase

//BoardChess
BoardChess::BoardChess(QGraphicsItem *parent)
    :BoardChessBase(parent)
{
    setFlag(ItemHasNoContents);
    chessCells.resize(8);

    BoardChessFrame*chessFrame=new BoardChessFrame(this);
    int i = 8;
    for(i; i>0; i--){
        int j = 8;
        for(j; j>0; j--){
            BoardChessCell*chessCellItem=new BoardChessCell(qMakePair(SIMBOL_48+i, SIMBOL_96+j),chessFrame);
            chessCells[i-1].push_back(chessCellItem);
            chessCells[i-1].at(8-j)->setPos(ALIGNMENT_LEFT_CELL_CHESS+SIZE_CELL*j,
                                            ALIGNMENT_TOP_CELL_CHESS-SIZE_CELL*i);
        }
    }
    chessFrame->setPos(0,0);
}

QRectF BoardChess::boundingRect() const{
    return QRectF();
}

void BoardChess::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget){
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//BoardChess

//BoardChessCell
BoardChessCell::BoardChessCell(const QPair<char, char> id, QGraphicsItem*parent)
    :BoardChessBase(parent), idCoordinate(0,0), pressed(false){
    //Эта функция добавляет элемент типа BoardChessCell* в вектор
    //BoardChess::chessCell
    //и устанавливает координат этого элемента. Координат клетки обозначается как id.
    //id.first - это значение строки, которое может обозначаться от 1-8;
    //id.second - это значение столбика, которое может обозначаться от a-h
    setAcceptDrops(true);
    try {
        if((id.first<'1'||id.first>'8')||
          (id.second<'a'||id.second>'h')){
            throw 10;
        }
    } catch (...) {
        QMessageBox msgBox;
        msgBox.setText("Неверный idCoordinate");
        msgBox.exec();
    }
    idCoordinate=id;
}

QPair<char, char> BoardChessCell::getId(){
    return idCoordinate;
}

void BoardChessCell::dragEnterEvent(QGraphicsSceneDragDropEvent *event){
    Q_UNUSED(event);
}

void BoardChessCell::dragLeaveEvent(QGraphicsSceneDragDropEvent *event){
    QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);
    event->accept();
}

void BoardChessCell::dragMoveEvent(QGraphicsSceneDragDropEvent *event){
    QRect updateRect = highlightedRect.united(targetSquare());

    if (pressed) {
        highlightedRect = targetSquare();
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        highlightedRect = QRect();
        event->ignore();
    }
    update(updateRect);
}

void BoardChessCell::dropEvent(QGraphicsSceneDragDropEvent *event) {
    QList<QGraphicsItem*> items = collidingItems();
    QPair<char, char> key(idCoordinate.second, idCoordinate.first);
    char coordinateMoves[3] = {idCoordinate.second, idCoordinate.first};
    QByteArray &byte = Game::getInstance()->byte;
    byte.append(coordinateMoves);

    //это условие проверяет есть жертва или нет
    if(!items.isEmpty()){
        //в данном случае есть жертва
        FigureBase *figure = dynamic_cast<FigureBase *>(items.at(0));
        byte.append((char)figure->getColor()+'0');
        byte.append('\n');

        QVector<FigureBase*>*vecDelFig;
        figure->getColor()?
                (vecDelFig=&Game::getInstance()->vecWhite):
                (vecDelFig=&Game::getInstance()->vecBlack);

        int i = vecDelFig->indexOf(figure);
        vecDelFig->remove(i);
        delete figure;

    }
    else{
        byte.append('\n');
    }

    QPointF position = BoardChessBase::mapCoordinates.find(key).value();
    FigureBase*figure = Game::getInstance()->getFigureMoved();
    figure->setPos(position);
    figure->firstStep=true;
    QVector<FigureBase*>vecFigures;
    figure->getColor()?
                (vecFigures=Game::getInstance()->vecBlack):
                (vecFigures=Game::getInstance()->vecWhite);

    for(auto&i:listFig)
        i->possibleSteps();

    auto cellOldStep = Game::getInstance()->
            getMapCell().find(qMakePair(figure->getOldStep().second,
                                        figure->getOldStep().first));

    for(auto&i:(cellOldStep.value()->listFig)){
        i->possibleSteps();
    }

    Game::getInstance()->setQueue();

    Game::getInstance()->serial.write(byte);

    Game::getInstance()->reDrawing();
    highlightedRect = QRect();
    update();
}

QRectF BoardChessCell::boundingRect() const{
    return QRectF(5, 5, 40, 40);
}

void BoardChessCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    int row = idCoordinate.first-'1';
    int col = idCoordinate.second-'a';
    int current = row+col;
    if(!(current%2))
        pixmap.load(":/img/main/BlackCell.png");
    else
        pixmap.load(":/img/main/WhiteCell.png");
    painter->drawPixmap(QPointF(0,0), pixmap);

    if(pressed){
        painter->setBrush(QBrush(Qt::red));
        painter->setOpacity(0.5);
        painter->drawRect(QRect(5, 5, 40, 40));
    }
    if(highlightedRect.isValid()){
        painter->setBrush(QBrush(Qt::blue));
        painter->setOpacity(0.5);
        painter->setPen(Qt::NoPen);
        painter->drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }
}

const QRect BoardChessCell::targetSquare() const
{
    return QRect(0, 0, cellSize(), cellSize());
}

int BoardChessCell::cellSize() const
{
    return SIZE_CELL;
}

//BoardChessCell

//BoardChessFrame
BoardChessFrame::BoardChessFrame(QGraphicsItem *parent)
    :BoardChessBase(parent)
{
}

QRectF BoardChessFrame::boundingRect() const{
    return QRectF();
}

void BoardChessFrame::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    pixmap.load(":/img/main/FrameBoard.png");
    painter->drawPixmap(QPointF(0, 0), pixmap);
}

//BoardChessFrame
