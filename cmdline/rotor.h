#ifndef ROTOR_H
#define ROTOR_H

#include <QHash>
#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "enigmaexception.h"
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
    QHash<QString, QString> map;

    bool sanityCheck();

private:

};

#endif // ROTOR_H
