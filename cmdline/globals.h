#ifndef GLOBALS_H
#define GLOBALS_H

#include <QObject>
#include <QString>

class Globals : public QObject
{
    Q_OBJECT
public:

    static const QString ORGANIZATION_NAME;
    static const QString APPLICATION_NAME;
    static const QString APPLICATION_VERSION;

    static const QString DB_DRIVER;
    static const QString DB_HOSTNAME;
    static const QString DB_DATABASENAME;
    static const QString DB_USERNAME;
    static const QString DB_PASSWORD;

    explicit Globals(QObject *parent = 0);

signals:

public slots:

};

#endif // GLOBALS_H
