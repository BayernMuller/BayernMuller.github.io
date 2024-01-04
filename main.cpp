#include <QtGui>
#include "game.h"

int main(int argc, char *argv[])
{
	QGuiApplication a(argc, argv);

	Game game(50, 800);
	game.show();
	
	return a.exec();
}
