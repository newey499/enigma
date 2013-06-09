#include "enigmaaction.h"

EnigmaAction::EnigmaAction(QObject *parent) :
    QAction(parent)
{
    commonConstructor();
}

EnigmaAction::EnigmaAction(const QString & text, QObject * parent) :
    QAction(text, parent)
{
    commonConstructor();
}

EnigmaAction::EnigmaAction(const QIcon & icon, const QString & text, QObject * parent) :
    QAction(icon, text, parent)
{
    commonConstructor();
}

void EnigmaAction::commonConstructor()
{
    connect(this, SIGNAL(triggered()),
            this, SLOT(slotTriggered()));
}

void EnigmaAction::slotTriggered()
{
    emit signalTriggered(this);
}
