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
     * символ \n - это стоп символ, после которого ардуино уже читает слово
     * byte - это массив данных, он состоит из 5 или из 6 ячеек
     * byte[0] и byte[1] - местоположение фигуры,
     * byte[2] и byte[3] - координаты куда надо перемещать фигуру,
     * byte[4] - это либо '\n', если нет жертвы, либо '1' (белый) или '0'
     * (черный), если есть жертва
     * byte[4] - это либо '\n', если есть жертва, либо '\0', если нет жертвы
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
