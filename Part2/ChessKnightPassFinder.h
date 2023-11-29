#ifndef KNIGHT_CHESSKNIGHTPASSFINDER_H
#define KNIGHT_CHESSKNIGHTPASSFINDER_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QMap>

class ChessKnightPathFinder : public QWidget {
    Q_OBJECT

public:
    ChessKnightPathFinder(QWidget *parent = nullptr);

private slots:
    void onStartButtonClicked();
    void animateKnightMovement();

private:
    void drawChessBoard();
    void convertNotation();
    void knight();

    QPushButton *startButton{};
    QLineEdit *startPosEdit{};
    QLineEdit *endPosEdit{};
    QLabel *knightImage{};
    QTimer *animationTimer{};
    QMap<QPair<int, int>, QPair<int, int>> shortestWay; // <startX, startY>, <endX, endY>

    std::vector<QPair<int, int>> path;
    int currentStep{};
};


#endif //KNIGHT_CHESSKNIGHTPASSFINDER_H
