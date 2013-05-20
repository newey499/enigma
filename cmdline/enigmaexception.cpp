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

#include "enigmaexception.h"


EnigmaException::~EnigmaException() throw()
{

}

EnigmaException::EnigmaException(char *message, char *filename, int lineNo) :
    runtime_error(message)
{
    this->message   = message;
    this->filename  = filename;
    this->lineNo    = lineNo;
}


QString EnigmaException::what()
{
    QString tmp = QString("EnigmaException msg [%1] : file [%2] : line [%3]").
                    arg(message).
                    arg(filename).
                    arg(lineNo);

    return tmp;
}


QString EnigmaException::getMessage()
{
    return message;
}

QString EnigmaException::getFilename()
{
    return filename;
}

int EnigmaException::getLineNo()
{
    return lineNo;
}
