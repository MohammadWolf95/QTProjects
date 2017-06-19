#include "figures.h"
#include <QtWidgets>
#include "game.h"

/*Определения для класса Pawn*/
FigureBase::FigureBase(QGraphicsItem *parent)
    :QGraphicsObject(parent), color(false), name(""){
    setCursor(Qt::OpenHandCursor);
}

FigureBase::~FigureBase()
{
}

QRectF FigureBase::boundingRect() const{
    return QRectF(5, 5, 40, 40);
}

void FigureBase::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event);
    setCursor(Qt::ClosedHandCursor);
}

void FigureBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;

    drag->setMimeData(mime);
    drag->setPixmap(pixmap);
    drag->setHotSpot(QPoint(25, 30));
    drag->exec();

    setCursor(Qt::OpenHandCursor);
}

void FigureBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event);
    setCursor(Qt::OpenHandCursor);
    /*auto game = Game::getInstance();
    game->reDrawing();*/
}

/*-----------------------------*/

/*Определения для класса Pawn*/
Pawn::Pawn(const bool &color, QGraphicsItem *parent)
    :FigureBase(parent), firstStep(false){
    this->color=color;
    name = "Pawn";
}

Pawn::~Pawn()
{
}

void Pawn::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option,
           QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    color?pixmap.load(":/img/white_figures/Pawn.png")
        :
          pixmap.load(":/img/black_figures/Pawn.png");

    painter->drawPixmap(QPointF(0,0),pixmap);
}

void Pawn::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setCursor(Qt::ClosedHandCursor);
    auto game = Game::getInstance();
    QPair<char, char> charCoordinate = BoardChessBase::mapCoordinates.key(pos());
    char x = charCoordinate.first;
    char y = charCoordinate.second;
    if(!firstStep){
        auto mapCells = game->getMapCell();
        QVector<BoardChessCell*>vec;
        for(int i=1;i<3;i++){
            color?(++y) :(--y);
            auto cell = mapCells.find(qMakePair(y,x)).value();
            cell->pressed = true;
            cell->update();
            vec.push_back(cell);
        }
        game->setVector(vec);
    }
    else{

    }
}

/*void Pawn::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    setCursor(Qt::OpenHandCursor);
    auto game = Game::getInstance();
    game->reDrawing();
}*/

/*-----------------------------*/

/*Определения для класса King*/
King::King(const bool &color, QGraphicsItem *parent)
    :FigureBase(parent){
    this->color=color;
    name = "King";
}

King::~King()
{
}

void King::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option,
           QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    color?pixmap.load(":/img/white_figures/King.png")
        :
          pixmap.load(":/img/black_figures/King.png");

    painter->drawPixmap(QPointF(0,0),pixmap);
}

/*-----------------------------*/

/*Определения для класса Queen*/
Queen::Queen(const bool &color, QGraphicsItem *parent)
    :FigureBase(parent){
    this->color=color;
    name = "Queen";
}

Queen::~Queen(){

}

void Queen::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option,
           QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    color?pixmap.load(":/img/white_figures/Queen.png")
        :
          pixmap.load(":/img/black_figures/Queen.png");

    painter->drawPixmap(QPointF(0,0),pixmap);
}

/*-----------------------------*/

/*Определения для класса Elephant*/
Elephant::Elephant(const bool &color, QGraphicsItem *parent)
    :FigureBase(parent){
    this->color=color;
    name = "Elephant";
}

Elephant::~Elephant(){

}

void Elephant::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option,
           QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    color?pixmap.load(":/img/white_figures/Elephant.png")
        :
          pixmap.load(":/img/black_figures/Elephant.png");

    painter->drawPixmap(QPointF(0,0),pixmap);
}

/*-----------------------------*/

/*Определения для класса Horse*/
Horse::Horse(const bool &color, QGraphicsItem *parent)
    :FigureBase(parent){
    this->color=color;
    name = "Horse";
}

Horse::~Horse(){

}

void Horse::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option,
           QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    color?pixmap.load(":/img/white_figures/Horse.png")
        :
          pixmap.load(":/img/black_figures/Horse.png");

    painter->drawPixmap(QPointF(0,0),pixmap);
}

/*-----------------------------*/

/*Определения для класса Rook*/
Rook::Rook(const bool &color, QGraphicsItem *parent)
    :FigureBase(parent){
    this->color=color;
     name = "Rook";
}

Rook::~Rook(){

}

void Rook::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option,
           QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    color?pixmap.load(":/img/white_figures/Rook.png")
        :
          pixmap.load(":/img/black_figures/Rook.png");

    painter->drawPixmap(QPointF(0,0),pixmap);
}

/*-----------------------------*/

/*Определения для класса Figure*/
Figures::Figures(const bool &color, QGraphicsItem *parent)
    :FigureBase(parent){
    char yPawn, yGuardian, xPawn='a', xRook='a', xHorse='b', xElephant='c'; //Здесь описаны
                                                                            //координаты фигур

    if(color){
        yGuardian   ='1';
        yPawn       ='2';
    }
    else{
        yGuardian   ='8';
        yPawn       ='7';
    }

    FigureBase*king=new King(color, this);
    king->setPos(BoardChessBase::mapCoordinates.find({'e',yGuardian})->toPoint());
    //vecFig.push_back(king);

    FigureBase*queen=new Queen(color, this);
    queen->setPos(BoardChessBase::mapCoordinates.find({'d',yGuardian})->toPoint());
    //vecFig.push_back(queen);

    for(int i=0;i<2;i++){
        FigureBase*rook=new Rook(color, this);
        rook->setPos(BoardChessBase::mapCoordinates.find({xRook,yGuardian})->toPoint());
        //vecFig.push_back(rook);
        xRook+=7;

        FigureBase*horse=new Horse(color, this);
        horse->setPos(BoardChessBase::mapCoordinates.find({xHorse,yGuardian})->toPoint());
        //vecFig.push_back(horse);
        xHorse+=5;

        FigureBase*elephant=new Elephant(color, this);
        elephant->setPos(BoardChessBase::mapCoordinates.find({xElephant,yGuardian})->toPoint());
        //vecFig.push_back(elephant);
        xElephant+=3;
    }

    for(int i=0; i<8; i++){
        static char x='h';
        FigureBase*pawn=new Pawn(color, this);
        pawn->setPos(BoardChessBase::mapCoordinates.find({xPawn++, yPawn})->toPoint());
        //vecFig.push_back(pawn);
    }
}

Figures::~Figures(){

}

bool Figures::getColor(){
    return color;
}

void Figures::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option,
           QWidget *widget){
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

/*QVector<FigureBase *> Figures::getVectorFig(){
    return vecFig;
}*/

/*-----------------------------*/
