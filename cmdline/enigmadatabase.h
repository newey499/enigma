#ifndef ENIGMADATABASE_H
#define ENIGMADATABASE_H

#include <QPointer>
#include <QSqlDatabase>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QVariant>



class EnigmaDatabase : public QObject
{
    Q_OBJECT

public:

    static EnigmaDatabase *getInstance();

    ~EnigmaDatabase();

    QSqlRecord getRotor(const QString &rotorName);
    QSqlRecord getRotor(int id);

    QSqlRecord getAlphabet(const QString &alphabetName);
    QSqlRecord getAlphabet(int id);

signals:

public slots:


protected:

    QSqlDatabase db;


private:

    static bool instanceFlag;
    static QPointer<EnigmaDatabase> singleton;

    explicit EnigmaDatabase(QObject *parent = 0);


};

#endif // ENIGMADATABASE_H
