#ifndef KNIGHT_CHESSKNIGHTPASSFINDER_H
#define KNIGHT_CHESSKNIGHTPASSFINDER_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QMap>
#include <QPair>

class ChessKnightPathFinder : public QWidget {
    Q_OBJECT

public:
    ChessKnightPathFinder(QWidget *parent = nullptr);

private slots:
    void onStartButtonClicked();
    void animateKnightMovement();

private:
    void drawChessBoard();
    void convertNotation(const QString& position, int& x, int& y);
    void pathFinder(int startX, int startY, int endX, int endY);
    int currentStep{};

    std::vector<QPair<int, int>> path;
    QMap<QPair<int, int>, QPair<int, int>> shortestWay; // <startX, startY>, <endX, endY>

    QPushButton *startButton{};
    QLineEdit *startPosEdit{};
    QLineEdit *endPosEdit{};
    QLabel *knightImage{};
    QTimer *animationTimer{};

};


#endif //KNIGHT_CHESSKNIGHTPASSFINDER_H
