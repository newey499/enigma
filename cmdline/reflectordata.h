#ifndef REFLECTORDATA_H
#define REFLECTORDATA_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QVariant>

#include "globals.h"
#include "componentbase.h"
#include "enigmadatabase.h"
#include "enigmaexception.h"

class ReflectorData : public ComponentBase
{
    Q_OBJECT

public:

    explicit ReflectorData(QObject *parent = 0);
    ~ReflectorData();

    virtual QSqlRecord getReflector(int id);
    virtual QSqlRecord getReflector(const QString &rotorName);
    virtual bool validateReflector(EDIT_MODE mode, QSqlRecord rec);

signals:

public slots:


protected:


private:


};

#endif // REFLECTORDATA_H
