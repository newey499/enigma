#ifndef ROTOR_H
#define ROTOR_H

#include <QHash>
#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>


#include "enigmadatabase.h"

class Rotor : public QObject
{
    Q_OBJECT

public:

    explicit Rotor(QObject *parent = 0);

    ~Rotor();

signals:

public slots:

protected:

    QPointer<EnigmaDatabase> edb;

    QSqlRecord recRotor;
    QSqlRecord recAlphabet;

private:

};

#endif // ROTOR_H
