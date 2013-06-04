#ifndef MACHINEDATA_H
#define MACHINEDATA_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QVariant>

#include "globals.h"
#include "componentbase.h"
#include "enigmadatabase.h"
#include "enigmaexception.h"


class MachineData : public ComponentBase
{
    Q_OBJECT

public:

    explicit MachineData(QObject *parent = 0);
    ~MachineData();

    virtual QSqlRecord getMachine(const QString &machineName);
    virtual QSqlRecord getMachine(int id);
    virtual bool validateMachine(EDIT_MODE mode, QSqlRecord rec);

    virtual QSqlRecord _getMachine(QSqlQuery qry);

signals:

public slots:


protected:


private:


};

#endif // MACHINEDATA_H
