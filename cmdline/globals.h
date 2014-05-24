/************************************************************************
Copyright Chris Newey 2013

enigmasim@outlook.com

This file is part of enigma.

Enigma is distributed under the terms of the GNU General Public License

Enigma is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Enigma is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Enigma.  If not, see <http://www.gnu.org/licenses/>.

***************************************************************************/

#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
using namespace std;

#include <QObject>
#include <QPointer>
#include <QSettings>
#include <QString>
#include <QVariant>

class Globals : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString db_driver       READ db_driver       WRITE setDb_driver       NOTIFY db_driverChanged)
    Q_PROPERTY(QString db_hostname     READ db_hostname     WRITE setDb_hostname     NOTIFY db_hostnameChanged)
    Q_PROPERTY(QString db_databasename READ db_databasename WRITE setDb_databasename NOTIFY db_databasenameChanged)
    Q_PROPERTY(QString db_username     READ db_username     WRITE setDb_username     NOTIFY db_usernameChanged)
    Q_PROPERTY(QString db_password     READ db_password     WRITE setDb_password     NOTIFY db_passwordChanged)

    Q_ENUMS(EDIT_MODE)

public:

    typedef enum
    {
        ROW_ADD, ROW_EDIT, ROW_DEL
    }
    EDIT_MODE;

    typedef int UNWRITTEN_ID;

    static const UNWRITTEN_ID NEW_ID;
    static const int INVALID_PIN_NUMBER;

    static const QString ORGANIZATION_NAME;
    static const QString APPLICATION_NAME;
    static const QString APPLICATION_VERSION;

    static const QString DB_DRIVER;
    static const QString DB_HOSTNAME;
    static const QString DB_DATABASENAME;
    static const QString DB_USERNAME;
    static const QString DB_PASSWORD;

    static Globals *getInstance();

    QString organization_name() const;
    void setOrganization_name(const QString &value);

    QString application_name() const;
    void setApplication_name(const QString &value);

    QString application_version() const;
    void setApplication_version(const QString &value);

    QString db_driver() const;
    void setDb_driver(const QString &value);

    QString db_hostname() const;
    void setDb_hostname(const QString &value);

    QString db_databasename() const;
    void setDb_databasename(const QString &value);

    QString db_username() const;
    void setDb_username(const QString &value);

    QString db_password() const;
    void setDb_password(const QString &value);

    virtual void save();
    virtual void display();

signals:

    void db_driverChanged(const QString &db_driver);
    void db_hostnameChanged(const QString &db_hostname);
    void db_databasenameChanged(const QString &db_databasename);
    void db_usernameChanged(const QString &db_username);
    void db_passwordChanged(const QString &db_password);


public slots:

protected:

    virtual void initialiseObject();

    virtual void saveSettings();
    virtual void getSettings();

private:

    static bool instanceFlag;
    static QPointer<Globals> singleton;

    QString m_organization_name;
    QString m_application_name;
    QString m_application_version;

    QString m_db_driver;
    QString m_db_hostname;
    QString m_db_databasename;
    QString m_db_username;
    QString m_db_password;


    explicit Globals(QObject *parent = 0);

};

#endif // GLOBALS_H
