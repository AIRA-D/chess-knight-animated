#include "ChessKnightPassFinder.h"
#include <QGridLayout>
#include <QPixmap>

ChessKnightPathFinder::ChessKnightPathFinder(QWidget *parent) : QWidget(parent){
    startButton = new QPushButton("Старт!", this);
    startPosEdit = new QLineEdit(this);
    endPosEdit = new QLineEdit(this);
    knightImage = new QLabel(this);
    drawChessBoard();

    connect(startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));

    /*
     * UI
     */

    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(animateKnightMovement()));
}

void ChessKnightPathFinder::drawChessBoard() {}
void ChessKnightPathFinder::onStartButtonClicked() {}
void ChessKnightPathFinder::animateKnightMovement() {}
void ChessKnightPathFinder::convertNotation() {}
void ChessKnightPathFinder::knight() {}