#include <QApplication>
#include "ChessKnightPassFinder.h"


int main(int argc, char *argv[]) {
    QApplication  application(argc, argv);
    ChessKnightPathFinder mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
