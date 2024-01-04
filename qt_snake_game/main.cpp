#include "Snake.h"
#include <QtGui>
#include <chrono>
#include <QDebug>

int main(int argc, char *argv[])
{
	QGuiApplication a(argc, argv);

	qDebug() << "Hello World";
	
	Snake w;
	w.resize(600, 600);
	
	qDebug() << "Raster Window Created";

	w.show();
	qDebug() << "Raster Window Shown";
	
	return a.exec();
}
