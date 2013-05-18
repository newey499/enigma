#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>

#include "globals.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void exec();

protected:

    QPointer<Globals> globals;


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
