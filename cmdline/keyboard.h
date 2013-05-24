#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "genlib.h"
#include "enigmaexception.h"
#include "enigmadatabase.h"

class Keyboard : public QObject
{
    Q_OBJECT

public:

    explicit Keyboard(QString name, QObject *parent = 0);
    explicit Keyboard(int alphabetId, QObject *parent = 0);

    virtual bool isValidKey(QString keyIn);
    virtual QString keyIn(QString keyIn);

    virtual QString getAlphabetName();
    virtual QString getAlphabetMap();


signals:

public slots:


protected:

    QPointer<EnigmaDatabase> edb;

    QSqlRecord recAlphabet;

    int alphabetSize;

    QString alphabetMap;
    QString alphabetName;

    virtual bool sanityCheck();


private:



};

#endif // KEYBOARD_H
