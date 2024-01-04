#include <QPainter>
#include <QKeyEvent>
#include "game.h"

Game::Game(int map_size, int window_size)
    : direction(eDirection::Up)
    , map_size(map_size)
    , window_size(window_size)
    , score(0)
    , finished(false)
    , timer(this)
{
    srand(time(nullptr));
    resize(window_size, window_size);
    connect(&timer, SIGNAL(timeout()), this, SLOT(processGame()));
    
    startGame();
}

void Game::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::darkGray);
    painter.drawRect(0, 0, window_size, window_size);

    if (finished)
    {
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 20));
        QString text = QString("Game Over, Score: %1, press any key to restart").arg(score);
        painter.drawText(0, (window_size - painter.fontMetrics().height()) / 2, text);
        return;
    }

    int color = 0;
    auto white_ratio = 255.0 / snake.size();

    painter.setPen(Qt::NoPen);
    for (auto p : snake)
    {
        painter.setBrush(QColor(color, 255, color));

        painter.drawRect(p.first * window_size / map_size,
                         p.second * window_size / map_size,
                         window_size / map_size,
                         window_size / map_size);
        color += white_ratio;
    }

    painter.setBrush(Qt::red);
    painter.drawRect(food.first * window_size / map_size,
                     food.second * window_size / map_size,
                     window_size / map_size,
                     window_size / map_size);

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 20));
    painter.drawText(10, 30, QString("Score: %1").arg(score));
}

void Game::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
    if (finished)
    {
        startGame();
        return;
    }

	if (!(Qt::Key_Left <= key && key <= Qt::Key_Down))
	{
        // allow only arrows
		return;
	}
	key -= Qt::Key_Left;

    int current_direction = static_cast<int>(direction);
	
    if (key == (current_direction + 2) % 4)
    {
        // do not allow to move in the opposite direction
        return;
    }
    direction = static_cast<eDirection>(key);
}

void Game::processGame()
{
    if (isGameOver())
    {
        finished = true;
        timer.stop();
        update();
        return;
    }
    moveSnake();

    if (snake.front() == food)
        feedSnake();

    update();
}

void Game::createFood()
{
    do
    {
        int x = rand() % map_size;
        int y = rand() % map_size;
        food = Point(x, y);

    } while (std::find(snake.begin(), snake.end(), food) != snake.end());
}

void Game::moveSnake()
{
    Point head = snake.front();
    
    static const int dx[] = { -1, 0, 1, 0 };
    static const int dy[] = { 0, -1, 0, 1 };
    head.first += dx[static_cast<int>(direction)];
    head.second += dy[static_cast<int>(direction)];

    snake.pop_back();
    snake.push_front(head);
}

void Game::feedSnake()
{
    score++;
    if (score % 5 == 0)
    {
        if (timer.interval() > 20)
            timer.setInterval(timer.interval() - 10);
    }
    createFood();
    snake.push_back(snake.back());
}

bool Game::isGameOver()
{
    Point head = snake.front();
    if (head.first < 0 || head.first >= map_size ||
        head.second < 0 || head.second >= map_size)
    {
        return true;
    }
    for (auto it = ++snake.begin(); it != snake.end(); ++it)
    {
        if (*it == head)
        {
            return true;
        }
    }
    return false;
}

void Game::startGame()
{
    snake.clear();
    snake.push_back(Point(map_size / 2, map_size / 2));
    snake.push_back(Point(map_size / 2, map_size / 2 + 1));
    direction = eDirection::Up;
    score = 0;
    createFood();
    timer.start(100);
    finished = false;
}