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

void ChessKnightPathFinder::drawChessBoard() {
    QGridLayout *gridLayout = new QGridLayout;

    const int numRows = 8;
    const int numCols = 8;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            QLabel *squareLabel = new QLabel(this);
            squareLabel->setFixedSize(50, 50); // Set the size of each square
            if ((row + col) % 2 == 0) {
                squareLabel->setStyleSheet("background-color: white");
            } else {
                squareLabel->setStyleSheet("background-color: gray");
            }
            gridLayout->addWidget(squareLabel, row, col);
        }
    }

    QStringList horizontalLabels = {"a", "b", "c", "d", "e", "f", "g", "h"};
    QStringList verticalLabels = {"8", "7", "6", "5", "4", "3", "2", "1"};

    for (int i = 0; i < numCols; ++i) {
        QLabel *horizontalLabel = new QLabel(horizontalLabels.at(i), this);
        QLabel *verticalLabel = new QLabel(verticalLabels.at(i), this);
        horizontalLabel->setAlignment(Qt::AlignHCenter);
        verticalLabel->setAlignment(Qt::AlignVCenter);
        gridLayout->addWidget(horizontalLabel, numRows, i, 1, 1, Qt::AlignHCenter);
        gridLayout->addWidget(verticalLabel, i, numCols, 1, 1, Qt::AlignVCenter);
    }
    
    setLayout(gridLayout);
}

void ChessKnightPathFinder::onStartButtonClicked() {}
void ChessKnightPathFinder::animateKnightMovement() {}
void ChessKnightPathFinder::convertNotation() {}
void ChessKnightPathFinder::knight() {}
