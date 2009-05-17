#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindowPrivate;
class MainWindow : public QMainWindow {
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)
  public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    void loadFile(const QString &filename);


  public Q_SLOTS:
    void fontFamilyChanged(const QFont &font);
    void fontSizeChanged(int index);

    void bondLengthChanged(double);
    void penWidthChanged(double);
    void bondWidthChanged(double);
    void bondSpacingChanged(double);

  protected:
    virtual void changeEvent(QEvent *e);


  private:
    Ui::MainWindow *m_ui;
    MainWindowPrivate * const d;
};

#endif // MAINWINDOW_H
