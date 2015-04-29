#include "workspace.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	WorkSpace w;
	w.show();
	return a.exec();
}
