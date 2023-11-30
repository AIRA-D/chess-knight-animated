#include "ChessKnightPassFinder.h"
#include <QGridLayout>
#include <QPixmap>
#include <QPair>
#include <vector>
#include <queue>
#include <map>

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

void ChessKnightPathFinder::drawChessBoard()  {
    auto *gridLayout = new QGridLayout;

    const int numRows = 8;
    const int numCols = 8;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            auto *squareLabel = new QLabel(this);
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
void ChessKnightPathFinder::pathFinder(int startX, int startY, int endX, int endY) {
    // Возможные ходы
    const std::vector<std::pair<int, int>> moves = {
            {-2,-1}, {-2,1}, {2,-1}, {2,1},
            {-1,-2}, {-1,2}, {1,-2}, {1,2}
    };

    std::queue<QPair<int, int>> positionsQueue;
    positionsQueue.emplace(startX, startY);

    QMap<QPair<int, int>, std::pair<int, int>> previousPositions;
    QPair<int, int> currentPos;

    while (!positionsQueue.empty()) {
        currentPos = positionsQueue.front();
        positionsQueue.pop();

        if (currentPos.first == endX && currentPos.second == endY) {
            QPair<int, int> retreatPosition = {endX, endY};
            while (retreatPosition != QPair(startX, startY)) {
                path.push_back(retreatPosition);
                //retreatPosition = previousPositions[retreatPosition];
            }
            path.emplace_back(startX, startY);
            std::reverse(path.begin(), path.end());
            return;
        }

        for (const auto& move : moves) {
            auto newX = currentPos.first + move.first;
            auto newY = currentPos.second + move.second;
            if (newX >= 1 && newX <= 8 && newY >= 1 && newY <= 8) {
                if (previousPositions.find({newX, newY}) == previousPositions.end()) {
                    positionsQueue.emplace(newX, newY);
                    //previousPositions[{newX, newY}] = currentPos;
                }
            }
        }
    }
}
