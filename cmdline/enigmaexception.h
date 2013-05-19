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
