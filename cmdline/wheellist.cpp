#include "wheellist.h"


const QString WheelList::SEPERATOR = ",";


WheelList::WheelList(QString wheelType, QString list) :
    QStringList()
{
    this->wheelType = wheelType;

    append(list.split(WheelList::SEPERATOR));
    for (int i = 0; i < count(); i++)
    {
        this->replace(i, at(i).trimmed());
    }
}


QString WheelList::join()
{
    return QStringList().join(WheelList::SEPERATOR);
}

bool WheelList::setWheelType()
{
    bool result = true;


    return result;
}

QString WheelList::getWheelType()
{
    return wheelType;
}

