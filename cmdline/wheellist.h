#ifndef WHEELLIST_H
#define WHEELLIST_H

#include <QObject>
#include <QStringList>

class WheelList : public QStringList
{

public:

    static const QString SEPERATOR;

    explicit WheelList();
    explicit WheelList(QString list);
    explicit WheelList(QStringList list);

    virtual QString join();

signals:


public slots:


protected:


private:


};

#endif // WHEELLIST_H
