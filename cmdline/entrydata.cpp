#include "entrydata.h"

EntryData::EntryData(QObject *parent) :
    ComponentBase(parent)
{
}


EntryData::~EntryData()
{
}


QSqlRecord EntryData::getEntry(const QString &rotorName)
{
    QSqlRecord rec = EnigmaDatabase::getWheel(EnigmaDatabase::WHEEL_ENTRY, rotorName);

    return rec;
}


QSqlRecord EntryData::getEntry(int id)
{
    QSqlRecord rec = EnigmaDatabase::getWheel(id);

    return rec;
}


bool EntryData::validateEntry(EDIT_MODE mode, QSqlRecord rec)
{
    bool result = true;
    QSqlQuery qry;
    clearError();

    rec = rec;  // TODO debug temporarily suppressed unused parm warning

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







