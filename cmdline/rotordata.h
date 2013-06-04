#ifndef ROTORDATA_H
#define ROTORDATA_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QVariant>

#include "globals.h"
#include "componentbase.h"
#include "enigmadatabase.h"
#include "enigmaexception.h"

class RotorData : public ComponentBase
{
    Q_OBJECT

public:

    explicit RotorData(QObject *parent = 0);
    ~RotorData();

    virtual QSqlRecord getRotor(int id);
    virtual QSqlRecord getRotor(const QString &rotorName);
    virtual bool validateRotor(EDIT_MODE mode, QSqlRecord rec);

signals:

public slots:


protected:


private:


};

#endif // ROTORDATA_H
