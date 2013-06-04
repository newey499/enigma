#include "reflectordata.h"

ReflectorData::ReflectorData(QObject *parent) :
    ComponentBase(parent)
{
}

ReflectorData::~ReflectorData()
{
}


QSqlRecord ReflectorData::getReflector(const QString &rotorName)
{
    QSqlRecord rec = EnigmaDatabase::getWheel(EnigmaDatabase::WHEEL_REFLECTOR, rotorName);

    return rec;
}


QSqlRecord ReflectorData::getReflector(int id)
{
    QSqlRecord rec = EnigmaDatabase::getWheel(id);

    return rec;
}


bool ReflectorData::validateReflector(EDIT_MODE mode, QSqlRecord rec)
{
    bool result = true;
    QSqlQuery qry;
    clearError();

    rec = rec; // TODO debug suppress unused parameter warning

    switch (mode)
    {
    case ROW_ADD :
        break;

    case ROW_EDIT :
        break;

    case ROW_DEL :
        break;

    default :
        result = false;
        QString msg = QString("");
        addError(msg);
        qDebug("[%d] is not an expected edit mode %s %d",
               mode,
               __FILE__,
               __LINE__);
        break;
    }

    return result;
}
