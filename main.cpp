#include "atimelogger.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ATimeLogger w;
	w.show();
	return a.exec();
}
