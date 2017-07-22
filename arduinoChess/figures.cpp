#include "figures.h"
#include <QtWidgets>
#include "game.h"

/*Определения для класса Pawn*/
FigureBase::FigureBase(QGraphicsItem *parent)
    :QGraphicsObject(parent), color(false), name(""), firstStep(false){
    setCursor(Qt::OpenHandCursor);
}

FigureBase::~FigureBase()
{
}

QRectF FigureBase::boundingRect() const{
    return QRectF(5, 5, 40, 40);
}

void FigureBase::writePosInByte(const char&x, const char&y){
    //Эта функция записывает координаты
    //местоположения фигуры в переменную
    //byte класса game
    QByteArray &byte = Game::getInstance()->byte;
    byte.clear();
    byte.append(x);
    byte.append(y);
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
    Game::getInstance()->setFigureMoved(this);

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

bool FigureBase::calcStepsForKQERH(BoardChessCell*cell, QVector<BoardChessCell*>&vec){
    //Эта функция высвечивает возможные ходы и убийства для таких фигур,
    //как King, Queen, Elephant, Rook, Horse
    QList<QGraphicsItem*> items = cell->collidingItems();
    if(!(items.isEmpty())){
        FigureBase *figure = dynamic_cast<FigureBase *>(items.at(0));
        if(figure->getColor()!=color){
            vec.push_back(cell);
        }
        return true;
    }
    else{
        vec.push_back(cell);
        return false;
    }
}

void FigureBase::possibleSteps(){
}

/*-----------------------------*/

/*Определения для класса Pawn*/
Pawn::Pawn(const bool &color, QGraphicsItem *parent)
    :FigureBase(parent){
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

void Pawn::possibleSteps(){
    auto cellD3=Game::getInstance()->getMapCell().find(QPair<char,char>('3','d'));

    vector.clear();
    auto game = Game::getInstance();
    QPair<char, char> charCoordinate = BoardChessBase::mapCoordinates.key(pos());
    idCoordinate=charCoordinate;
    char x = charCoordinate.first;
    char y = charCoordinate.second;

    writePosInByte(x,y);

    char yStep = y;
    char xKillDiagonal[]={x-1, x+1};    //координаты жертв для текущей пешки по x
    int imax=1;
    auto mapCells = game->getMapCell();

    firstStep?(imax=1):(imax=2);//проверка первого хода.
                                //Если это первый ход, то есть возможность пешке
                                //пойти на два хода вперед

    //алгоритм нахождения ходов для пешки
    for(int i=0;i<imax;i++){
        color?(++yStep) :(--yStep);
        auto cell = mapCells.find(qMakePair(yStep,x)).value();
        if(!(cell->collidingItems().isEmpty())){
            break;
        }
        vector.push_back(cell);
    }

    //алгоритм нахождения убийств для пешки
    yStep = y;
    color?(++yStep) :(--yStep);
    for(int i=0;i<2;i++){
        if((yStep>='1' && yStep<='8') &&
                (xKillDiagonal[i]>='a' && xKillDiagonal[i]<='h')){
            auto cell = mapCells.find(qMakePair(yStep,xKillDiagonal[i])).value();
            QList<QGraphicsItem*> items = cell->collidingItems();
            if(!(items.isEmpty())){
                FigureBase *figure = dynamic_cast<FigureBase *>(items.at(0));
                if(figure->getColor()!=color){
                    vector.push_back(cell);
                }
            }
        }
    }
}

void Pawn::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setCursor(Qt::ClosedHandCursor);
    auto game = Game::getInstance();
    game->reDrawing();
    game->setVector(vector);
}

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

void King::possibleSteps(){
    vector.clear();
    auto game = Game::getInstance();
    QPair<char, char> charCoordinate = BoardChessBase::mapCoordinates.key(pos());
    char x = charCoordinate.first;
    char y = charCoordinate.second;
    //QVector<BoardChessCell*>vec;

    writePosInByte(x,y);
    this->firstStep;
    //алгоритм для нахождения ходов и убийств для короля
    QVector <QPair<char, char>>vecKillSteps;
    auto mapCells = game->getMapCell();

    //Ходы для короля
    vecKillSteps.push_front(qMakePair(y-1,x-1));
    vecKillSteps.push_front(qMakePair(y-1,x+1));
    vecKillSteps.push_front(qMakePair(y-1,x));
    vecKillSteps.push_front(qMakePair(y,x+1));
    vecKillSteps.push_front(qMakePair(y,x-1));
    vecKillSteps.push_front(qMakePair(y+1,x+1));
    vecKillSteps.push_front(qMakePair(y+1,x-1));
    vecKillSteps.push_front(qMakePair(y+1,x));
    for(auto i:vecKillSteps){
        if((i.first>='1' && i.first<='8') &&
            (i.second>='a' && i.second<='h')){
            auto cell = mapCells.find(i).value();
            calcStepsForKQERH(cell, vector);
        }
    }

    //Проверка рокировки
    vecKillSteps.clear();
    int left=0, right=0;
    if(!firstStep){
        QPair<char, char> hRoock(y,x+3);
        auto cellH = mapCells.find(hRoock).value();
        QList<QGraphicsItem*> itemsH = cellH->collidingItems();
        if(!(itemsH.isEmpty())){
            FigureBase *figure = dynamic_cast<FigureBase *>(itemsH.at(0));
            if(!(figure->firstStep)){
                //Эти клетки между короткой рокировки
                vecKillSteps.push_front(qMakePair(y,x+1));
                vecKillSteps.push_front(qMakePair(y,x+2));
                for(auto i:vecKillSteps){
                    auto cell = mapCells.find(i).value();
                    QList<QGraphicsItem*> items = cell->collidingItems();
                    if(!(items.isEmpty())){
                        break;
                    }
                    ++left;
                }
                if(left==2)
                    vector.push_back(cellH);
            }
        }

        vecKillSteps.clear();
        QPair<char, char> aRook(y,x-4);
        auto cellA = mapCells.find(aRook).value();
        QList<QGraphicsItem*> itemsA = cellA->collidingItems();
        if(!(itemsA.isEmpty())){
            FigureBase *figure = dynamic_cast<FigureBase *>(itemsA.at(0));
            if(!(figure->firstStep)){
                //Эти клетки между длинной рокировки
                vecKillSteps.push_front(qMakePair(y,x-1));
                vecKillSteps.push_front(qMakePair(y,x-2));
                vecKillSteps.push_front(qMakePair(y,x-3));
                for(auto i:vecKillSteps){
                    auto cell = mapCells.find(i).value();
                    QList<QGraphicsItem*> items = cell->collidingItems();
                    if(!(items.isEmpty())){
                        break;
                    }
                    ++right;
                }
                if(right==3)
                    vector.push_back(cellA);
            }
        }
    }
}

void King::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setCursor(Qt::ClosedHandCursor);
    auto game = Game::getInstance();
    game->reDrawing();
    game->setVector(vector);
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

void Queen::possibleSteps(){
    auto game = Game::getInstance();
    QPair<char, char> charCoordinate = BoardChessBase::mapCoordinates.key(pos());
    char x = charCoordinate.first;
    char y = charCoordinate.second;
    //QVector<BoardChessCell*>vec;

    writePosInByte(x,y);

    //алгоритм для нахождения ходов и убийств для короля
    char yStepKill, xStepKill;
    auto mapCells = game->getMapCell();
    yStepKill=y+1;
    xStepKill=x;
    for(yStepKill;yStepKill<='8';++yStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }

    yStepKill=y-1;
    xStepKill=x;
    for(yStepKill;yStepKill>='1';--yStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }

    yStepKill=y;
    xStepKill=x+1;
    for(xStepKill;xStepKill<='h';++xStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }

    yStepKill=y;
    xStepKill=x-1;
    for(xStepKill;xStepKill>='a';--xStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }

    yStepKill=y-1;
    xStepKill=x-1;
    for(xStepKill,yStepKill;(xStepKill>='a' && yStepKill>='1');--xStepKill, --yStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }

    yStepKill=y+1;
    xStepKill=x+1;
    for(xStepKill,yStepKill;(xStepKill<='h' && yStepKill<='8');++xStepKill, ++yStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }

    yStepKill=y+1;
    xStepKill=x-1;
    for(xStepKill,yStepKill;(xStepKill>='a' && yStepKill<='8');--xStepKill, ++yStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }

    yStepKill=y-1;
    xStepKill=x+1;
    for(xStepKill,yStepKill;(xStepKill<='h' && yStepKill>='1');++xStepKill, --yStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }
}

void Queen::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setCursor(Qt::ClosedHandCursor);
    auto game = Game::getInstance();
    game->reDrawing();
    game->setVector(vector);
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

void Elephant::possibleSteps(){
    auto game = Game::getInstance();
    QPair<char, char> charCoordinate = BoardChessBase::mapCoordinates.key(pos());
    char x = charCoordinate.first;
    char y = charCoordinate.second;

    writePosInByte(x,y);

    //алгоритм для нахождения ходов и убийств для короля
    char yStepKill, xStepKill;
    auto mapCells = game->getMapCell();

    yStepKill=y-1;
    xStepKill=x-1;
    for(xStepKill,yStepKill;(xStepKill>='a' && yStepKill>='1');--xStepKill, --yStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }

    yStepKill=y+1;
    xStepKill=x+1;
    for(xStepKill,yStepKill;(xStepKill<='h' && yStepKill<='8');++xStepKill, ++yStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }

    yStepKill=y+1;
    xStepKill=x-1;
    for(xStepKill,yStepKill;(xStepKill>='a' && yStepKill<='8');--xStepKill, ++yStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }

    yStepKill=y-1;
    xStepKill=x+1;
    for(xStepKill,yStepKill;(xStepKill<='h' && yStepKill>='1');++xStepKill, --yStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }
}

void Elephant::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setCursor(Qt::ClosedHandCursor);
    auto game = Game::getInstance();
    game->reDrawing();
    game->setVector(vector);
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

void Horse::possibleSteps(){
    auto game = Game::getInstance();
    QPair<char, char> charCoordinate = BoardChessBase::mapCoordinates.key(pos());
    char x = charCoordinate.first;
    char y = charCoordinate.second;
    //QVector<BoardChessCell*>vec;

    writePosInByte(x,y);

    //алгоритм для нахождения ходов и убийств для короля
    QVector <QPair<char, char>>vecKillSteps;
    auto mapCells = game->getMapCell();
    vecKillSteps.push_front(qMakePair(y+1,x+2));
    vecKillSteps.push_front(qMakePair(y+1,x-2));
    vecKillSteps.push_front(qMakePair(y+2,x+1));
    vecKillSteps.push_front(qMakePair(y+2,x-1));
    vecKillSteps.push_front(qMakePair(y-1,x+2));
    vecKillSteps.push_front(qMakePair(y-1,x-2));
    vecKillSteps.push_front(qMakePair(y-2,x+1));
    vecKillSteps.push_front(qMakePair(y-2,x-1));

    for(auto i:vecKillSteps){
        if((i.first>='1' && i.first<='8') &&
            (i.second>='a' && i.second<='h')){
            auto cell = mapCells.find(i).value();
            calcStepsForKQERH(cell, vector);
        }
    }
}

void Horse::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setCursor(Qt::ClosedHandCursor);
    auto game = Game::getInstance();
    game->reDrawing(); 
    game->setVector(vector);
}

/*-----------------------------*/

/*Определения для класса Rook*/
Rook::Rook(const bool &color, QGraphicsItem *parent)
    :FigureBase(parent){
    this->color=color;
    name = "Rook";
}

Rook::~Rook()
{
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

void Rook::possibleSteps(){
    auto game = Game::getInstance();
    QPair<char, char> charCoordinate = BoardChessBase::mapCoordinates.key(pos());
    char x = charCoordinate.first;
    char y = charCoordinate.second;
    //QVector<BoardChessCell*>vec;

    writePosInByte(x,y);

    //алгоритм для нахождения ходов и убийств для короля
    char yStepKill, xStepKill;
    auto mapCells = game->getMapCell();
    yStepKill=y+1;
    xStepKill=x;
    for(yStepKill;yStepKill<='8';++yStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }

    yStepKill=y-1;
    xStepKill=x;
    for(yStepKill;yStepKill>='1';--yStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }

    yStepKill=y;
    xStepKill=x+1;
    for(xStepKill;xStepKill<='h';++xStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }

    yStepKill=y;
    xStepKill=x-1;
    for(xStepKill;xStepKill>='a';--xStepKill){
        auto cell = mapCells.find(qMakePair(yStepKill,xStepKill)).value();
        if(calcStepsForKQERH(cell, vector))
            break;
    }
}

void Rook::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setCursor(Qt::ClosedHandCursor);
    auto game = Game::getInstance();
    game->reDrawing();
    game->setVector(vector);
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
    vecFig.push_back(king);

    FigureBase*queen=new Queen(color, this);
    queen->setPos(BoardChessBase::mapCoordinates.find({'d',yGuardian})->toPoint());
    vecFig.push_back(queen);

    for(int i=0;i<2;i++){
        FigureBase*rook=new Rook(color, this);
        rook->setPos(BoardChessBase::mapCoordinates.find({xRook,yGuardian})->toPoint());
        vecFig.push_back(rook);
        xRook+=7;

        FigureBase*horse=new Horse(color, this);
        horse->setPos(BoardChessBase::mapCoordinates.find({xHorse,yGuardian})->toPoint());
        vecFig.push_back(horse);
        xHorse+=5;

        FigureBase*elephant=new Elephant(color, this);
        elephant->setPos(BoardChessBase::mapCoordinates.find({xElephant,yGuardian})->toPoint());
        vecFig.push_back(elephant);
        xElephant+=3;
    }

    for(int i=0; i<8; i++){
        FigureBase*pawn=new Pawn(color, this);
        pawn->setPos(BoardChessBase::mapCoordinates.find({xPawn++, yPawn})->toPoint());
        vecFig.push_back(pawn);
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
