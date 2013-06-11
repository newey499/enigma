#ifndef EMITSTRING_H
#define EMITSTRING_H

#include <QObject>
#include <QString>

class EmitString : public QObject
{
    Q_OBJECT
public:
    explicit EmitString(QObject * formPtr, QObject *parent = 0);

signals:

    void emitStr(QString);

public slots:

    virtual void slotEmitStr(QString str);

protected:

    QObject *formPtr;


};

#endif // EMITSTRING_H
