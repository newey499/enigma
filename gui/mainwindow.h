#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QtGui/QApplication>

#include <QCloseEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QPointer>
#include <QSettings>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "globals.h"
#include "genlib.h"
#include "enigmaexception.h"
#include "enigmaaction.h"

#include "formmachine.h"
#include "formtestcomponents.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    virtual void aboutEnigma();
    virtual void aboutQt();
    virtual void quitApplication();
    virtual void slotFormTestAlphabet();
    virtual void createMachineMenuItems(QMenu *menu);
    virtual void slotMachine(EnigmaAction *action);
    virtual void slotFormTestComponents();

protected:

    QPointer<Globals> globals;

    virtual void buildMenusAndForms();

    virtual void saveSettings();

    /**
    \brief called by QT when request is made to exit the application
      ***************/
    virtual void closeEvent(QCloseEvent *event);

    /**
    \brief Message Box that asks for confirmation of application exit
      ******************/
    virtual int quitYesNo();



    virtual EnigmaAction * addMenuItem(QMenu *menu, QString title);



private:

    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
