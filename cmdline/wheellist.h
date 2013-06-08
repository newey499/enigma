#ifndef WHEELLIST_H
#define WHEELLIST_H

#include <QObject>
#include <QStringList>

class WheelList : public QStringList
{

public:

    static const QString SEPERATOR;

    explicit WheelList(QString wheelType, QString list);

    virtual QString join();
    virtual bool setWheelType();
    virtual QString getWheelType();

signals:


public slots:


protected:

    QString wheelType;

private:


};

#endif // WHEELLIST_H
