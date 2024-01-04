#ifndef GAME_H
#define GAME_H

#include <QtGui>
#include <QTimer>
#include <list>

using Point = std::pair<int, int>;

enum class eDirection
{
	Left, Up, Right, Down
};

class Game : public QRasterWindow
{
	Q_OBJECT

public:
	Game(int map_size, int window_size);
	void paintEvent(QPaintEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;

private slots:
    void processGame();

private:
    
    void createFood();
    void moveSnake();
    void feedSnake();
    bool isGameOver();
    void startGame();

private:
	std::list<Point> snake;
    eDirection direction;
    Point food;

    int score;
    QTimer timer;
    bool finished;
    const int map_size;
    const int window_size;
};

#endif // GAME_H