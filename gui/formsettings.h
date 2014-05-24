#ifndef FORMSETTINGS_H
#define FORMSETTINGS_H

#include <QSqlDatabase>
#include <QWidget>
#include "globals.h"
#include "enigmadatabase.h"

namespace Ui {
class FormSettings;
}

class FormSettings : public QWidget
{
    Q_OBJECT

public:
    explicit FormSettings(QWidget *parent = 0);
    ~FormSettings();

public slots:

    void slotSaveSettings();
    void slotDriverChanged(QString newDriver);

protected:

    Globals * globals;
    EnigmaDatabase *database;

    void initUi();
    bool isOdbcDriver(QString driverName);

private:
    Ui::FormSettings *ui;
};

#endif // FORMSETTINGS_H
