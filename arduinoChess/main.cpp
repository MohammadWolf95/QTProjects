#include <QApplication>
#include <QtWidgets>
#include "boardchess.h"
#include "figures.h"
#include "defines.h"
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    QGraphicsScene scene;
    scene.setSceneRect(200, 24, 600, 600);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    scene.addItem(Game::getInstance());

    /*
     *Нужно сделать map для всех фигур и узнать
     * находится-ли фигура в какой-то позиции
     * В этом поможет
     *
     *    QList<QGraphicsItem *> list = this->collidingItems();
     *   list.at(0);
     *
     * но нужно постоянно обновлять и поэтому потребуются сигналы и слоты
    */

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QPixmap(":/img/main/background.jpg"));
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Arduino Chess"));
    view.resize(1160, 650);
    view.show();

    /*QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    timer.start(1000 / 33);*/

    return a.exec();
}
