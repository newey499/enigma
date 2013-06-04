#include "rotordata.h"

RotorData::RotorData(QObject *parent) :
    ComponentBase(parent)
{
}


RotorData::~RotorData()
{
}




QSqlRecord RotorData::getRotor(const QString &rotorName)
{
    QSqlRecord rec = EnigmaDatabase::getWheel(EnigmaDatabase::WHEEL_ROTOR, rotorName);

    return rec;
}


QSqlRecord RotorData::getRotor(int id)
{
    QSqlRecord rec = EnigmaDatabase::getWheel(id);

    return rec;
}


bool RotorData::validateRotor(EDIT_MODE mode, QSqlRecord rec)
{
    bool result = true;
    QSqlQuery qry;
    clearError();

    rec = rec;  // TODO debug temporary - remove copiler warning

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



