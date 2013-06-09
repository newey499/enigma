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

const QString Globals::DB_DRIVER        = "QMYSQL";
const QString Globals::DB_HOSTNAME      = "127.0.0.1";
const QString Globals::DB_DATABASENAME  = "enigma";
const QString Globals::DB_USERNAME      = "cdn";
const QString Globals::DB_PASSWORD      = "charlton";

const Globals::UNWRITTEN_ID Globals::NEW_ID = -999;
const int Globals::INVALID_PIN_NUMBER = -888;

Globals::Globals(QObject *parent) :
    QObject(parent)
{
}


