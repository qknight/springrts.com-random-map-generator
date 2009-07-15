#include <QApplication>
#include "mainWidget.h"

int main(int argc, char* argv[]) {
  QApplication app(argc,argv);
  mainWidget z;
  z.show();
  return app.exec();
}
