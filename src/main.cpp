#include <QApplication>
#include "MainWidget.h"

int main(int argc, char* argv[]) {
  QApplication app(argc,argv);
  MainWidget z;
  z.show();
  return app.exec();
}
