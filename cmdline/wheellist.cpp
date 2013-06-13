#include "wheellist.h"


const QString WheelList::SEPERATOR = ",";


WheelList::WheelList() :
    QStringList()
{

}


WheelList::WheelList(QString list) :
    QStringList()
{
    append(list.split(WheelList::SEPERATOR, QString::SkipEmptyParts, Qt::CaseSensitive));
    for (int i = 0; i < count(); i++)
    {
        this->replace(i, at(i).trimmed());
    }
}

WheelList::WheelList(QStringList list) :
    QStringList(list)
{

}


QString WheelList::join()
{
    QString result = QStringList::join(WheelList::SEPERATOR);

    return result;
}






