#include <QTimer>
#include <QLabel>
#include <QPixmap>
#include <qdebug.h>
#include <queue>
#include <QPainter>

#include "chessknightpathfinder.h"
#include "./ui_chessknightpathfinder.h"

ChessKnightPathFinder::ChessKnightPathFinder(QWidget *parent): QMainWindow(parent), ui(new Ui::ChessKnightPathFinder)
{
    ui->setupUi(this);
    drawChessboard();

    startPosEdit = findChild<QLineEdit *>("lineEditStart");  // Assign the member variable
    endPosEdit = findChild<QLineEdit *>("lineEditEnd");  // Assign the member variable
    startButton = findChild<QPushButton *>("startButton");  // Assign the member variable

    animationTimer = new QTimer(this);

    connect(startButton, &QPushButton::clicked, this, &ChessKnightPathFinder::on_startButton_clicked);
    connect(startPosEdit, &QLineEdit::textEdited, this, &ChessKnightPathFinder::on_lineEditStart_textEdited);
    connect(endPosEdit, &QLineEdit::textEdited, this, &ChessKnightPathFinder::on_lineEditEnd_textEdited);
    connect(animationTimer, &QTimer::timeout, this, &ChessKnightPathFinder::animateKnightMovement);
}

ChessKnightPathFinder::~ChessKnightPathFinder()
{
    delete ui;
}

void ChessKnightPathFinder::on_lineEditEnd_textEdited(const QString &arg1){}

void ChessKnightPathFinder::on_lineEditStart_textEdited(const QString &arg1){}


void ChessKnightPathFinder::on_startButton_clicked()
{
    QString startPos = startPosEdit->text();
    QString endPos = endPosEdit->text();

    int startX, startY, endX, endY;
    convertNotation(startPos, startX, startY);
    convertNotation(endPos, endX, endY);

    path.clear();
    pathFinder(startX, startY, endX, endY);

    currentStep = 0;
    animationTimer->start(500);
    startButton->setEnabled(false);
}

void ChessKnightPathFinder::drawChessboard()  {

    auto *chessboardLayout = findChild<QGridLayout *>("chessboard");

    const int numRows = 8;
    const int numCols = 8;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            auto *squareLabel = new QLabel(this);
            squareLabel->setFixedSize(50, 50); // Set the size of each square
            if ((row + col) % 2 == 0) {
                squareLabel->setStyleSheet("background-color: white");
            } else {
                squareLabel->setStyleSheet("background-color: #99582a");
            }
            chessboardLayout->addWidget(squareLabel, row, col);
        }
    }

    QStringList horizontalLabels = {"a", "b", "c", "d", "e", "f", "g", "h"};
    QStringList verticalLabels = {"8", "7", "6", "5", "4", "3", "2", "1"};

    for (int i = 0; i < numCols; ++i) {
        auto *horizontalLabel = new QLabel(horizontalLabels.at(i), this);
        auto verticalLabel = new QLabel(verticalLabels.at(i), this);
        horizontalLabel->setAlignment(Qt::AlignHCenter);
        verticalLabel->setAlignment(Qt::AlignVCenter);
        chessboardLayout->addWidget(horizontalLabel, numRows, i, 1, 1, Qt::AlignHCenter);
        chessboardLayout->addWidget(verticalLabel, i, numCols, 1, 1, Qt::AlignVCenter);
    }

}

void ChessKnightPathFinder::animateKnightMovement() {
    if (currentStep < path.size()) {
        int newX = path[currentStep].first;
        int newY = path[currentStep].second;

        int x = newX - 1;  // Convert 1-8 to array index 0-7
        int y = 8 - newY;  // Adjust to account for the board's orientation

        auto *chessboardLayout = findChild<QGridLayout *>("chessboard");

        auto* currentChessLabel = qobject_cast<QLabel*>(chessboardLayout->itemAtPosition(y, x)->widget());
        //QPixmap knightPixmap("/home/aira/PathFinder/knight.png");
        QPixmap knightPixmap(":/knight.png");

        if (currentChessLabel) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    auto* label = qobject_cast<QLabel*>(chessboardLayout->itemAtPosition(i, j)->widget());
                    if (label) {
                        label->clear();  // clear the content of the label
                    }
                }
            }
            currentChessLabel->setPixmap(knightPixmap.scaled(50, 50, Qt::KeepAspectRatio));
        }

        currentStep++;
    } else {
        animationTimer->stop();
        startButton->setEnabled(true);
    }
}

void ChessKnightPathFinder::convertNotation(const QString& position, int& x, int& y) {
    QChar col = position.at(0).toLower();  // Convert the letter to lowercase, allowing both uppercase and lowercase input
    QChar row = position.at(1);

    if (col < 'a' || col > 'h' || row < '1' || row > '8') {
        // handle out-of-range input, possibly by throwing an exception or setting default values for x and y
        x = -1;  // Invalid x
        y = -1;  // Invalid y
        return;
    }

    // Преобразование col и row в соответствующие координаты x и y
    x = col.toLatin1() - 'a' + 1;  // a=1, b=2, ..., h=8
    y = row.digitValue();
}

void ChessKnightPathFinder::pathFinder(int startX, int startY, int endX, int endY) {
    // Возможные ходы
    const std::vector<std::pair<int, int>> moves = {
            {-2,-1}, {-2,1}, {2,-1}, {2,1},
            {-1,-2}, {-1,2}, {1,-2}, {1,2}
    };

    std::queue<QPair<int, int>> positionsQueue;
    positionsQueue.emplace(startX, startY);

    QMap<QPair<int, int>, QPair<int, int>> previousPositions;
    QPair<int, int> currentPos;

    while (!positionsQueue.empty()) {
        currentPos = positionsQueue.front();
        positionsQueue.pop();

        if (currentPos.first == endX && currentPos.second == endY) {
            QPair<int, int> retreatPosition = {endX, endY};
            while (retreatPosition != QPair(startX, startY)) {
                path.push_back(retreatPosition);
                retreatPosition = previousPositions[retreatPosition];
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
                    previousPositions[{newX, newY}] = currentPos;
                }
            }
        }
    }
}


