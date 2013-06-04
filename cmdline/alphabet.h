#ifndef ALPHABET_H
#define ALPHABET_H

#include <QObject>
#include <QPointer>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "enigmaexception.h"
#include "globals.h"
#include "genlib.h"
#include "componentbase.h"

class Alphabet : public ComponentBase
{
    Q_OBJECT

public:

    explicit Alphabet(QObject *parent = 0);
    ~Alphabet();

    virtual QSqlRecord getAlphabet(const QString &alphabetName);
    virtual QSqlRecord getAlphabet(int id);
    virtual bool validateAlphabet(EDIT_MODE mode, QSqlRecord rec);

    virtual bool validateAlphabetName(QSqlQuery &qry, QString name, QString msg);

signals:

public slots:


protected:


private:


};

#endif // ALPHABET_H
