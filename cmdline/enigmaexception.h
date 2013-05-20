/************************************************************************
Copyright Chris Newey 2013

enigmasim@outlook.com

This file is part of enigma.

Enigma is distributed under the terms of the GNU General Public License

Enigma is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Qiptables is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Qiptables.  If not, see <http://www.gnu.org/licenses/>.

***************************************************************************/

#ifndef ENIGMAEXCEPTION_H
#define ENIGMAEXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

#include <QString>
#include <QtDebug>


class EnigmaException : public runtime_error
{

public:

    // EnigmaException(const string& message);
    EnigmaException(char *message, char *filename, int lineNo);

    virtual ~EnigmaException() throw();

    QString what();
    QString getMessage();
    QString getFilename();
    int getLineNo();

protected:

    QString message;
    QString filename;
    int lineNo;

private:


};

#endif // ENIGMAEXCEPTION_H
