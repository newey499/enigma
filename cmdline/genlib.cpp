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

#include "genlib.h"

GenLib::GenLib(QObject *parent) :
    QObject(parent)
{
}


GenLib::~GenLib()
{

}


bool GenLib::alphabetDuplicateCheck(QString alphabetName, QString alphabet)
{
    bool result = true;

    // Disable deprecated conversion from string constant to char * warning
    // when instantiating EnigmaException object
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

    for (int i = 0; i < alphabet.count(); i++)
    {
        if (alphabet.count(alphabet.at(i), Qt::CaseSensitive ) != 1)
        {
            QString tmp = QString("character [%1] found [%2] time(s) in definition [%3] - should only be one").
                            arg(alphabet.at(i)).
                            arg(alphabet.count(alphabet.at(i), Qt::CaseSensitive )).
                            arg(alphabetName);
            result = false;
            throw EnigmaException(tmp.toAscii().data(), __FILE__ , __LINE__);
        }
    }

#pragma GCC diagnostic pop

    return result;
}


bool GenLib::alphabetSanityCheck(QString alphabetName, QString alphabet,
                                 QString mappingName, QString mapping)
{
    bool result = true;


// Disable deprecated conversion from string constant to char * warning
// when instantiating EnigmaException object
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

    // alphabetDuplicateCheck will throw an exception if a duplate is found
    GenLib::alphabetDuplicateCheck(alphabetName, alphabet);
    GenLib::alphabetDuplicateCheck(mappingName, mapping);

    if (alphabet.size() != mapping.size())
    {
        QString tmp = QString("mapping: alphabet lengths do not match alphabet [%1] mapping [%2]").
                                arg(alphabetName).
                                arg(mappingName);
        result = false;
        throw EnigmaException(tmp.toAscii().data(), __FILE__ , __LINE__);
    }

    for (int i = 0; i < alphabet.count(); i++)
    {
        if (! mapping.contains(alphabet.at(i), Qt::CaseSensitive))
        {

            QString tmp = QString("Alphabet character [%1] not found in mapping definition [%2]").
                                    arg(alphabet.at(i)).
                                    arg(mappingName);
            result = false;
            throw EnigmaException(tmp.toAscii().data(), __FILE__ , __LINE__);
        }
    }

    for (int i = 0; i < mapping.count(); i++)
    {
        if (! alphabet.contains(mapping.at(i), Qt::CaseSensitive))
        {

            QString tmp = QString("mapping character [%1] not found in Alphabet definition [%2]").
                                    arg(mapping.at(i)).
                                    arg(alphabetName);
            result = false;
            throw EnigmaException(tmp.toAscii().data(), __FILE__ , __LINE__);
        }
    }

#pragma GCC diagnostic pop

    return result;
}



void GenLib::myMessageHandler(QtMsgType type, const char *msg)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(msg);
        break;
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg);
    break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
    break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(msg);
    break;
    }
    QFile outFile("Qtlog.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    //ts << txt << endl;
    fprintf(stdout, txt.append("\n").toAscii().data());
}
