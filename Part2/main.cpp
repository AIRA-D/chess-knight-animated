
#include "chessknightpathfinder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChessKnightPathFinder w;
    w.show();
    return a.exec();
}
