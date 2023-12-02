#ifndef CHESSKNIGHTPATHFINDER_H
#define CHESSKNIGHTPATHFINDER_H

#include <QMainWindow>
#include <QMap>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class ChessKnightPathFinder; }
QT_END_NAMESPACE

class ChessKnightPathFinder : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChessKnightPathFinder(QWidget *parent = nullptr);
    ~ChessKnightPathFinder() override;

private slots:
    void on_lineEditEnd_textEdited(const QString &arg1);
    void on_lineEditStart_textEdited(const QString &arg1);
    void on_startButton_clicked();
    void animateKnightMovement();

private:
    Ui::ChessKnightPathFinder *ui;
    std::vector<QPair<int, int>> path;
    QMap<QPair<int, int>, QPair<int, int>> shortestWay; // <startX, startY>, <endX, endY>

    void drawChessboard();
    static void convertNotation(const QString& position, int& x, int& y);
    void pathFinder(int startX, int startY, int endX, int endY);
    int currentStep{};


    QPushButton *startButton{};
    QLineEdit *startPosEdit{};
    QLineEdit *endPosEdit{};
    QLabel *knightImage{};
    QTimer *animationTimer{};

};
#endif // CHESSKNIGHTPATHFINDER_H
