#include <QApplication>
#include <QWidget>

#include "mainwindow.h"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  MainWindow *window = new MainWindow;
  window->show();

  if (argc > 1)
    window->loadFile(argv[1]);

  return app.exec();
}
