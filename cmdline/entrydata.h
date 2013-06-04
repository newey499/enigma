#ifndef ENTRYDATA_H
#define ENTRYDATA_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QVariant>

#include "globals.h"
#include "componentbase.h"
#include "enigmadatabase.h"
#include "enigmaexception.h"

class EntryData : public ComponentBase
{
    Q_OBJECT

public:

    explicit EntryData(QObject *parent = 0);
    ~EntryData();


    virtual QSqlRecord getEntry(int id);
    virtual QSqlRecord getEntry(const QString &rotorName);
    virtual bool validateEntry(EDIT_MODE mode, QSqlRecord rec);

signals:

public slots:

};

#endif // ENTRYDATA_H
