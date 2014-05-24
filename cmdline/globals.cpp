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

#include "globals.h"

const QString Globals::ORGANIZATION_NAME    = "net.home.chris-newey";
const QString Globals::APPLICATION_NAME     = "ENIGMA";
const QString Globals::APPLICATION_VERSION  = "0.3.0";

const QString Globals::DB_DRIVER        = "QODBC";
const QString Globals::DB_HOSTNAME      = "127.0.0.1"; // Not needed for ODBC connections
const QString Globals::DB_DATABASENAME  = "enigma_mysql";
const QString Globals::DB_USERNAME      = "cdn";
const QString Globals::DB_PASSWORD      = "charlton";

const Globals::UNWRITTEN_ID Globals::NEW_ID = -999;
const int Globals::INVALID_PIN_NUMBER = -888;

bool Globals::instanceFlag = false;
QPointer<Globals> Globals::singleton = NULL;

Globals::Globals(QObject *parent) :
    QObject(parent)
{
    initialiseObject();
}

Globals *Globals::getInstance()
{
    if(! instanceFlag)
    {
        singleton = new Globals();
        instanceFlag = true;
    }

    return singleton;
}
QString Globals::organization_name() const
{
    return m_organization_name;
}

void Globals::setOrganization_name(const QString &value)
{
    m_organization_name = value;
}
QString Globals::application_name() const
{
    return m_application_name;
}

void Globals::setApplication_name(const QString &value)
{
    m_application_name = value;
}
QString Globals::application_version() const
{
    return m_application_version;
}

void Globals::setApplication_version(const QString &value)
{
    m_application_version = value;
}
QString Globals::db_driver() const
{
    return m_db_driver;
}

void Globals::setDb_driver(const QString &value)
{
    m_db_driver = value;
}
QString Globals::db_hostname() const
{
    return m_db_hostname;
}

void Globals::setDb_hostname(const QString &value)
{
    m_db_hostname = value;
}
QString Globals::db_databasename() const
{
    return m_db_databasename;
}

void Globals::setDb_databasename(const QString &value)
{
    m_db_databasename = value;
}
QString Globals::db_username() const
{
    return m_db_username;
}

void Globals::setDb_username(const QString &value)
{
    m_db_username = value;
}
QString Globals::db_password() const
{
    return m_db_password;
}

void Globals::setDb_password(const QString &value)
{
    m_db_password = value;
}

void Globals::save()
{
    saveSettings();
}

void Globals::saveSettings()
{
    QSettings settings(Globals::ORGANIZATION_NAME, Globals::APPLICATION_NAME, this);

    //qDebug("Globals::saveSettings()");

    settings.setValue("database/driver", db_driver());
    settings.setValue("database/hostname", db_hostname());
    settings.setValue("database/databasename", db_databasename());
    settings.setValue("database/username", db_username());
    settings.setValue("database/password", db_password());

    //display();

}

void Globals::getSettings()
{
    QSettings settings(Globals::ORGANIZATION_NAME, Globals::APPLICATION_NAME, this);

    setDb_driver(settings.value("database/driver", Globals::DB_DRIVER).toString());
    setDb_hostname(settings.value("database/hostname", Globals::DB_HOSTNAME).toString());
    setDb_databasename(settings.value("database/databasename", Globals::DB_DATABASENAME).toString());
    setDb_username(settings.value("database/username", Globals::DB_USERNAME).toString());
    setDb_password(settings.value("database/password", Globals::DB_PASSWORD).toString());

    //qDebug("Globals::getSettings()");
    //display();
}

void Globals::initialiseObject()
{
    getSettings();
}

void Globals::display()
{
    QString msg;

    msg = QString("Globals::display \norganization %1\napplication %2\nversion %3\ndriver %4\nhostname %5\ndatabasename %6\nusername %7\npassword %8\n")
            .arg(m_organization_name)
            .arg(m_application_name)
            .arg(m_application_version)
            .arg(m_db_driver)
            .arg(m_db_hostname)
            .arg(m_db_databasename)
            .arg(m_db_username)
            .arg(m_db_password);

    cout << msg.toStdString() << endl;
}




