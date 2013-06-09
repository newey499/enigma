#ifndef ENIGMAACTION_H
#define ENIGMAACTION_H

#include <QAction>

class EnigmaAction : public QAction
{
    Q_OBJECT

public:
    explicit EnigmaAction(QObject *parent = 0);
    explicit EnigmaAction(const QString & text, QObject * parent = 0);
    explicit EnigmaAction(const QIcon & icon, const QString & text, QObject * parent = 0);


signals:

    void signalTriggered(EnigmaAction *);


public slots:


protected slots:

    virtual void slotTriggered();

protected:

    void commonConstructor();


private:

};

#endif // ENIGMAACTION_H
