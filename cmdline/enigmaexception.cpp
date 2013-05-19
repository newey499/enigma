#include "enigmaexception.h"

/********
EnigmaException::EnigmaException(const string& message) :
    runtime_error(message)
{
}
*********************/

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
