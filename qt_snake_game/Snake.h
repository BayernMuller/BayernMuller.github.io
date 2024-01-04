#pragma once
#include <QtGui>
#include "Game.h"

class Snake : public QRasterWindow
{
	Q_OBJECT

public:
	Snake();
	void paintEvent(QPaintEvent* event) override;
	void keyPressEvent(QKeyEvent* d) override;


private:
	Game mGame;
};
