#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <QCoreApplication>

#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>


#include "enigmadatabase.h"
#include "rotor.h"

class EntryPoint : public QObject
{
    Q_OBJECT

public:

    explicit EntryPoint(QObject *parent = 0);

    int exec();


signals:

public slots:


protected:

    QPointer<EnigmaDatabase> edb;

private:


};

#endif // ENTRYPOINT_H
